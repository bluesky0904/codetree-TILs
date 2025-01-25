#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
using namespace std;

#define MAX_N 99
#define DIR_NUM 4

int n, m, h, k;
int catcher_x, catcher_y, catcher_d;
vector<int> grid[MAX_N + 1][MAX_N + 1]; // runner들의 위치 관리
vector<int> next_grid[MAX_N + 1][MAX_N + 1]; // runner들의 위치 관리
bool tree[MAX_N + 1][MAX_N];

bool is_clock;
int clock_dir[MAX_N + 1][MAX_N + 1];
int counter_clock_dir[MAX_N + 1][MAX_N + 1];

int ans;

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

void print() {
	cout << "CATCHER_POS : " << catcher_x << " " << catcher_y << "\n";
	cout << "CATCHER_DIR : " << catcher_d << "\n";
	cout << "GRID" << "\n";
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			cout << "{ ";
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				cout << grid[x][y][i] << " ";
			}
			cout << " } ";
		}
		cout << "\n";
	}
	cout << "TREE" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (tree[i][j]) cout << 1 << " ";
			else cout << 0 << " ";
		}
		cout << "\n";
	}
	cout << "ANS : " << ans << "\n";
}

void setCatcherDir() {
	int cx = (n + 1) / 2, cy = (n + 1) / 2;
	int dir = 0, dist = 1;

	while (!(cx == 1 && cy == 1)) {
		for (int cnt = 1; cnt <= 2; cnt++) {
			for (int i = 1; i <= dist; i++) {
				clock_dir[cx][cy] = dir;
				cx += dx[dir], cy += dy[dir];

				if (cx == 1 && cy == 1) return;
			}
			dir = (dir + 1) % DIR_NUM;
		}
		dist++;
	}
}
/*
x 1 1 1 2
0 0 1 2 2
0 0 0 2 2
0 0 3 3 2
0 3 3 3 3
*/

void setCounterCatcherDir() {
	int cx = n, cy = 1;
	int dir = 1, dist = n - 1;

	for (int i = 1; i <= n - 1; i++) {
		counter_clock_dir[i][1] = 2;
	}

	while (!(cx == (n + 1) / 2 && cy == (n + 1) / 2)) {
		for (int cnt = 1; cnt <= 2; cnt++) {
			for (int i = 1; i <= dist; i++) {
				counter_clock_dir[cx][cy] = dir;
				cx += dx[dir], cy += dy[dir];

				if (cx == (n + 1) / 2 && cy == (n + 1) / 2) return;
			}
			dir = (dir + 3) % DIR_NUM;
		}
		dist--;
	}
}
/*
2 2 3 3 3
2 2 2 3 0
2 2 x 0 0
2 1 1 0 0
1 1 1 1 0
*/

bool inRange(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

int getDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

tuple<int, int, int> getNextPos(int x, int y, int d) {
	int nx = x + dx[d], ny = y + dy[d], nd = d;
	if (inRange(nx, ny)) {
		if (nx == catcher_x && ny == catcher_y) return make_tuple(x, y, nd);
		else return make_tuple(nx, ny, nd);
	}
	else {
		nd = (nd + 2) % DIR_NUM;
		nx = x + dx[nd], ny = y + dy[nd];
		if (nx == catcher_x && ny == catcher_y) return make_tuple(x, y, nd);
		else return make_tuple(nx, ny, nd);
	}
}

// 여기 분명 무슨 문제가 꼭 있음 시발!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void moveRunner() {
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			next_grid[x][y].clear();
		}
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			if (grid[x][y].empty()) continue;

			if (getDist(x, y, catcher_x, catcher_y) > 3) {
				for (int i = 0; i < (int)grid[x][y].size(); i++) {
					next_grid[x][y].push_back(grid[x][y][i]);
				}
			}
			else {
				for (int i = 0; i < (int)grid[x][y].size(); i++) {
					int nx, ny, nd;
					tie(nx, ny, nd) = getNextPos(x, y, grid[x][y][i]);
					next_grid[nx][ny].push_back(nd);
				}
			}
		}
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void moveCatcher() {
	if (is_clock) {
		catcher_x += dx[catcher_d], catcher_y += dy[catcher_d];
		catcher_d = clock_dir[catcher_x][catcher_y];
		if (catcher_x == 1 && catcher_y == 1) {
			is_clock = false;
			catcher_d = 2;
			return;
		}
	}
	else {
		catcher_x += dx[catcher_d], catcher_y += dy[catcher_d];
		catcher_d = counter_clock_dir[catcher_x][catcher_y];
		if (catcher_x == (n + 1) / 2 && catcher_y == (n + 1) / 2) {
			is_clock = true;
			catcher_d = 0;
			return;
		}
	}
}

void catchRunner(int turn) {
	int cnt = 0;
	int cx = catcher_x, cy = catcher_y, cd = catcher_d;
	for (int dist = 0; dist < 3; dist++) {
		int nx = cx + dx[cd] * dist, ny = cy + dy[cd] * dist;
		if (inRange(nx, ny) && !tree[nx][ny] && !grid[nx][ny].empty()) {
			cnt += (int)grid[nx][ny].size();
			grid[nx][ny].clear();
		}
	}

	if(cnt != 0) ans += (cnt * turn);
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);

	cin >> n >> m >> h >> k;

	ans = 0;
	catcher_x = (n + 1) / 2, catcher_y = (n + 1) / 2, catcher_d = 0;;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			grid[i][j].clear();
			tree[i][j] = false;
		}
	}

	is_clock = true;
	setCatcherDir();
	setCounterCatcherDir();

	for (int i = 1; i <= m; i++) {
		int x, y, d; cin >> x >> y >> d;

		if (d == 1) {
			grid[x][y].push_back(1);
		}
		else if(d == 2) {
			grid[x][y].push_back(2);
		}
	}

	for (int i = 1; i <= h; i++) {
		int x, y; cin >> x >> y;
		tree[x][y] = true;
	}

	//print();
	for (int i = 1; i <= k; i++) {
		//cout << "/////////////////// TURN : " << i  << " ///////////////////" << "\n";
		moveRunner();
		//print();

		moveCatcher();
		//print();
		
		catchRunner(i);
		//print();
	}

	cout << ans << "\n";
	return 0;
}
