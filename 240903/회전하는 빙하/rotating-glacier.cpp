#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAX_NUM 64
#define DIR_NUM 4

int n, q;
int grid_size;

int grid[MAX_NUM][MAX_NUM];
int next_grid[MAX_NUM][MAX_NUM];

int dx[DIR_NUM] = {0, 1, 0, -1};
int dy[DIR_NUM] = {1, 0, -1, 0};

bool visited[MAX_NUM][MAX_NUM] = {false};


bool InRange(int x, int y) {
	return 0 <= x && x < grid_size && 0 <= y && y < grid_size;
}

void InitializeNextGrid() {
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			next_grid[i][j] = 0;
		}
	}
}

void Move(int row, int col, int half_size, int dir) {
	for (int x = row; x < row + half_size; x++) {
		for (int y = col; y < col + half_size; y++) {
			int nx = x + dx[dir] * half_size, ny = y + dy[dir] * half_size;
			next_grid[nx][ny] = grid[x][y];
		}
	}
}

void Rotate(int level) {
	if (level == 0) return;

	InitializeNextGrid();

	int box_size = pow(2, level);
	int half_size = box_size / 2; // 이동할 크기
	for (int center_x = 0; center_x < grid_size; center_x += box_size) {
		for (int center_y = 0; center_y < grid_size; center_y += box_size) {
			Move(center_x, center_y, half_size, 0);
			Move(center_x, center_y + half_size, half_size, 1);
			Move(center_x + half_size, center_y + half_size, half_size, 2);
			Move(center_x + half_size, center_y, half_size, 3);
		}
	}

	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

void Melt() {
	InitializeNextGrid();

	for (int x = 0; x < grid_size; x++) {
		for (int y = 0; y < grid_size; y++) {
			if (grid[x][y] > 0) {
				int cnt = 0;
				for (int dir = 0; dir < DIR_NUM; dir++) {
					int nx = x + dx[dir], ny = y + dy[dir];
					if (InRange(nx, ny) && grid[nx][ny] > 0) cnt++;
				}
				if (cnt >= 3) next_grid[x][y] = grid[x][y];
				else next_grid[x][y] = grid[x][y] - 1;
			}
		}
	}

	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

int GetTotal() {
	int total = 0;
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			if(grid[i][j] > 0) total += grid[i][j];
		}
	}
	return total;
}

int BFS(int x, int y) {
	int cnt = 1;
	queue<pair<int, int>> que;
	que.push({ x, y });
	visited[x][y] = true;
	while (!que.empty()) {
		int cx = que.front().first, cy = que.front().second;
		que.pop();
		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && grid[nx][ny] > 0 && visited[nx][ny] == false) {
				que.push({ nx, ny });
				visited[nx][ny] = true;
				cnt++;
			}
		}
	}
	return cnt;
}

int GetMaxCluster() {
	int max_cluster = 0;
	for (int x = 0; x < grid_size; x++) {
		for (int y = 0; y < grid_size; y++) {
			if (grid[x][y] == 0 || visited[x][y] == true) continue;
			max_cluster = max(max_cluster, BFS(x, y));
		}
	}
	return max_cluster;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	cin >> n >> q;
	grid_size = pow(2, n);
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			cin >> grid[i][j];
		}
	}
	while (q--) {
		int level;
		cin >> level;
		Rotate(level);
		Melt();
	}

	cout << GetTotal() << '\n';
	cout << GetMaxCluster() << '\n';
}