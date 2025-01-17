/*
포탑 : N x M 격자의 모든 위치에 존재 (NM개)
	   공격력. 공격력이 0 이하가 된다면, 해당 포탑은 부서지며 더 이상의 공격을 할 수 없음
	   생존 여부
	   최근 공격 턴 (모든 포탑은 시점 0에 모두 공격한 경험이 있다고 가정)
	   한 턴에서 공격 관련 여부
공격자
피공격자

하나의 턴은 다음의 4가지 액션을 순서대로 수행, 총 K번 반복
만약 부서지지 않은 포탑이 1개가 된다면 그 즉시 중지
1. 공격자 선정
부서지지 않은 포탑 중 가장 약한 포탑이 공격자로 선정. N+M 만큼의 공격력 증가
우선순위 : 공격력 최소 > 공격 턴 최대 > 행 + 열 최대 > 열 최대

2. 공격자의 공격
위에서 선정된 공격자는 자신을 제외한 가장 강한 포탑을 공격
가장 강한 포탑의 우선순위 : 공격력 최대 > 공격 턴 최소 > 행 + 열 최소 > 열 최소
(1) 레이저 공격
상하좌우의 4개의 방향으로 움직임
부서진 포탑이 있는 위치는 지날 수 없음
가장자리에서 막힌 방향으로 진행하고자 한다면, 반대편으로 나옴

공격자의 위치에서 공격 대상 포탑까지의 최단 경로로 공격.
만약 그러한 경로가 존재하지 않는다면 포탄 공격을 진행
경로의 길이가 똑같은 최단 경로가 2개 이상이라면 우/하/좌/상의 우선순위대로 먼저 움직인 경로

공격 대상에는 공격자 만큼의 피해를 입히며, 피해를 입은 포탑은 해당 수치만큼 공격력이 줄어듬
공격 대상을 제외한 레이저 경로에 있는 포탑도 공격을 받게 되는데 공격자 공격력의 절반만큼

(2) 포탄 공격
공격 대상에 포탄을 던짐.
공격 대상은 공격자 공격력 만큼의 피해를 받음
주위 8개 방향의 포탑도 공격자 공격력 절반만큼
공격자는 해당 공격에 영향을 받지 않음
가장자리에 포탄이 떨어졌다면, 레이저 이동처럼 포탄의 추가 피해가 반대편 격자에 미침

3. 포탑 부서짐
공격을 받아 공격력이 0 이하가 된 포탑은 부서짐

4. 포탑 정비
부서지지 않은 포탑 중 공격과 무관했던 포탑은 공격력이 1씩 올라감
공격자도 아니고 공격에 피해를 입은 포탑도 아니라는 의미

전체 과정이 종료된 후 남아있는 포탑 중 가장 강한 포탑의 공격력을 출력
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

#define GRID_SIZE 10
#define DIR_NUM 4
#define EIGHT_NUM 8

struct Turret {
	int power;
	int turn;
	int row;
	int col;
};

bool Comparator(Turret& a, Turret& b) {
	if (a.power != b.power) return a.power < b.power;
	if (a.turn != b.turn) return a.turn > b.turn;
	if (a.row + a.col != b.row + b.col) return a.row + a.col > b.row + b.col;
	return a.col > b.col;
}

int n, m, k;
int grid[GRID_SIZE][GRID_SIZE];
int recent_attack[GRID_SIZE][GRID_SIZE];
bool participate[GRID_SIZE][GRID_SIZE];

int visited[GRID_SIZE][GRID_SIZE];

int back_x[GRID_SIZE][GRID_SIZE];
int back_y[GRID_SIZE][GRID_SIZE];

// 우하좌상 우선순위
int dx[DIR_NUM] = {0,1,0,-1};
int dy[DIR_NUM] = {1,0,-1,0};

int dx8[EIGHT_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy8[EIGHT_NUM] = {0,1,1,1,0,-1,-1,-1};

pair<int, int> attacker;
pair<int, int> attacked;
  
bool KeepGoing() {
	int cnt = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] != 0) cnt++;
		}
	}

	if (cnt <= 1) return false;
	else return true;
}

void SelectAttack() {
	vector<Turret> v;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] != 0) {
				Turret new_turret;
				new_turret.power = grid[i][j];
				new_turret.turn = recent_attack[i][j];
				new_turret.row = i;
				new_turret.col = j;
				v.push_back(new_turret);
			}
		}
	}

	sort(v.begin(), v.end(), Comparator);

	attacker = make_pair(v[0].row, v[0].col);
	attacked = make_pair(v[v.size() - 1].row, v[v.size() - 1].col);

	grid[attacker.first][attacker.second] += (n + m);

	
}

bool InRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

bool RaserAttack(int turn) {
	// 레이저 공격이 성공했는지 실패했는지 return 해야함
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = false;
			back_x[i][j] = -1;
			back_y[i][j] = -1;
		}
	}

	queue<pair<int, int>> q;
	q.push({ attacker.first, attacker.second });
	visited[attacker.first][attacker.second] = true;

	while (!q.empty()) {
		int cx, cy;
		tie(cx, cy) = q.front(); q.pop();

		if (cx == attacked.first && cy == attacked.second) {

			recent_attack[attacker.first][attacker.second] = turn;
			participate[attacker.first][attacker.second] = true;

			// 공격력 / 최근 공격 턴 / 한 턴에서 관련 여부
			int damage = grid[attacker.first][attacker.second];
			int half_damage = damage / 2;

			grid[attacked.first][attacked.second] -= damage;
			participate[attacked.first][attacked.second] = true;

			int cx = attacked.first, cy = attacked.second;
			while (!(cx == attacker.first && cy == attacker.second)) {
				int bx = back_x[cx][cy], by = back_y[cx][cy];

				if (bx == attacker.first && by == attacker.second) break;
				grid[bx][by] -= half_damage;
				participate[bx][by] = true;

				cx = bx, cy = by;
			}

			return true;
		}

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];

			if (!InRange(nx, ny)) {
				while (nx < 0) {
					nx += n;
				}
				nx %= n;

				while (ny < 0) {
					ny += m;
				}
				ny %= m;
			}

			if (visited[nx][ny] || grid[nx][ny] == 0) continue;

			q.push({ nx, ny });
			visited[nx][ny] = true;
			back_x[nx][ny] = cx;
			back_y[nx][ny] = cy;
		}
	}

	return false;
}

void BombAttack(int turn) {
	recent_attack[attacker.first][attacker.second] = turn;
	participate[attacker.first][attacker.second] = true;

	int damage = grid[attacker.first][attacker.second];
	int half_damage = damage / 2;

	grid[attacked.first][attacked.second] -= damage;
	participate[attacked.first][attacked.second] = true;

	for (int dir = 0; dir < EIGHT_NUM; dir++) {
		int nx = attacked.first + dx8[dir], ny = attacked.second + dy8[dir];
		if (!InRange(nx, ny)) {
			while (nx < 0) {
				nx += n;
			}
			nx %= n;

			while (ny < 0) {
				ny += m;
			}
			ny %= m;
		}

		if (grid[nx][ny] == 0) continue;
		if (nx == attacker.first && ny == attacker.second) continue;
		
		grid[nx][ny] -= half_damage;
		participate[nx][ny] = true;
	}
}

void Attack(int turn) {
	// 공격자의 최근 공격 턴과 한 턴에서의 공격 여부를 관리해주어야 함
	if (!RaserAttack(turn)) {
		BombAttack(turn);
	}
}

void Destroy() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] < 0) grid[i][j] = 0;
		}
	}
}

void Restore() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (participate[i][j] || grid[i][j] == 0) continue;
			grid[i][j]++;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			recent_attack[i][j] = 1;
		}
	}

	for (int t = 1; t <= k; t++) {
		if (!KeepGoing()) break;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				participate[i][j] = false;
			}
		}

		SelectAttack();
		Attack(t);

		
		Destroy();
		

		Restore();
		
	}

	// 남아있는 포탑 중 가장 강한 포탑의 공격력 출력
	int max_power = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 0) continue;
			max_power = max(max_power, grid[i][j]);
		}
	}

	cout << max_power << "\n";
	return 0;
}