#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

#define MAX 50
#define DIR_NUM 4

int n, m, t;
int grid[MAX][MAX];
int next_grid[MAX][MAX];

int dx[DIR_NUM] = { -1, 0, 1, 0 };
int dy[DIR_NUM] = { 0, 1, 0, -1 };

vector<pair<int, int>> cleaner;

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

void SpreadDust() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			next_grid[x][y] = 0;
		}
	}
	
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			if (grid[x][y] == -1 || grid[x][y] == 0) continue;
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = x + dx[dir];
				int ny = y + dy[dir];
				if (!InRange(nx, ny) || grid[nx][ny] == -1) continue;
				next_grid[nx][ny] += grid[x][y] / 5;
				next_grid[x][y] -= grid[x][y] / 5;
			}

		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			grid[x][y] += next_grid[x][y];
		}
	}
}

void CleanDust() {
	int clear_x = cleaner[0].first;
	int clear_y = cleaner[0].second;

	for (int x = clear_x - 1; x > 0; x--) {
		grid[x][0] = grid[x - 1][0];
	}
	for (int y = 0; y < m - 1; y++) {
		grid[0][y] = grid[0][y + 1];
	}
	for (int x = 0; x < clear_x; x++) {
		grid[x][m - 1] = grid[x + 1][m - 1];
	}
	for (int y = m - 1; y > 1; y--) {
		grid[clear_x][y] = grid[clear_x][y - 1];
	}
	grid[clear_x][1] = 0;

	clear_x = cleaner[1].first;
	clear_y = cleaner[1].second;

	for (int x = clear_x + 1; x < n - 1; x++) {
		grid[x][0] = grid[x + 1][0];
	}
	for (int y = 0; y < m - 1; y++) {
		grid[n - 1][y] = grid[n - 1][y + 1];
	}
	for (int x = n - 1; x > clear_x; x--) {
		grid[x][m - 1] = grid[x - 1][m - 1];
	}
	for (int y = m - 1; y > 1; y--) {
		grid[clear_x][y] = grid[clear_x][y - 1];
	}
	grid[clear_x][1] = 0;
}

void Simulate() {
	SpreadDust();
	CleanDust();
}

int CountDust() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] != -1)
				ans += grid[i][j];
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m >> t;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == -1) {
				cleaner.push_back({ i, j });
			}
		}
	}

	while (t--) {
		Simulate();
	}

	cout << CountDust() << "\n";
	return 0;
}