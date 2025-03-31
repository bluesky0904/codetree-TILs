/*
격자 : n x n
술래 : 초기 위치 = 정중앙, 이동 방향, 점수
도망자 : m명, 위치, 좌우로만 움직이는 유형 -> 오른쪽을 보고 시작 || 상하로만 움직이는 유형 -> 아래쪽을 보고 시작, 사라짐 여부
나무 : h개, 위치
나무가 도망자와 초기에 겹쳐져 주어지는 것 역시 가능

k번 턴을 반복하면서
1. m명의 도망자가 먼저 동시에 움직임
현재 술래와의 거리가 3 이하인 도망자만 움직임. 거리는 절댓값의 합
1-1.현재 바라보고 있는 방향으로 1칸 움직인다 했을 때 격자를 벗어나지 않는 경우
-> 움직이려는 칸에 술래가 있는 경우라면 움직이지 않음
-> 움직이려는 칸에 술래가 있지 않다면 해당 칸으로 이동. 해당 칸에 나무가 있어도 괜찮음
1-2. 현재 바라보고 있는 방향으로 1칸 움직인다 했을 때 격자를 벗어나는 경우
-> 먼저 방향을 반대로 틀어줌. 이후 바라보고 있는 방향으로 1칸 움직인다 했을 때 해당 위치에 술래가 없다면 1칸 앞으로 이동
2. 술래가 움직임
술래는 처음 위 방향으로 시작하여 달팽이 모양으로 움직임
만약 끝에 도달하게 되면 다시 거꾸로 중심으로 이동하고, 다시 중심에 오게 되면 처음처럼 위 방향으로 시작하여 시계방향으로 도는 것을 k턴에 걸쳐 반복
술래는 1번의 턴 동안 정확히 한 칸 해당하는 방향으로 이동
이동 후의 위치가 만약 이동방향이 틀어지는 지점이라면, 방향을 바로 틀어줌
만약 이동을 통해 양끝에 해당하는 위치인 (1행, 1열) 혹은 정중앙에 도달하게 된다면 이 경우 역시 방향을 바로 틀어줘야 함에 유의

이동 직후 술래는 턴을 넘기기 전에 시야 내에 있는 도망자를 잡음
술래의 시야는 현재 바라보고 있는 방향을 기준으로 현재 칸을 포함하여 3칸
격자 크기에 상관없이 술래의 시야는 항상 3칸임에 유의
하지만 만약 나무가 놓여 있는 칸이라면, 해당 칸에 있는 도망자는 나무에 가려져 보이지 않게 됨. 그 뒤에 있는 3칸 안에 있는 도망자는 잡힘
잡힌 도망자는 사라지게 되고, 술래는 현재 턴을 t번째 턴이라고 했을 때 t x (현재 턴에서 잡힌 도망자의 수) 만큼의 점수를 얻게 됨

k번에 걸쳐 술래잡기를 진행하는 동안 술래가 총 얻게된 점수를 출력
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
using namespace std;

const int MAXN = 99;

int n, m, h, k;
int catcher_x, catcher_y, catcher_dir; // 술래
int is_clock;
int clock_dir[MAXN + 10][MAXN + 10];
int counter_clock_dir[MAXN + 10][MAXN + 10];
int score;

vector<int> grid[MAXN + 10][MAXN + 10]; // 도망자
vector<int> next_grid[MAXN + 10][MAXN + 10]; // 도망자
int tree[MAXN + 10][MAXN + 10]; // 나무

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void print() {
	cout << "catcher : " << catcher_x << " " << catcher_y << " " << catcher_dir << "\n";
	cout << "grid" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cout << "{ ";
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				cout << grid[x][y][i] << " ";
			}
			cout << "} ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "score : " << score << "\n";
}

void setClockDir() {
	int cx = n / 2;
	int cy = n / 2;
	int dist = 1;
	int dir = 0;

	while (1) {
		for (int cnt = 0; cnt < 2; cnt++) {
			for (int i = 0; i < dist; i++) {
				clock_dir[cx][cy] = dir;
				cx += dx[dir];
				cy += dy[dir];

				if (cx == 0 && cy == 0) return;
			}
			dir = (dir + 1) % 4;
		}
		dist++;
	}
}

void setCounterClockDir() {
	for (int i = 0; i < n - 1; i++) {
		counter_clock_dir[i][0] = 2;
	}

	int cx = n - 1;
	int cy = 0;
	int dir = 1;
	int dist = 4;

	while (1) {
		for (int cnt = 0; cnt < 2; cnt++) {
			for (int i = 0; i < dist; i++) {
				counter_clock_dir[cx][cy] = dir;
				cx += dx[dir];
				cy += dy[dir];

				if (cx == n / 2 && cy == n / 2) return;
			}
			dir = (dir + 3) % 4;
		}
		dist--;
	}
}

int getDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

bool inRange(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < n);
}

tuple<int, int, int> getNextPos(int x, int y, int dir) {
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	if (inRange(nx, ny)) {
		if (nx == catcher_x && ny == catcher_y) return make_tuple(x, y, dir);
		else return make_tuple(nx, ny, dir);
	}
	else {
		dir = (dir + 2) % 4;
		nx = x + dx[dir];
		ny = y + dy[dir];
		if (nx == catcher_x && ny == catcher_y) return make_tuple(x, y, dir);
		else return make_tuple(nx, ny, dir);
	}
}

void moveRunner() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y].clear();
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (grid[x][y].empty()) continue;
			if (getDist(x, y, catcher_x, catcher_y) > 3) continue;

			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				int nx, ny, nd;
				tie(nx, ny, nd) = getNextPos(x, y, grid[x][y][i]);
				next_grid[nx][ny].push_back(nd);
			}
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y].clear();
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int i = 0; i < (int)next_grid[x][y].size(); i++) {
				grid[x][y].push_back(next_grid[x][y][i]);
			}
		}
	}
}

void moveCatcher() {
	int dir;
	if (is_clock) {
		dir = clock_dir[catcher_x][catcher_y];
		catcher_x += dx[dir];
		catcher_y += dy[dir];
		catcher_dir = clock_dir[catcher_x][catcher_y];

		if (catcher_x == 0 && catcher_y == 0) catcher_dir = 2;
	}
	else {
		dir = counter_clock_dir[catcher_x][catcher_y];
		catcher_x += dx[dir];
		catcher_y += dy[dir];
		catcher_dir = counter_clock_dir[catcher_x][catcher_y];

		if (catcher_x == n / 2 && catcher_y == n / 2) catcher_dir = 0;
	}
}

/*
이동 직후 술래는 턴을 넘기기 전에 시야 내에 있는 도망자를 잡음
술래의 시야는 현재 바라보고 있는 방향을 기준으로 현재 칸을 포함하여 3칸
격자 크기에 상관없이 술래의 시야는 항상 3칸임에 유의
하지만 만약 나무가 놓여 있는 칸이라면, 해당 칸에 있는 도망자는 나무에 가려져 보이지 않게 됨. 그 뒤에 있는 3칸 안에 있는 도망자는 잡힘
잡힌 도망자는 사라지게 되고, 술래는 현재 턴을 t번째 턴이라고 했을 때 t x (현재 턴에서 잡힌 도망자의 수) 만큼의 점수를 얻게 됨
*/
void catchRunner(int turn) {
	int cx = catcher_x;
	int cy = catcher_y;
	int cd = catcher_dir;

	for (int dist = 0; dist < 3; dist++) {
		int nx = cx + dx[cd] * dist;
		int ny = cy + dy[cd] * dist;
		if (!inRange(nx, ny)) continue;
		if (grid[nx][ny].empty()) continue;
		if (tree[nx][ny] == 1) continue;
		int sz = grid[nx][ny].size();
		score += turn * sz;
		grid[nx][ny].clear();
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> n >> m >> h >> k;
	catcher_x = n / 2; catcher_y = n / 2; catcher_dir = 0;
	setClockDir();
	cout << "clock_dir" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cout << clock_dir[x][y] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	setCounterClockDir();
	cout << "counter_clock_dir" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cout << counter_clock_dir[x][y] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	is_clock = true;

	for (int i = 0; i < m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		x--; y--;
		grid[x][y].push_back(d);
	}
	for (int i = 0; i < h; i++) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		tree[x][y] = 1;
	}

	//print();

	for (int turn = 1; turn <= k; turn++) {
		//cout << "turn : " << turn << "\n";

		//cout << "moveRunner" << "\n";
		moveRunner();
		//print();

		//cout << "moveCatcher" << "\n";
		moveCatcher();
		//print();

		//cout << "catchRunner" << "\n";
		catchRunner(turn);
		//print();
	}

	cout << score << "\n";
	return 0;
}