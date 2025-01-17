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
			recent_attack[i][j] = 0;
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