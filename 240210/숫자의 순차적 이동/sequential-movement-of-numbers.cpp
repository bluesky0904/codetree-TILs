#include <iostream>
#include <tuple>
using namespace std;

#define MAX_N 20
#define DIR_NUM 8

int n, m;
int grid[MAX_N][MAX_N];
int dx[DIR_NUM] = {-1,-1,-1,0,1,1,1,0};
int dy[DIR_NUM] = {1,0,-1,-1,-1,0,1,1};

pair<int, int> FindPos(int num) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == num) return make_pair(i, j);
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> GetNextPos(pair<int, int> cur_pos) {
	int x, y; tie(x, y) = cur_pos;
	int max_num = -1;
	int mx, my;
	for (int i = 0; i < DIR_NUM; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (InRange(nx, ny) && grid[nx][ny] > max_num) {
			max_num = grid[nx][ny];
			mx = nx, my = ny;
		}
	}
	return make_pair(mx, my);
}

void Swap(pair<int, int> pos, pair<int, int> next_pos) {
	int x, y, nx, ny;
	tie(x, y) = pos;
	tie(nx, ny) = next_pos;

	int temp = grid[x][y];
	grid[x][y] = grid[nx][ny];
	grid[nx][ny] = temp;
}

void Simulate() {
	for (int num = 1; num <= n * n; num++) {
		pair<int, int > pos = FindPos(num);
		pair<int, int> next_pos = GetNextPos(pos);
		Swap(pos, next_pos);
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	while (m--) Simulate();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}