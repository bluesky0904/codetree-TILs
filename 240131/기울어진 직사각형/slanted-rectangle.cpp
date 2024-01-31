#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n;
int grid[MAX_N][MAX_N];
int dx[DIR_NUM] = {-1,-1, 1, 1};
int dy[DIR_NUM] = {1,-1, -1, 1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int RecSum(int x, int y, int width, int length) {
	int cx = x, cy = y;
	int rec_sum = 0;
	int nx, ny;
	for (int i = 1; i < width; i++) {
		nx = cx + dx[0];
		ny = cy + dy[0];
		if (InRange(nx, ny)) {
			rec_sum += grid[nx][ny];
			cx = nx;
			cy = ny;
		}
		else return -1;
	}
	for (int i = 1; i < length; i++) {
		nx = cx + dx[1];
		ny = cy + dy[1];
		if (InRange(nx, ny)) {
			rec_sum += grid[nx][ny];
			cx = nx;
			cy = ny;
		}
		else return -1;
	}
	for (int i = 1; i < width; i++) {
		nx = cx + dx[2];
		ny = cy + dy[2];
		if (InRange(nx, ny)) {
			rec_sum += grid[nx][ny];
			cx = nx;
			cy = ny;
		}
		else return -1;
	}
	for (int i = 1; i < length; i++) {
		nx = cx + dx[3];
		ny = cy + dy[3];
		if (InRange(nx, ny)) {
			rec_sum += grid[nx][ny];
			cx = nx;
			cy = ny;
		}
		else return -1;
	}
	return rec_sum;
}

int Simulate(int x, int y) {
	int max_val = -1;
	for (int width = 1; width < n; width++) {
		for (int length = 1; length < n; length++) {
			max_val = max(max_val, RecSum(x, y, width, length));
		}
	}
	return max_val;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans = max(ans, Simulate(i, j));
		}
	}

	cout << ans << "\n";
}