#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

#define GRID_NUM 70
#define DIR_NUM 4

int ans = 0;
int R, C, K;
int grid[GRID_NUM + 3][GRID_NUM + 1]; // 0은 빈 상태, 1,2,3,... 은 각 골렘의 번호
bool is_exit[GRID_NUM + 3][GRID_NUM + 1] = { false, };

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool InRange(int x, int y) {
	return 1 <= x && x <= R + 2 && 1 <= y && y <= C;
}

bool InGrid(int x, int y) {
	return 3 <= x && x <= R + 2 && 1 <= y && y <= C;
}

bool CanGoSouth(int row, int col) {
	if (!InRange(row + 1, col - 1) || grid[row + 1][col - 1] != 0) return false;
	if (!InRange(row + 2, col) || grid[row + 2][col] != 0) return false;
	if (!InRange(row + 1, col + 1) || grid[row + 1][col + 1] != 0) return false;
	return true;
}

bool CanGoWest(int row, int col) {
	if (!InRange(row - 1, col - 1) || grid[row - 1][col - 1] != 0) return false;
	if (!InRange(row, col - 2) || grid[row][col - 2] != 0) return false;
	if (!InRange(row + 1, col - 1) || grid[row + 1][col - 1] != 0) return false;
	return true;
}

bool CanGoEast(int row, int col) {
	if (!InRange(row - 1, col + 1) || grid[row - 1][col + 1] != 0) return false;
	if (!InRange(row, col + 2) || grid[row][col + 2] != 0) return false;
	if (!InRange(row + 1, col + 1) || grid[row + 1][col + 1] != 0) return false;
	return true;
}

bool OutGrid(int row, int col) {
	if (!InGrid(row, col)) return true;
	for (int dir = DIR_NUM - 1; dir >= 0; dir--) {
		int nx = row + dx[dir], ny = col + dy[dir];
		if (!InGrid(nx, ny)) return true;
	}
	return false;
}

void InitGrid() {
	for (int i = 1; i <= R + 2; i++) {
		for (int j = 1; j <= C; j++) {
			grid[i][j] = 0;
			is_exit[i][j] = false;
		}
	}
}

void SearchGrid(int num, int col, int dir) {
	int robot_row = 2, robot_col = col, robot_dir = dir;
	while (true) {
		if (CanGoSouth(robot_row, robot_col)) {
			robot_row++;
		}
		else if (CanGoWest(robot_row, robot_col) && CanGoSouth(robot_row, robot_col - 1)) {
			robot_row++;
			robot_col--;
			robot_dir = (robot_dir + 3) % 4;
		}
		else if (CanGoEast(robot_row, robot_col) && CanGoSouth(robot_row, robot_col + 1)) {
			robot_row++;
			robot_col++;
			robot_dir = (robot_dir + 1) % 4;
		}
		else break;
	}

	if (OutGrid(robot_row, robot_col)) {
		InitGrid();
		return;
	}

	grid[robot_row][robot_col] = num;
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = robot_row + dx[dir], ny = robot_col + dy[dir];
		if (dir == robot_dir) is_exit[nx][ny] = true;
		grid[nx][ny] = num;
	}

	int max_row = robot_row;
	queue<pair<int, int>> q;
	bool visited[GRID_NUM + 3][GRID_NUM + 1] = { false, };

	q.push({ robot_row, robot_col });
	visited[robot_row][robot_col] = true;
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second; q.pop();

		if (cx > max_row) max_row = cx;

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InGrid(nx, ny) && !visited[nx][ny] && (grid[cx][cy] == grid[nx][ny] || (is_exit[cx][cy] && grid[nx][ny] > 0))) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}
	ans += (max_row - 2);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> R >> C >> K;
	for (int i = 1; i <= K; i++) {
		int col, dir;
		cin >> col >> dir;
		SearchGrid(i, col, dir);
	}

	cout << ans << "\n";
	return 0;
}