#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;

#define MAX_N 10
#define DIR_NUM 4
int n, m, k;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];

vector<pair<int, int>> runner;
vector<pair<int, int>> next_runner;

int exit_x, exit_y;
int ans = 0;

int dx[DIR_NUM] = { -1, 1, 0, 0 }; // 상하좌우
int dy[DIR_NUM] = { 0, 0, -1, 1 };

bool InRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

bool IsShort(int x, int y, int nx, int ny) {
	return (abs(exit_x - x) + abs(exit_y - y)) > (abs(exit_x - nx) + abs(exit_y - ny));
}

pair<int, int> MoveRunner(int x, int y) {
	if (exit_x != x) {
		int nx = x, ny = y;
		if (exit_x < nx) nx--;
		else nx++;

		if (grid[nx][ny] == 0) {
			ans++;
			return { nx, ny };
		}
	}

	if (exit_y != y) {
		int nx = x, ny = y;
		if (exit_y < ny) ny--;
		else ny++;

		if (grid[nx][ny] == 0) {
			ans++;
			return { nx, ny };
		}
	}

	return { x, y };
}

void MoveAllRunner() {
	next_runner.clear();

	for (int i = 0; i < (int)runner.size(); i++) {
		int x = runner[i].first;
		int y = runner[i].second;
		int nx, ny;
		tie(nx, ny) = MoveRunner(x, y);
		if (!(nx == exit_x && ny == exit_y)) {
			next_runner.push_back({ nx, ny });
		}
	}

	runner = next_runner;
}

tuple<int, int, int> FindMinSquare() {
	for (int sz = 2; sz <= n; sz++) {
		for (int sx = 0; sx < n - sz; sx++) {
			for (int sy = 0; sy < n - sz; sy++) {
				int ex = sx + sz - 1, ey = sy + sz - 1;
				if(!(sx <= exit_x && exit_x <= ex && sy <= exit_y && exit_y <= ey)) continue;

				bool is_possible = false;
				for (int i = 0; i < (int)runner.size(); i++) {
					int rx = runner[i].first, ry = runner[i].second;
					if (sx <= rx && rx <= ex && sy <= ry && ry <= ey) {
						is_possible = true;
						break;
					}
				}

				if (is_possible) {
					return { sx, sy, sz };
				}
			}
		}
	}
	return { n, n, 1 };
}

void RotateGrid() {
	int sx, sy, sz;
	tie(sx, sy, sz) = FindMinSquare();

	if (sx == n && sy == n && sz == 1) return;

	// 출구 회전
	exit_x -= sx, exit_y -= sy;
	int tmp = exit_x;
	exit_x  = exit_y, exit_y = sz - 1 - tmp;
	exit_x += sx, exit_y += sy;

	// 참가자 회전
	next_runner.clear();
	for (int i = 0; i < (int)runner.size(); i++) {
		int x = runner[i].first, y = runner[i].second;
		if (sx <= x && x <= sx + sz - 1 && sy <= y && y <= sy + sz - 1) {
			 x -= sx, y -= sy;
			 int tmp = x;
			 int nx = y, ny = sz - 1 - tmp;
			 nx += sx, ny += sy;
			 next_runner.push_back({ nx, ny });
		}
		else {
			next_runner.push_back({ x, y });
		}
	}
	runner = next_runner;

	// 미로 회전
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y] = 0;
		}
	}

	for (int x = sx; x < sx + sz; x++) {
		for (int y = sy; y < sy + sz; y++) {
			int nx = x - sx, ny = y - sy;
			int tmp = nx;
			nx = ny, ny = sz - 1 - tmp;
			nx += sx, ny += sy;
			if (grid[x][y] > 0) {
				next_grid[nx][ny] = grid[x][y] - 1;
			}
			else {
				next_grid[nx][ny] = grid[x][y];
			}
		}
	}

	for (int x = sx; x < sx + sz; x++) {
		for (int y = sy; y < sy + sz; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void Print() {
	cout << "====================\n";
	cout << "runner\n";
	for (int i = 0; i < (int)runner.size(); i++) {
		cout << runner[i].first << " " << runner[i].second << "\n";
	}
	cout << "grid\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "====================\n";
	cout << exit_x << " " << exit_y << "\n";
}

void Simulate() {
	//Print();
	MoveAllRunner();
	//Print();
	RotateGrid();
	//Print();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		int r, c;
		cin >> r >> c;
		r--, c--;
		runner.push_back({ r, c });
	}
	cin >> exit_x >> exit_y;
	exit_x--, exit_y--;

	while (k--) {
		if(runner.empty()) break;
		Simulate();
	}
	
	cout << ans << "\n" << exit_x + 1 << " " << exit_y + 1 << "\n";
	return 0;
}