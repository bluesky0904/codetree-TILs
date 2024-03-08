#include <iostream>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n, x, y;
char grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N][DIR_NUM];

int dx[DIR_NUM] = {0, -1, 0, 1};
int dy[DIR_NUM] = {1, 0, -1, 0};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int Simulate(int x, int y) {
	int elapsed_time = 0;
	int cx = x, cy = y, dir = 0;
	visited[cx][cy][dir] = true;
	while (true) {
		int nx = cx + dx[dir], ny = cy + dy[dir];

		if (InRange(nx, ny) && visited[nx][ny][dir]) return -1;

		if (InRange(nx, ny) && grid[nx][ny] == '#') {
			dir = (dir + 1) % 4;
		}
		else if (!InRange(nx, ny)) {
			elapsed_time++;
			return elapsed_time;
		}
		else {
			int rx = nx + dx[(dir + 3) % 4], ry = ny + dy[(dir + 3) % 4];
			if (InRange(rx, ry) && grid[rx][ry] == '#') {
				elapsed_time++;
				cx = nx;
				cy = ny;
				visited[cx][cy][dir] = true;
			}
			else {
				elapsed_time += 2;
				visited[nx][ny][dir] = true;
				cx = rx;
				cy = ry;
				dir = (dir + 3) % 4;
				visited[cx][cy][dir] = true;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> x >> y;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
		cin.ignore();
	}

	cout << Simulate(x - 1, y - 1) << "\n";

	return 0;
}