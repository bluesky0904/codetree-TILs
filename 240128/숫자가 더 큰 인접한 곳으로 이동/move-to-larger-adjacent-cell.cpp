#include <iostream>
#include <vector>
using namespace std;

#define DIR_NUM 4

int n;
vector<vector<int>> grid;
int dx[DIR_NUM] = {-1,1,0,0};
int dy[DIR_NUM] = {0,0,-1,1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int r, int c) {
	int cx = r;
	int cy = c;
	while (true) {
		int max_num = 0;
		bool is_possible = false;
		for (int i = 0; i < DIR_NUM; i++) {
			int cnt = 1;
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (InRange(nx, ny) && grid[nx][ny] > grid[cx][cy]) {
				is_possible = true;
				max_num = grid[nx][ny];
				cx = nx;
				cy = ny;
				cout << grid[cx][cy] << " ";
			}
			
		}
		if (!is_possible) return;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	int r, c; cin >> r >> c; r--; c--;
	grid.resize(n, vector<int>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	cout << grid[r][c] << " ";
	Simulate(r, c);
}