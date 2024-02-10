#include<iostream>
#include <tuple>
#include <vector>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n, m, t;
int nums[MAX_N][MAX_N];
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];
int dx[DIR_NUM] = {-1,1,0,0};
int dy[DIR_NUM] = {0,0,-1,1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> GetNextPos(int x, int y) {
	int max_num = -1;
	int mx, my;
	for (int i = 0; i < DIR_NUM; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (InRange(nx, ny) && nums[nx][ny] > max_num) {
			max_num = nums[nx][ny];
			mx = nx, my = ny;
		}
	}
	return make_pair(mx, my);
}

void MoveAll() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 1) {
				int x, y;
				tie(x, y) = GetNextPos(i, j);
				next_grid[x][y]++;
			}
		}
	}
}

void RemoveDuplicateMarble() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (next_grid[i][j] > 1) next_grid[i][j] = 0;
		}
	}
}

void Simulate() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = 0;
		}
	}

	MoveAll();
	RemoveDuplicateMarble();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

int CountRemainMarbles() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] > 0) cnt++;
		}
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> t;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> nums[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int r, c; cin >> r >> c;
		grid[r - 1][c - 1]++;
	}

	while (t--) Simulate();
	cout << CountRemainMarbles() << "\n";
}