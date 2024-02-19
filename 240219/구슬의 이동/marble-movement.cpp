#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

typedef tuple <int, int, int> Marble;

#define MAX_N 50
#define DIR_NUM 4
#define ASCII_NUM 128

int n, m, t, k;

int mapper[ASCII_NUM];
int dx[DIR_NUM] = {-1, 0, 1, 0};
int dy[DIR_NUM] = {0, 1, 0, -1};

vector<Marble> grid[MAX_N][MAX_N];
vector<Marble> next_grid[MAX_N][MAX_N];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

Marble GetNextPos(int x, int y, int v, int dir) {
	while (v--) {
		int nx = x + dx[dir], ny = y + dy[dir];
		if (!InRange(nx, ny)) {
			dir = (dir + 2) % 4;
			nx = x + dx[dir], ny = y + dy[dir];
		}
		x = nx; y = ny;
	}
	return Marble(x, y, dir);
}

void MoveAll() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int i = 0; i < grid[x][y].size(); i++) {
				int v, num, dir;
				tie(v, num, dir) = grid[x][y][i];

				int nx, ny, ndir;
				tie(nx, ny, ndir) = GetNextPos(x, y, -v, dir);
				next_grid[nx][ny].push_back(make_tuple(v, num, ndir));
			}
		}
	}
}

void SelectMarbles() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (next_grid[x][y].size() > k) {
				sort(next_grid[x][y].begin(), next_grid[x][y].end());
				while ((int)next_grid[x][y].size() > k) next_grid[x][y].pop_back();
			}
		}
	}
}

void Simulate() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y].clear();
		}
	}

	MoveAll();
	SelectMarbles();

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

int CountRemainMarbles() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cnt += (int)grid[i][j].size();
		}
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> t >> k;
	mapper['U'] = 0;
	mapper['R'] = 1;
	mapper['D'] = 2;
	mapper['L'] = 3;
	for (int i = 1; i <= m; i++) {
		int r, c, v; char d;
		cin >> r >> c >> d >> v;
		grid[r - 1][c - 1].push_back(make_tuple(-v, -i, mapper[d]));
	}

	while (t--) Simulate();

	cout << CountRemainMarbles() << "\n";
	return 0;
}