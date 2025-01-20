#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <cmath>
#include <tuple>
using namespace std;

#define MAX_N 10
#define MAX_M 10
#define DIR_NUM 4

int n, m, k;
int ans;
int grid[MAX_N + 1][MAX_N + 1];
int next_grid[MAX_N + 1][MAX_N + 1];

pair<int, int> exit_pos;
pair<int, int> runner[MAX_M + 1];
bool is_live[MAX_M + 1];

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool isAllExit() {
	for (int i = 1; i <= m; i++) {
		if (is_live[i]) return false;
	}
	return true;
}

int GetDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

bool inRange(int x, int y) {
	return (x >= 1 && x <= n && y >= 1 && y <= n);
}

void moveAllRunner() {
	int ex = exit_pos.first, ey = exit_pos.second;

	for (int i = 1; i <= m; i++) {
		if (!is_live[i]) continue;
		
		int cx = runner[i].first, cy = runner[i].second;

		int nx = cx + dx[0], ny = cy + dy[0];
		int next_dist = GetDist(nx, ny, ex, ey);
		if (inRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(cx, cy, ex, ey) > next_dist)) {
			runner[i] = { nx, ny };
			ans++;
			if (next_dist == 0) is_live[i] = false;
			continue;
		}

		nx = cx + dx[2], ny = cy + dy[2];
		next_dist = GetDist(nx, ny, ex, ey);
		if (inRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(cx, cy, ex, ey) > next_dist)) {
			runner[i] = { nx, ny };
			ans++;
			if (next_dist == 0) is_live[i] = false;
			continue;
		}

		nx = cx + dx[1], ny = cy + dy[1];
		next_dist = GetDist(nx, ny, ex, ey);
		if (inRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(cx, cy, ex, ey) > next_dist)) {
			runner[i] = { nx, ny };
			ans++;
			if (next_dist == 0) is_live[i] = false;
			continue;
		}

		nx = cx + dx[3], ny = cy + dy[3];
		next_dist = GetDist(nx, ny, ex, ey);
		if (inRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(cx, cy, ex, ey) > next_dist)) {
			runner[i] = { nx, ny };
			ans++;
			if (next_dist == 0) is_live[i] = false;
			continue;
		}
	}
}

tuple<int, int, int> selectRec() {
	int ex = exit_pos.first, ey = exit_pos.second;

	for (int size = 2; size <= n; size++) {
		for (int row = 1; row <= n - size + 1; row++) {
			for (int col = 1; col <= n - size + 1; col++) {
				if (!(row <= ex && ex <= row + size - 1 && col <= ey && ey <= col + size - 1)) continue;

				bool is_runner_in = false;
				for (int i = 1; i <= m; i++) {
					int cx = runner[i].first, cy = runner[i].second;

					if (!is_live[i]) continue;
					if (row <= cx && cx <= row + size - 1 && col <= cy && cy <= col + size - 1) {
						is_runner_in = true;
						break;
					}
				}

				if (is_runner_in) return make_tuple(size, row, col);
				else continue;
			}
		}
	}
	return make_tuple(-1, -1, -1);
}

void rotateGrid() {
	int rec_size, sx, sy;
	tie(rec_size, sx, sy) = selectRec();

	// 그리드 회전
	for (int x = sx; x <= sx + rec_size - 1; x++) {
		for (int y = sy; y <= sy + rec_size - 1; y++) {
			next_grid[x][y] = 0;
		}
	}

	for (int x = sx; x <= sx + rec_size - 1; x++) {
		for (int y = sy; y <= sy + rec_size - 1; y++) {
			if (grid[x][y] == 0) continue;

			int ox = x - sx + 1, oy = y - sy + 1;
			int rx = oy, ry = rec_size - ox + 1;
			next_grid[rx + sx - 1][ry + sy - 1] = grid[x][y] - 1;
		}
	}

	for (int x = sx; x <= sx + rec_size - 1; x++) {
		for (int y = sy; y <= sy + rec_size - 1; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}

	// 출구 회전
	int ox = exit_pos.first - sx + 1, oy = exit_pos.second - sy + 1;
	int rx = oy, ry = rec_size - ox + 1;
	exit_pos = { rx + sx - 1, ry + sy - 1};

	// 러너 회전
	for (int i = 1; i <= m; i++) {
		int cx = runner[i].first, cy = runner[i].second;

		if (!is_live[i]) continue;
		if (sx <= cx && cx <= sx + rec_size - 1 && sy <= cy && cy <= sy + rec_size - 1) {
			int ox = cx - sx + 1, oy = cy - sy + 1;
			int rx = oy, ry = rec_size - ox + 1;
			runner[i] = { rx + sx - 1, ry + sy - 1};
		}
	}
}

void print() {
	cout << "GRID" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "RUNNERS" << "\n";
	for (int i = 1; i <= m; i++) {
		cout << i << " : " << runner[i].first << " " << runner[i].second << "\n";
	}
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}
	
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		runner[i] = { x, y };
		is_live[i] = true;
	}

	cin >> exit_pos.first >> exit_pos.second;

	ans = 0;
	for (int t = 1; t <= k; t++) {
		if (isAllExit()) break;
		moveAllRunner();
		
		rotateGrid();
		
	}

	
	cout << ans << "\n";
	cout << exit_pos.first << " " << exit_pos.second << "\n";
	return 0;
}