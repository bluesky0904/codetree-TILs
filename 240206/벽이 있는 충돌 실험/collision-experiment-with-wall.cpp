#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 50
#define DIR_NUM 4
#define ASCII_NUM 128

int t, n, m;
vector<int> grid[MAX_N][MAX_N];
vector<int> next_grid[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};
int dir_mapper[ASCII_NUM];

void ClearGrid() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j].clear();
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

tuple<int, int, int> NextPos(int x, int y, int dir) {
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	if (!InRange(nx, ny)) {
		dir = (dir + 2) % 4;
		return make_tuple(x, y, dir);
	}
	return make_tuple(nx, ny, dir);
}

void MoveAll() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int i = 0; i < grid[x][y].size(); i++) {
				int dir = grid[x][y][i];
				int nx, ny, ndir;
				tie(nx, ny, ndir) = NextPos(x, y, dir);
				next_grid[nx][ny].push_back(ndir);
			}
		}
	}
}

void RemoveDuplicateMarbles() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (next_grid[i][j].size() > 1) next_grid[i][j].clear();
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

	RemoveDuplicateMarbles();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> t;
	dir_mapper['U'] = 0;
	dir_mapper['R'] = 1;
	dir_mapper['D'] = 2;
	dir_mapper['L'] = 3;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;

		ClearGrid();

		for (int i = 0; i < m; i++) {
			int x, y; char d; cin >> x >> y >> d;
			grid[x - 1][y - 1].push_back(dir_mapper[d]);
		}

		for (int i = 0; i < 2*n; i++) Simulate();

		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ans += grid[i][j].size();
			}
		}
		cout << ans << "\n";
	}
}