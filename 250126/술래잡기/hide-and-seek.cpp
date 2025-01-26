#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 99
#define DIR_NUM 4

int n, m, h, k;
int catcher_x, catcher_y, catcher_dir;
vector<int> grid[MAX_N + 1][MAX_N + 1];
vector<int> next_grid[MAX_N + 1][MAX_N + 1];
bool tree[MAX_N + 1][MAX_N + 1];

bool is_clock;
int clock_dir[MAX_N + 1][MAX_N + 1];
int counter_clock_dir[MAX_N + 1][MAX_N + 1];

int ans;

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

void print() {
	cout << "CATCHER POS : " << catcher_x << " " << catcher_y << "\n";
	cout << "CATCHER DIR : " << catcher_dir << "\n";

	cout << "GRID" << "\n";
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			cout << " { ";
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				cout << grid[x][y][i] << " ";
			}
			cout << "} ";
		}
		cout << "\n";
	}
	cout << "TREE" << "\n";
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			if (tree[x][y]) cout << 1 << " ";
			else cout << 0 << " ";
		}
		cout << "\n";
	}

	cout << "ANS : " << ans << "\n";
}

int getDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

bool inRange(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

tuple<int, int, int> getNextPos(int x, int y, int d) {
	int nx = x + dx[d], ny = y + dy[d], nd = d;
	if (inRange(nx, ny)) {
		if (nx == catcher_x && ny == catcher_y) return make_tuple(x, y, nd);
		else return make_tuple(nx, ny, nd);
	}
	else {
		nd = (d + 2) % DIR_NUM;
		nx = x + dx[nd], ny = y + dy[nd];
		if (nx == catcher_x && ny == catcher_y) return make_tuple(x, y, nd);
		else return make_tuple(nx, ny, nd);
	}
}

void moveAllRunner() {
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			next_grid[x][y].clear();
		}
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			if (getDist(x, y, catcher_x, catcher_y) > 3) {
				for (int i = 0; i < (int)grid[x][y].size(); i++) {
					next_grid[x][y].push_back(grid[x][y][i]);
				}
				continue;
			}

			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				int nx, ny, nd;
				tie(nx, ny, nd) = getNextPos(x, y, grid[x][y][i]);
				next_grid[nx][ny].push_back(nd);
			}
		}
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			grid[x][y].clear();
		}
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			for (int i = 0; i < (int)next_grid[x][y].size(); i++) {
				grid[x][y].push_back(next_grid[x][y][i]);
			}
		}
	}
}

void setClockDir() {
	int cx = (n + 1) / 2, cy = (n + 1) / 2;
	int dir = 0, dist = 1;

	while (1) {
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

void setCounterClockDir() {
	for (int i = 1; i <= n; i++) {
		counter_clock_dir[i][1] = 2;
	}
	int cx = n, cy = 1;
	int dir = 1, dist = n - 1;
	while (1) {
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

void moveCatcher() {
	catcher_x += dx[catcher_dir], catcher_y += dy[catcher_dir];
	if (catcher_x == 1 && catcher_y == 1) {
		is_clock = false;
		catcher_dir = 2;
		return;
	}
	if (catcher_x == (n + 1) / 2 && catcher_y == (n + 1) / 2) {
		is_clock = true;
		catcher_dir = 0;
		return;
	}

	if (is_clock) {
		catcher_dir = clock_dir[catcher_x][catcher_y];
	}
	else {
		catcher_dir = counter_clock_dir[catcher_x][catcher_y];
	}
}

void catchRunner(int turn) {
	int cnt = 0;
	int cx = catcher_x, cy = catcher_y, cd = catcher_dir;

	for (int dist = 0; dist < 3; dist++) {
		int nx = cx + dx[cd] * dist, ny = cy + dy[cd] * dist;
		if (!inRange(nx, ny) || tree[nx][ny] || grid[nx][ny].empty()) continue;
		cnt += (int)grid[nx][ny].size();
		grid[nx][ny].clear();
	}

	ans += cnt * turn;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);

	cin >> n >> m >> h >> k;

	catcher_x = (n + 1) / 2, catcher_y = (n + 1) / 2, catcher_dir = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			grid[i][j].clear();
			tree[i][j] = false;
		}
	}
	ans = 0;
	is_clock = true;
	setClockDir();
	setCounterClockDir();

	for (int i = 1; i <= m; i++) {
		int x, y, d; cin >> x >> y >> d;
		grid[x][y].push_back(d);
	}

	for (int i = 1; i <= h; i++) {
		int x, y; cin >> x >> y;
		tree[x][y] = true;
	}

	
	for (int i = 1; i <= k; i++) {
		
		moveAllRunner();
		

		moveCatcher();
		

		catchRunner(i);
		
	}

	cout << ans << "\n";
	return 0;
}