#include <iostream>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n, r, c;

int grid[MAX_N][MAX_N];

int dx[DIR_NUM] = { -1,1,0,0 };
int dy[DIR_NUM] = { 0,0,-1,1 };

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int x, int y) {
	int cx = x, cy = y;
	cout << grid[cx][cy] << " ";
	while (true) {
		bool is_possible = false;
		for (int dir = 0; dir <= DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && grid[nx][ny] > grid[cx][cy]) {
				is_possible = true;
				cx = nx;
				cy = ny;
				cout << grid[cx][cy] << " ";
				break;
			}
		}
		if (!is_possible) return;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> r >> c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	Simulate(r-1, c-1);
	return 0;
}