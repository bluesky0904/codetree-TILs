#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 50
#define DIR_NUM 4
#define ASCII_NUM 128

typedef tuple<int, int, int> Marble;

int n, m, t, k;
vector<Marble> grid[MAX_N][MAX_N];
vector<Marble> next_grid[MAX_N][MAX_N];
int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};
int dir_mapper[ASCII_NUM];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

tuple<int, int, int> NextPos(int x, int y, int v, int dir) {
	while (v--) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (!InRange(nx, ny)) dir = (dir + 2) % 4;
		x += dx[dir];
		y += dy[dir];
	}
	return make_tuple(x, y, dir);
}

void MoveAll() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int i = 0; i < grid[x][y].size(); i++) {
				int v, num, dir;
				tie(v, num, dir) = grid[x][y][i];
				int nx, ny, ndir;
				tie(nx, ny, ndir) = NextPos(x, y, -v, dir);
				next_grid[nx][ny].push_back(make_tuple(v, num, ndir));
			}
		}
	}
}

void SelectMarbles() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sort(next_grid[i][j].begin(), next_grid[i][j].end());
			while (next_grid[i][j].size() > k) {
				next_grid[i][j].pop_back();
			}
		}
	}
}

void Simulate() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j].clear();
		}
	}

	MoveAll();

	SelectMarbles();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> t >> k;

	dir_mapper['U'] = 0;
	dir_mapper['R'] = 1;
	dir_mapper['D'] = 2;
	dir_mapper['L'] = 3;
	for (int i = 0; i < m; i++) {
		int r, c, v; char d; cin >> r >> c >> d >> v;
		grid[r - 1][c - 1].push_back(make_tuple(-v,-(i+1), dir_mapper[d]));
	}

	while (t--) Simulate();

	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans += grid[i][j].size();
		}
	}
	cout << ans << "\n";
}