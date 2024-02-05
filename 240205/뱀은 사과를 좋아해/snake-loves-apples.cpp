#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define DIR_NUM 4
#define MAX_N 100
#define ASCII_NUM 128

int n, m, k;
int ans = 0;
bool keep_go;
int grid[MAX_N][MAX_N];
int dx[DIR_NUM] = {-1,1,0,0};
int dy[DIR_NUM] = {0,0,1,-1};

vector<pair<int, int>> snake;

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

bool OverlappedSnake() {
	for (int i = 1; i < snake.size(); i++) {
		if (snake[i] == snake[0]) return true;
	}
	return false;
}

bool GameQuit() {
	if (!InRange(snake[0].first, snake[0].second)) return true;
	if (OverlappedSnake()) return true;
	return false;
}

void Simulate(int d, int p) {
	
	for (int dis = 0; dis < p; dis++) {
		int nx = snake[0].first + dx[d];
		int ny = snake[0].second + dy[d];

		// 변화 포인트
		/*
		if (!InRange(nx, ny) || OverlappedSnake()) {
			keep_go = false;
			return;

		}
		*/
		if (grid[nx][ny] == 1) {
			grid[nx][ny] = 0;
			snake.insert(snake.begin(), { nx, ny });
		}
		// 변화 포인트
		else {
			snake.insert(snake.begin(), { nx, ny });
			snake.pop_back();
		}
		ans++;

		if (GameQuit()) {
			keep_go = false;
			return;
		}
	}
	keep_go = true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	snake.push_back({0, 0});
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		x--; y--;
		grid[x][y] = 1;
	}

	int dir_num[ASCII_NUM];
	dir_num['U'] = 0;
	dir_num['D'] = 1;
	dir_num['R'] = 2;
	dir_num['L'] = 3;

	keep_go = false;
	for (int i = 0; i < k; i++) {
		char d; int p; cin >> d >> p;
		Simulate(dir_num[d], p);
		if (!keep_go) break;
	}
	cout << ans << "\n";
}