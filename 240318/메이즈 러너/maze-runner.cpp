#include <iostream>
#include <tuple>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAX_N 10
#define MAX_M 10

int n, m, k;
int ex, ey;
int sx, sy, square_size;
int ans = 0;

int grid[MAX_N + 1][MAX_N + 1];
int next_grid[MAX_N + 1][MAX_N + 1];
pair<int, int> runner[MAX_M + 1];

void MoveAll() {
	for (int i = 1; i <= m; i++) {
		if (runner[i].first == ex && runner[i].second == ey) continue;
		
		if (runner[i].first != ex) {
			int nx = runner[i].first;
			int ny = runner[i].second;

			if (ex > nx) nx++;
			else nx--;

			if (!grid[nx][ny]) {
				runner[i].first = nx;
				runner[i].second = ny;
				ans++;
				continue;
			}
		}

		if (runner[i].second != ey) {
			int nx = runner[i].first;
			int ny = runner[i].second;

			if (ey > ny) ny++;
			else ny--;

			if (!grid[nx][ny]) {
				runner[i].first = nx;
				runner[i].second = ny;
				ans++;
				continue;
			}
		}
	}
}

void FindMinSquare() {
	for (int sz = 2; sz <= n; sz++) {
		for (int x1 = 1; x1 <= n - sz + 1; x1++) {
			for (int y1 = 1; y1 <= n - sz + 1; y1++) {
				int x2 = x1 + sz - 1;
				int y2 = y1 + sz - 1;

				if (!(x1 <= ex && ex <= x2 && y1 <= ey && ey <= y2)) continue;

				bool is_possible = false;
				for (int i = 1; i <= m; i++) {
					int rx = runner[i].first;
					int ry = runner[i].second;
					if (x1 <= rx && rx <= x2 && y1 <= ry && ry <= y2) {
						if (!(ex == rx && ey == ry)) is_possible = true;
					}
				}

				if (is_possible) {
					sx = x1;
					sy = y1;
					square_size = sz;
					return;
				}
			}
		}
	}
}

void RotateGrid() {
	for (int x = sx; x <= sx + square_size - 1; x++) {
		for (int y = sy; y <= sy + square_size - 1; y++) {
			if (grid[x][y]) grid[x][y]--;
		}
	}

	for (int x = sx; x <= sx + square_size - 1; x++) {
		for (int y = sy; y <= sy + square_size - 1; y++) {
			int ox = x - sx, oy = y - sy;
			int rx = oy, ry = square_size - 1 - ox;
			next_grid[rx + sx][ry + sy] = grid[x][y];
		}
	}

	for (int x = sx; x <= sx + square_size - 1; x++) {
		for (int y = sy; y <= sy + square_size - 1; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void RotateRunnerAndExit() {
	for (int i = 1; i <= m; i++) {
		int x = runner[i].first;
		int y = runner[i].second;
		if (sx <= x && x <= sx + square_size - 1 && sy <= y && y <= sy + square_size - 1) {
			int ox = x - sx, oy = y - sy;
			int rx = oy, ry = square_size - 1 - ox;
			runner[i] = make_pair(rx + sx, ry + sy);
		}
	}

	if (sx <= ex && ex <= sx + square_size - 1 && sy <= ey && ey <= sy + square_size - 1) {
		int ox = ex - sx, oy = ey - sy;
		int rx = oy, ry = square_size - 1 - ox;
		ex = rx + sx, ey = ry + sy;
	}
}

void Print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "-------------------------------\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= m; i++) {
		cin >> runner[i].first;
		cin >> runner[i].second;
	}

	cin >> ex >> ey;

	while (k--) {
		MoveAll();
		Print();

		bool is_possible = true;
		for (int i = 1; i <= m; i++) {
			if (!(ex == runner[i].first && ey == runner[i].second)) {
				is_possible = false;
			}
		}

		if (is_possible) break;

		FindMinSquare();
		Print();

		RotateGrid();
		Print();

		RotateRunnerAndExit();
		Print();
	}

	cout << ans << "\n";
	cout << ex << " " << ey << "\n";
	return 0;
}