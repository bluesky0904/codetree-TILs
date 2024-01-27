#include <iostream>
#include <vector>
using namespace std;

#define DIR_NUM 5

int N, M, Q;
int dx[DIR_NUM] = {0, 1,0,-1,0};
int dy[DIR_NUM] = {0, 0,-1,0,1};

bool InRange(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < M;
}

void Simulate(vector<vector<int>>& grid, vector<vector<int>>& tmp_grid, int r1, int c1, int r2, int c2) {
	int tmp = grid[r1][c1];
	for (int i = r1; i < r2; i++) {
		grid[i][c1] = grid[i + 1][c1];
	}
	for (int i = c1; i < c2; i++) {
		grid[r2][i] = grid[r2][i + 1];
	}
	for (int i = r2; i > r1; i--) {
		grid[i][c2] = grid[i-1][c2];
	}
	for (int i = c2; i > c1+1; i--) {
		grid[r1][i] = grid[r1][i-1];
	}
	grid[r1][c1+1] = tmp;

	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			int hap = 0;
			int cnt = 0;
			int cx = i, cy = j;
			for (int k = 0; k < DIR_NUM; k++) {
				int nx = cx + dx[k]; 
				int ny = cy + dy[k];
				if (InRange(nx, ny)) {
					hap += grid[nx][ny];
					cnt++;
				}
			}
			tmp_grid[i][j] = hap / cnt;
		}
	}

	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			grid[i][j] = tmp_grid[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M >> Q;
	vector<vector<int>> grid(N, vector<int>(M));
	vector<vector<int>> tmp_grid(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> grid[i][j];
			tmp_grid[i][j] = grid[i][j];
		}
	}

	for (int i = 0; i < Q; i++) {
		int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
		Simulate(grid, tmp_grid, r1-1, c1-1, r2-1, c2-1);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}