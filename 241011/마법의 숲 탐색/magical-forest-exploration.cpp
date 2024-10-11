/*
정령 : K명, 각자 골렘(십자 모양의 구조, 중앙 칸을 포함 5칸 차지)을 타고 숲을 탐색
	골렘의 중앙을 제외한 4칸 중 한 칸은 골렘의 출구
	정령은 어떤 방향에서는 골렘에 탑승 가능, 내릴 때에는 정해진 출구로만 가능
마법의 숲 : 1 base index, R * C, 숲의 동/서/남은 벽으로 막혀 있고, 정령들은 숲의 북쪽으로만 들어올 수 있음

골렘의 이동. 더 이상 움직이지 못할 때까지 해당 과정을 반복
1. 남쪽으로 한 칸 내려감
	아래쪽의 세 칸이 비워져 있을 때만 내려갈 수 있음
2. 서쪽 방향으로 회전하면서 내려감
	서쪽의 세 칸 그리고 남쪽의 두 칸이 비워져 있을 때만 내려갈 수 있음
	출구가 반시계 방향으로 이동함
3. 동쪽 방향으로 회전하면서 내려감
	동쪽의 세 칸 그리고 남쪽의 두 칸이 비워져 있을 때만 내려갈 수 있음
	출구가 시계 방향으로 이동함

골렘이 이동할 수 있는 가장 남쪽에 도달에 더이상 이동할 수 없으면 정령은 골렘 내에서 상하좌우 인접한 칸으로 이동 가능.
만약 현재 위치하고 있는 골렘의 출구가 다른 골렘과 인접하고 있다면 해당 출구를 통해 다른 골렘으로 이동할 수 있음
정령은 갈 수 있는 모든 칸 중 가장 남쪽 칸으로 이동하고 이동을 종료. 이때 정령의 위치가 최종 위치.

골렘의 몸 일부가 여전히 숲을 벗어난 상태라면, 숲에 위치한 모든 골렘들은 숲을 빠져나간 뒤 다음 골렘부터 새롭게 시작
단, 이 경우는 정령이 도달하는 최종 위치를 답에 포함시키지 않음

골렘들이 숲에 진입함에 따라 각 정령들이 최종적으로 위치한 행의 총합.
*/

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
int grid[GRID_NUM + 4][GRID_NUM + 1]; // 0은 빈 상태, 1,2,3,... 은 각 골렘의 번호
bool is_exit[GRID_NUM + 4][GRID_NUM + 1] = { false, };

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool InRange(int x, int y) {
	return 1 <= x && x <= R + 3 && 1 <= y && y <= C;
}

bool InGrid(int x, int y) {
	return 4 <= x && x <= R + 3 && 1 <= y && y <= C;
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
	for (int i = 1; i <= R + 3; i++) {
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
			if (InGrid(nx, ny) && !visited[nx][ny] && grid[nx][ny] != 0 &&(grid[cx][cy] == grid[nx][ny] || is_exit[cx][cy])) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}

	ans += (max_row - 3);
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