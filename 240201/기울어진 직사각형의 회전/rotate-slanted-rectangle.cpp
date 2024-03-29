#include <iostream>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int x, int y, int m1, int m2, int m3, int m4, int dir) {
	int cnt[DIR_NUM], dx[DIR_NUM], dy[DIR_NUM];
	int tmp = grid[x][y];
	if (dir == 0) {
		cnt[0] = m4, cnt[1] = m3, cnt[2] = m2,cnt[3] = m1 - 1;
		dx[0] = -1, dx[1] = -1, dx[2] = 1, dx[3] = 1;
		dy[0] = -1, dy[1] = 1, dy[2] = 1, dy[3] = -1;
	}
	else {
		cnt[0] = m1, cnt[1] = m2, cnt[2] = m3, cnt[3] = m4 - 1;
		dx[0] = -1, dx[1] = -1, dx[2] = 1, dx[3] = 1;
		dy[0] = 1, dy[1] = -1, dy[2] = -1, dy[3] = 1;
	}

	for (int i =0; i < DIR_NUM; i++) {
		for (int j = 0; j < cnt[i]; j++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (InRange(nx, ny)) {
				grid[x][y] = grid[nx][ny];
				x = nx;
				y = ny;
			}
		}
	}
	grid[x][y] = tmp;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	int r, c, m1, m2, m3, m4, dir;
	cin >> r >> c >> m1 >> m2 >> m3 >> m4 >> dir;
	r--; c--;
	Simulate(r, c, m1, m2, m3, m4, dir);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}