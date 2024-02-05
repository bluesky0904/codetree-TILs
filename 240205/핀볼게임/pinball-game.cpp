#include <iostream>
#include <algorithm>
using namespace std;

#define DIR_NUM 4
#define MAX_N 100

int n;
int ans = -1;
int grid[MAX_N][MAX_N];
int dx[DIR_NUM] = {1,0,-1,0};
int dy[DIR_NUM] = {0,-1,0,1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int Simulate(int dir_num, int start_n) {
	int t = 1;
	int cx, cy, dir = dir_num;
	if (dir == 0) {
		cx = 0; cy = start_n;
	}
	else if (dir == 1) {
		cx = start_n; cy = n - 1;
	}
	else if (dir == 2) {
		cx = n - 1; cy = start_n;
	}
	else {
		cx = start_n; cy = 0;
	}

	while (true) {
		if (!InRange(cx, cy)) break;

		if (grid[cx][cy] == 0) {
			cx += dx[dir];
			cy += dy[dir];
		}
		else if (grid[cx][cy] == 1) {
			if (dir == 0) dir = 1;
			else if (dir == 1) dir = 0;
			else if (dir == 2) dir = 3;
			else dir = 2;

			cx += dx[dir];
			cy += dy[dir];
		}
		else {
			if (dir == 0) dir = 3;
			else if (dir == 1) dir = 2;
			else if (dir == 2) dir = 1;
			else dir = 0;

			cx += dx[dir];
			cy += dy[dir];
		}
		t++;
	}
	return t;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}
	
	for (int dir_num = 0; dir_num < DIR_NUM; dir_num++) {
		for (int start_n = 0; start_n < n; start_n++) {
			ans = max(ans, Simulate(dir_num, start_n));
		}
	}
	
	cout << ans << "\n";
}