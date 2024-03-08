#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 100
#define ASCII_NUM 128
#define DIR_NUM 4

int n, m, k;
int elapsed_time = 0;

vector<pair<int, int>> snake;
int grid[MAX_N][MAX_N];
int mapper[ASCII_NUM];

int dx[DIR_NUM] = {-1,1,0,0};
int dy[DIR_NUM] = {0,0,1,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

bool Overlapped(int x, int y) {
	for (int i = 1; i < snake.size()-1; i++) {
		if (snake[i] == make_pair(x, y)) return true;
	}
	return false;
}

bool Simulate(int dir, int dis) {
	while (dis--) {
		int cx, cy;
		tie(cx, cy) = snake.front();
		int nx = cx + dx[dir], ny = cy + dy[dir];
		if (!InRange(nx, ny) || Overlapped(nx, ny)) {
			elapsed_time++;
			return false;
		}
		if (grid[nx][ny] == 1) {
			grid[nx][ny] = 0;
			snake.insert(snake.begin(), { nx, ny });
			elapsed_time++;
		}
		else {
			snake.insert(snake.begin(), { nx, ny });
			snake.pop_back();
			elapsed_time++;
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		grid[x - 1][y - 1] = 1;
	}

	snake.push_back(make_pair(0, 0));

	mapper['U'] = 0;
	mapper['D'] = 1;
	mapper['R'] = 2;
	mapper['L'] = 3;

	for (int i = 0; i < k; i++) {
		char d;
		int p;
		cin >> d >> p;
		if (!Simulate(mapper[d], p)) break;
	}

	cout << elapsed_time << "\n";
	return 0;
}