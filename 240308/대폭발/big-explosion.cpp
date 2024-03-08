#include <iostream>
using namespace std;

#define MAX_N 100
#define DIR_NUM 5

int n, m;
int x, y;

int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];

int dx[DIR_NUM] = {0,-1,0,1,0};
int dy[DIR_NUM] = {0,0,1,0,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void DuplicateGrid() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

int CountGrid() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 1) cnt++;
		}
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int r, c;
	cin >> n >> m >> r >> c;
	x = r - 1, y = c - 1;
	grid[x][y] = 1;
	for (int t = 1; t <= m; t++) {
		int dis = 1 << (t - 1);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (grid[i][j] == 1) {
					for (int dir = 0; dir < DIR_NUM; dir++) {
						int ni = i + dx[dir] * dis, nj = j + dy[dir] * dis;
						if (InRange(ni, nj))next_grid[ni][nj] = 1;
					}
				}
			}
		}
		DuplicateGrid();
	}

	cout << CountGrid() << "\n";
}