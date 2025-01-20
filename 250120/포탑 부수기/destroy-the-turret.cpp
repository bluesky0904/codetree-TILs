#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

#define GRID_SIZE 10
#define DIR_NUM 4
#define DIR_EIGHT 8

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

bool visited[GRID_SIZE][GRID_SIZE];
int back_x[GRID_SIZE][GRID_SIZE];
int back_y[GRID_SIZE][GRID_SIZE];

pair<int, int> attacker;
pair<int, int> attacked;

int dx[DIR_NUM] = {0,1,0,-1};
int dy[DIR_NUM] = {1,0,-1,0};

int dx_8[DIR_EIGHT] = {-1,-1,0,1,1,1,0,-1};
int dy_8[DIR_EIGHT] = {0,1,1,1,0,-1,-1,-1};

bool keepGoing() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] > 0) cnt++;
		}
	}
	if (cnt > 1) return true;
	else return false;
}

void selectAttack() {
	vector<Turret> v;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 0) continue;

			Turret new_turret;
			new_turret.power = grid[i][j];
			new_turret.turn = recent_attack[i][j];
			new_turret.row = i;
			new_turret.col = j;

			v.push_back(new_turret);
		}
	}

	sort(v.begin(), v.end(), Comparator);
	
	attacker = { v[0].row, v[0].col };
	grid[attacker.first][attacker.second] += (n + m);

	attacked = { v[v.size() - 1].row, v[v.size() - 1].col };

	//cout << "공격자 " << attacker.first << " " << attacker.second << "\n";
	//cout << "피공격자 " << attacked.first << " " << attacked.second << "\n";
}

void print() {
	cout << "GRID\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "RECENT_ATTACK\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << recent_attack[i][j] << " ";
		}
		cout << "\n";
	}cout << "PARTICIPATE\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << participate[i][j] << " ";
		}
		cout << "\n";
	}
}

bool inRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

bool raserAttack(int turn) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = false;
		}
	}

	queue<pair<int, int>> q;

	q.push(attacker);
	visited[attacker.first][attacker.second] = true;
	while (!q.empty()) {
		int cx, cy;
		tie(cx, cy) = q.front(); q.pop();

		if (cx == attacked.first && cy == attacked.second) {

			int damage = grid[attacker.first][attacker.second];
			int half_damage = damage / 2;
			recent_attack[attacker.first][attacker.second] = turn;
			participate[attacker.first][attacker.second] = true;

			grid[attacked.first][attacked.second] -= damage;
			participate[attacked.first][attacked.second] = true;

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
			if (!inRange(nx, ny)) {
				while (nx < 0) nx += n;
				nx %= n;
				while (ny < 0) ny += m;
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

void bombAttack(int turn) {
	int damage = grid[attacker.first][attacker.second];
	int half_damage = damage / 2;
	recent_attack[attacker.first][attacker.second] = turn;
	participate[attacker.first][attacker.second] = true;

	grid[attacked.first][attacked.second] -= damage;
	participate[attacked.first][attacked.second] = true;
	for (int dir = 0; dir < DIR_EIGHT; dir++) {
		int nx = attacked.first + dx_8[dir], ny = attacked.second + dy_8[dir];
		if (!inRange(nx, ny)) {
			while (nx < 0) nx += n;
			nx %= n;
			while (ny < 0) ny += m;
			ny %= m;
		}

		if (grid[nx][ny] == 0) continue;
		if (nx == attacker.first && ny == attacker.second) continue;

		grid[nx][ny] -= half_damage;
		participate[nx][ny] = true;
	}
}

void attack(int turn) {
	// 최근 공격턴과 공격 참여 여부 관리
	if (!raserAttack(turn)) bombAttack(turn);
}

void broken() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] < 0) grid[i][j] = 0;
		}
	}
}

void recovery() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 0 || participate[i][j]) continue;
			grid[i][j]++;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);

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
		if (!keepGoing()) break;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				participate[i][j] = false;
			}
		}

		selectAttack();
		//print();

		attack(t);
		//print();

		broken();
		//print();

		recovery();
		//print();
	}

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