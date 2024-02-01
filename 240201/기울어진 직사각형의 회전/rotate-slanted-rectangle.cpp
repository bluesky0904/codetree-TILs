#include <iostream>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n;
int grid[MAX_N][MAX_N];
int dx[DIR_NUM] = {-1,-1,1,1};
int dy[DIR_NUM] = {1,-1,-1,1};

int dx_clock[DIR_NUM] = { -1,-1,1,1 };
int dy_clock[DIR_NUM] = { -1,1,1,-1 };

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int r, int c, int m1, int m2, int m3, int m4, int dir) {
	int cx = r, cy = c;
	if (dir == 0) {
		int cnt[DIR_NUM] = { m4,m3,m2,m1-1};
		int tmp = grid[cx][cy];
		for (int i = 0; i < DIR_NUM; i++) {
			for (int j = 0; j < cnt[i]; j++) {
				int nx = cx + dx_clock[i];
				int ny = cy + dy_clock[i];
				if (InRange(nx, ny)) {
					grid[cx][cy] = grid[nx][ny];
					cx = nx;
					cy = ny;
				}
			}
		}
		grid[cx][cy] = tmp;
	}
	else {
		int cnt[DIR_NUM] = { m1,m2,m3,m4 - 1 };
		int tmp = grid[cx][cy];
		for (int i = 0; i < DIR_NUM; i++) {
			for (int j = 0; j < cnt[i]; j++) {
				int nx = cx + dx[i];
				int ny = cy + dy[i];
				if (InRange(nx, ny)) {
					grid[cx][cy] = grid[nx][ny];
					cx = nx;
					cy = ny;
				}
			}
		}
		grid[cx][cy] = tmp;
	}
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