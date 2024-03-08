#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n;
int max_time = -1;

int grid[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1, 0, 1, 0};
int dy[DIR_NUM] = {0, 1, 0, -1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int Simulate(int x, int y, int dir) {
	int cnt = 1;
	int cx = x, cy = y;
	while (true) {
		int nx = cx + dx[dir], ny = cy + dy[dir];
		if (!InRange(nx, ny)) break;

		if (grid[nx][ny] == 0) {
			cnt++;
			cx = nx;
			cy = ny;
		}
		else if (grid[nx][ny] == 1) {
			cnt++;
			cx = nx;
			cy = ny;
			if (dir == 0) dir = 1;
			else if (dir == 1) dir = 0;
			else if (dir == 2) dir = 3;
			else if (dir == 3) dir = 2;
		}
		else if (grid[nx][ny] == 2) {
			cnt++;
			cx = nx;
			cy = ny;
			if (dir == 0) dir = 3;
			else if (dir == 1) dir = 2;
			else if (dir == 2) dir = 1;
			else if (dir == 3) dir = 0;
		}
	}
	return cnt + 1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 0; i < DIR_NUM; i++) {
		if (i == 0) {
			for (int col = 0; col < n; col++) {
				max_time = max(max_time, Simulate(n - 1, col, i));
			}
		}
		else if (i == 1) {
			for (int row = 0; row < n; row++) {
				max_time = max(max_time, Simulate(row, 0, i));
			}
		}
		else if (i == 2) {
			for (int col = 0; col < n; col++) {
				max_time = max(max_time, Simulate(0, col, i));
			}
		}
		else if (i == 3) {
			for (int row = 0; row < n; row++) {
				max_time = max(max_time, Simulate(row, n-1, i));
			}
		}
	}
	
	cout << max_time << "\n";
	return 0;
}