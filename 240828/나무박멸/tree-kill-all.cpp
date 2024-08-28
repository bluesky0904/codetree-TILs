#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <tuple>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4
#define DIAG_DIR_NUM 4

int n, m, k, c;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];
int herbicide[MAX_N][MAX_N];
int ans = 0;

int dx[DIR_NUM] = { -1, 0, 1, 0};
int dy[DIR_NUM] = { 0, 1, 0, -1};

int dx_diag[DIAG_DIR_NUM] = { -1, -1, 1, 1 };
int dy_diag[DIAG_DIR_NUM] = { -1, 1, 1, -1 };

bool InRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

void GrowTree() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = 0;
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (grid[x][y] > 0) {
				int cnt = 0;
				for (int dir = 0; dir < DIR_NUM; dir++) {
					int nx = x + dx[dir], ny = y + dy[dir];
					if (InRange(nx, ny) && grid[nx][ny] > 0) cnt++;
				}
				next_grid[x][y] = grid[x][y] + cnt;
			}
			else if (grid[x][y] == -1) next_grid[x][y] = grid[x][y];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

void ReproduceTree() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = 0;
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (grid[x][y] > 0) {
				next_grid[x][y] = grid[x][y];

				int cnt = 0;
				for (int dir = 0; dir < DIR_NUM; dir++) {
					int nx = x + dx[dir], ny = y + dy[dir];
					if (InRange(nx, ny) && grid[nx][ny] == 0 && herbicide[nx][ny] == 0) cnt++;
				}
				if (cnt > 0) {
					for (int dir = 0; dir < DIR_NUM; dir++) {
						int nx = x + dx[dir], ny = y + dy[dir];
						if (InRange(nx, ny) && grid[nx][ny] == 0 && herbicide[nx][ny] == 0)
							next_grid[nx][ny] += grid[x][y] / cnt;
					}
				}
			}
			else if (grid[x][y] == -1) next_grid[x][y] = grid[x][y];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

pair<int, int> FindMaxPos() {
	int max_val = 0;
	int mx = -1, my = -1;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (grid[x][y] > 0) {
				int val = grid[x][y];
				for (int dir = 0; dir < DIAG_DIR_NUM; dir++) {
					for (int i = 1; i <= k; i++) {
						int nx = x + dx_diag[dir] * i, ny = y + dy_diag[dir] * i;
						if (InRange(nx, ny) && grid[nx][ny] >= 0)
							val += grid[nx][ny];
						else break;
					}
				}
				if (max_val < val) {
					max_val = val;
					mx = x, my = y;
				}
			}
		}
	}
	return { mx, my };
}

void RemoveTree() {
	int x, y;
	tie(x, y) = FindMaxPos();
	int val = grid[x][y];
	herbicide[x][y] = c + 1;
	grid[x][y] = 0;
	for (int dir = 0; dir < DIAG_DIR_NUM; dir++) {
		for (int i = 1; i <= k; i++) {
			int nx = x + dx_diag[dir] * i, ny = y + dy_diag[dir] * i;
			if (InRange(nx, ny) && grid[nx][ny] >= 0) {
				val += grid[nx][ny];
				grid[nx][ny] = 0;
				herbicide[nx][ny] = c + 1;
			}
			else break;
		}
	}

	ans += val;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (herbicide[i][j] > 0)
				herbicide[i][j]--;
		}
	}
}

void Print() {
	cout << "====================\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}

void Simulate() {
	//Print();
	GrowTree();
	//Print();
	ReproduceTree();
	//Print();
	RemoveTree();
	//Print();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m >> k >> c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	while (m--) Simulate();

	cout << ans << "\n";
	return 0;
}