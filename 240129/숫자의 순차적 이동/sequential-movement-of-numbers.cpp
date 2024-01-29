#include <iostream>
using namespace std;

#define MAX_N 20
#define DIR_NUM 8

int n, m;

int grid[MAX_N][MAX_N];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> GetNextPos(int x, int y) {
	int dx[DIR_NUM] = {-1,-1,-1,0,1,1,1,0};
	int dy[DIR_NUM] = {1,0,-1,-1,-1,0,1,1};
	int max_num = 0;
	int mx, my;
	for (int i = 0; i < DIR_NUM; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (InRange(nx, ny) && grid[nx][ny] > max_num) {
			max_num = grid[nx][ny];
			mx = nx;
			my = ny;
		}
	}
	return make_pair(mx, my);
}

void Exchange(int x, int y) {
	pair<int, int> next_pos = GetNextPos(x, y);
	int nx = next_pos.first;
	int ny = next_pos.second;
	int tmp = grid[nx][ny];
	grid[nx][ny] = grid[x][y];
	grid[x][y] = tmp;
}

void Simulate() {
	for (int k = 1; k <= n * n; k++) {
		int x, y;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (grid[i][j] == k) {
					x = i;
					y = j;
				}
			}
		}
		Exchange(x, y);
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	while (m--) Simulate();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout <<  grid[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}