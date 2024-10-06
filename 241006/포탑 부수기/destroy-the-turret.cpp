/*
격자 : N * M, 모든 위치에는 포탑이 존재
포탑 : 위치, 공격력, 가장 최근 공격한 턴, 턴 참여 여부

공격력이 0 이하가 된다면, 해당 포탑은 부서지며 더 이상의 공격을 할 수 없음. 최초에 공격력이 0인 포탑이 존재할 수 있음.
모든 포탑은 시점 0에 모두 공격한 경험이 있다고 가정.

하나의 턴은 4가지 액션을 순서대로 수행하며, 총 K번 반복. 만약 부서지지 않은 포탑이 1개가 된다면 그 즉시 중지.

1. 공격자 선정
부서지지 않은 포탑 중 가장 약한 포탑. N + M 만큼의 공격력이 증가
1) 공격력 최소
2) 최근 공격한 턴 최대
3) 행 + 열 값 최대
4) 열 값 최대

2. 공격자의 공격
자신을 제외한 가장 강한 포탑을 공격. 레이저 공격을 먼저 시도하고, 만약 그게 안 된다면 포탄 공격.
1) 공격력 최대
2) 최근 공격한 턴 최소
3) 행 + 열 값 최소
4) 열 값 최소

2-1. 레이저 공격
1) 상하좌우 4개의 방향으로 이동 가능
2) 부서진 포탑이 있는 위치는 지날 수 없음
3) 가장자리에서 막힌 방향으로 진행하고자 한다면, 반대편으로 나옴.
공격자의 위치에서 공격 대상 포탑까지의 최단 경로로 공격. 만약 그러한 경로가 존재하지 않으면 포탄 공격.
최단 경로가 두 개 이상이라면 우/하/좌/상의 우선순위대로 먼저 움직인 경로가 선택.

공격 대상 포탑은 공격자의 공격력 만큼의 공격력이 줄어듬. 또한 레이저 경로에 있는 포탑들은 공격자 공격력의 절반(2로 나눈 몫)만큼 공격력이 줄어듬.

2-2. 포탄 공격
공격 대상은 공격자 공격력 만큼의 피해. 주위 8개의 방향에 있는 포탑도 공격자의 공격력의 절반 만큼의 피해. 가장자리에 포탄이 떨어졌다면, 반대편 격자에 영향

3. 공격을 받아 공격력이 0 이하가 된 포탑은 부서짐.

4 포탑 정비
부서지지 않은 포탑 중 공격과 무관했던 포탑(공격자도 아니고, 공격에 피해를 입은 포탑도 아님)은 공격력이 1씩 올라감.

전체 과정이 종료된 후 남아있는 포탑 중 가장 강한 포탑의 공격력을 출력
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>
using namespace std;

#define GRID_SIZE 10
#define DIR_NUM 8

struct Turret {
	int power;
	int turn;
	int row;
	int col;
};

bool Cmp1(Turret a, Turret b) {
	if (a.power != b.power) return a.power < b.power;
	if (a.turn != b.turn) return a.turn > b.turn;
	if (a.row + a.col != b.row + b.col) return a.row + a.col > b.row + b.col;
	return a.col > b.col;
}

bool Cmp2(Turret a, Turret b) {
	if (a.power != b.power) return a.power > b.power;
	if (a.turn != b.turn) return a.turn < b.turn;
	if (a.row + a.col != b.row + b.col) return a.row + a.col < b.row + b.col;
	return a.col < b.col;
}

int N, M, K;
int grid[GRID_SIZE][GRID_SIZE];
int recent_attack[GRID_SIZE][GRID_SIZE] = { 0, };
bool participate[GRID_SIZE][GRID_SIZE];

pair<int, int> attacker;
pair<int, int> attacked;

bool visited[GRID_SIZE][GRID_SIZE];
int back_x[GRID_SIZE][GRID_SIZE], back_y[GRID_SIZE][GRID_SIZE];

int dx[DIR_NUM] = {0,1,1,1,0,-1,-1,-1};
int dy[DIR_NUM] = {1,1,0,-1,-1,-1,0,1};

bool StopTest() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] > 0) cnt++;
		}
	}
	if (cnt == 1) return true;
	else return false;
}

void ChooseAttacker() {
	Turret weak_turret;
	weak_turret.power = 5000;
	weak_turret.turn = 0;
	weak_turret.row = -1;
	weak_turret.col = -1;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] == 0) continue;

			Turret turret;
			turret.power = grid[i][j];
			turret.turn = recent_attack[i][j];
			turret.row = i;
			turret.col = j;

			if (Cmp1(turret, weak_turret)) weak_turret = turret;
		}
	}

	attacker.first = weak_turret.row;
	attacker.second = weak_turret.col;
	grid[attacker.first][attacker.second] += (N + M);
}

void ChooseAttacked() {
	Turret strong_turret;
	strong_turret.power = 0;
	strong_turret.turn = K;
	strong_turret.row = N;
	strong_turret.col = M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] == 0) continue;
			if(i == attacker.first && j == attacker.second) continue;
			Turret turret;
			turret.power = grid[i][j];
			turret.turn = recent_attack[i][j];
			turret.row = i;
			turret.col = j;

			if(Cmp2(turret, strong_turret)) strong_turret = turret;
		}
	}

	attacked.first = strong_turret.row;
	attacked.second = strong_turret.col;
}

bool BFS() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = false;
		}
	}

	queue<pair<int, int>> q;
	q.push({ attacker.first, attacker.second });
	visited[attacker.first][attacker.second] = true;

	bool can_attack = false;

	while (!q.empty()) {
		int x, y;
		tie(x, y) = q.front(); q.pop();

		if (x == attacked.first && y == attacked.second) {
			can_attack = true;
			break;
		}

		for (int dir = 0; dir < DIR_NUM; dir+=2) {
			int nx = (x + dx[dir] + N) % N;
			int ny = (y + dy[dir] + M) % M;

			if (visited[nx][ny]) continue;
			if (grid[nx][ny] == 0) continue;
			visited[nx][ny] = true;
			back_x[nx][ny] = x;
			back_y[nx][ny] = y;
			q.push(make_pair(nx, ny));
		}
	}

	return can_attack;
}

bool RaserAttack() {
	if(!BFS()) return false;
	
	int sx = attacker.first;
	int sy = attacker.second;

	int pow = grid[sx][sy];

	int ex = attacked.first;
	int ey = attacked.second;

	grid[ex][ey] -= pow;
	participate[ex][ey] = true;

	int cx = back_x[ex][ey];
	int cy = back_y[ex][ey];

	while (!(cx == sx && cy == sy)) {
		grid[cx][cy] -= int(pow / 2);
		participate[cx][cy] = true;

		int next_cx = back_x[cx][cy];
		int next_cy = back_y[cx][cy];

		cx = next_cx;
		cy = next_cy;
	}
	participate[sx][sy] = true;

	return true;
}

void BombAttack() {
	int sx = attacker.first;
	int sy = attacker.second;
	participate[sx][sy] = true;

	int damage = grid[attacker.first][attacker.second];

	int cx = attacked.first, cy = attacked.second;
	participate[cx][cy] = true;
	grid[cx][cy] -= damage;

	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = (cx + dx[dir] + N) % N;
		int ny = (cy + dy[dir] + M) % M;

		if (nx == attacker.first && ny == attacker.second) continue;

		if (grid[nx][ny] == 0) continue;

		participate[nx][ny] = true;
		grid[nx][ny] -= int(damage / 2);
	}
}

void Attack(int turn) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			participate[i][j] = false;
		}
	}

	if (!RaserAttack()) BombAttack();
	recent_attack[attacker.first][attacker.second] = turn;
}

void Destroy() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] < 0) grid[i][j] = 0;
		}
	}
}

void Recover() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] != 0 && !participate[i][j]) grid[i][j]++;
		}
	}
}

int ChoosePowerful() {
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] > ans) ans = grid[i][j];
		}
	}

	return ans;
}

void Print() {
	cout << "============================================\n";
	cout << attacker.first << " " << attacker.second << "\n";
	cout << attacked.first << " " << attacked.second << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout <<  grid[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> grid[i][j];
		}
	}

	for(int i = 1; i <= K; i++){
		if (StopTest()) break;

		ChooseAttacker();
		ChooseAttacked();
		//Print();

		Attack(i);
		//Print();

		Destroy();
		//Print();

		Recover();
		//Print();
	}

	cout << ChoosePowerful() << "\n";
	return 0;
}