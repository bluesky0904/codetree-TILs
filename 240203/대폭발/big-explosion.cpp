#include <iostream>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n, m, r, c;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];
int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,-1,0,1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int t) {
	int dis = 1 << (t - 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 1) {
				for (int dir = 0; dir < DIR_NUM; dir++) {
					int ni = i, nj = j;
					next_grid[ni][nj] = 1;
					for (int cnt = 0; cnt < dis; cnt++) {
						ni += dx[dir];
						nj += dy[dir];
					}
					if (InRange(ni, nj) && grid[ni][nj] == 0) next_grid[ni][nj] = 1;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
	
}

int CountRemainBombs() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] != 0) cnt++;
		}
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> r >> c; r--; c--;
	grid[r][c] = 1;
	for (int t = 1; t <= m; t++) Simulate(t);
	cout << CountRemainBombs() << "\n";
}