#include <iostream>
using namespace std;

#define MAX_N 10

int n, m, k;
int ex, ey;
int sx, sy, square_size;
int ans = 0;

int miro[MAX_N + 1][MAX_N + 1];
int next_miro[MAX_N + 1][MAX_N + 1];
pair<int, int> runner[MAX_N + 1];

void MoveAll() {
	for (int i = 1; i <= m; i++) {
		if (ex == runner[i].first && ey == runner[i].second) continue;

		if (ex != runner[i].first) {
			int nx = runner[i].first, ny = runner[i].second;
			if (ex < nx) nx--;
			else nx++;

			if (miro[nx][ny] == 0) {
				runner[i].first = nx;
				runner[i].second = ny;
				ans++;
				continue;
			}
		}

		if (ey != runner[i].second) {
			int nx = runner[i].first, ny = runner[i].second;
			if (ey < ny) ny--;
			else ny++;

			if (miro[nx][ny] == 0) {
				runner[i].first = nx;
				runner[i].second = ny;
				ans++;
				continue;
			}
		}
	}
}

void GetRec() {
	for (int sz = 2; sz <= n; sz++) {
		for (int x1 = 1; x1 <= n - sz + 1; x1++) {
			for (int y1 = 1; y1 <= n - sz + 1; y1++) {
				int x2 = x1 + sz - 1, y2 = y1 + sz - 1;
				if (!(x1 <= ex && ex <= x2 && y1 <= ey && ey <= y2)) continue;

				bool is_possible = false;
				for (int i = 1; i <= m; i++) {
					int rx = runner[i].first, ry = runner[i].second;
					if (x1 <= rx && rx <= x2 && y1 <= ry && ry <= y2) {
						if (!(rx == ex && ry == ey)) {
							is_possible = true;
							break;
						}
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

void RotateMiro() {
	for (int x = sx; x <= sx + square_size - 1; x++) {
		for (int y = sy; y <= sy + square_size - 1; y++) {
			if (miro[x][y]) miro[x][y]--;
		}
	}

	for (int x = sx; x <= sx + square_size - 1; x++) {
		for (int y = sy; y <= sy + square_size - 1; y++) {
			int ox = x - sx, oy = y - sy;
			int rx = oy, ry = square_size - 1 - ox;
			next_miro[rx + sx][ry + sy] = miro[x][y];
		}
	}

	for (int x = sx; x <= sx + square_size - 1; x++) {
		for (int y = sy; y <= sy + square_size - 1; y++) {
			miro[x][y] = next_miro[x][y];
		}
	}
}

void RotateRunnerAndExit() {
	for (int i = 1; i <= m; i++) {
		int x = runner[i].first, y = runner[i].second;
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
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			cout <<  miro[x][y] << " ";
		}
		cout << "\n";
	}
	cout << ans << "\n";
	cout << "-----------------------------\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> miro[i][j];
		}
	}

	for (int i = 1; i <= m; i++) {
		int r, c;
		cin >> r >> c;
		runner[i] = make_pair(r, c);
	}
	cin >> ex >> ey;

	while (k--) {
		MoveAll();
		Print();

		bool is_possible = true;
		for (int i = 1; i <= m; i++) {
			if (!(ex == runner[i].first && ey == runner[i].second)) is_possible = false;
		}

		if (is_possible) break;

		GetRec();

		RotateMiro();
		Print();

		RotateRunnerAndExit();
		Print();
	}
	cout << ans << "\n";
	cout << ex << " " << ey << "\n";
	return 0;
}