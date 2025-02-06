/*
n x m 크기의 이차원 영역에 방화벽을 설치
불은 상하좌우의 인접한 공간으로 모두 번지는 특성
방화벽을 뚫을 수는 없음

기존에 이미 설치되어 있는 방화벽을 제외하고 추가로 3개의 방화벽을 설치
정확히 3개의 방화벽을 추가로 설치하여 불이 퍼지지 않는 영역이 최대일 때의 크기 출력

격자 : 불 2 벽 1 빈칸 0
불
방화벽
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define GRID_SIZE 8
#define DIR_NUM 4

int n, m;
int grid[GRID_SIZE][GRID_SIZE];
int next_grid[GRID_SIZE][GRID_SIZE];
bool visited[GRID_SIZE][GRID_SIZE];
int max_size = 0;
vector<pair<int, int>> fire_pos;
vector<pair<int, int>> fire_wall;
vector<pair<int, int>> empty_space;

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

void print() {
	cout << "FIRE POS" << "\n";
	for (int i = 0; i < fire_pos.size(); i++)
		cout << fire_pos[i].first << " " << fire_pos[i].second << "\n";
	cout << "FIRE WALL" << "\n";
	for (int i = 0; i < fire_wall.size(); i++)
		cout << fire_wall[i].first << " " << fire_wall[i] .second << "\n";

}

vector<pair<int, int>> selected;

bool inRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

int getSize() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			next_grid[i][j] = grid[i][j];
		}
	}

	for (int i = 0; i < selected.size(); i++) {
		int x = selected[i].first, y = selected[i].second;
		next_grid[x][y] = 1;
	}

	queue<pair<int, int>> q;
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < fire_pos.size(); i++) {
		int x = fire_pos[i].first, y = fire_pos[i].second;
		q.push({ x, y });
		visited[x][y] = true;
	}
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second; q.pop();

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (inRange(nx, ny) && next_grid[nx][ny] == 0 && !visited[nx][ny]) {
				q.push({ nx, ny});
				visited[nx][ny] = true;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j]) cnt++;
		}
	}

	return n * m - cnt - 3 - fire_wall.size();
}

void findMaxRegion(int start) {
	if (selected.size() == 3) {
		max_size = max(max_size, getSize());
		return;
	}

	for (int i = start; i < empty_space.size(); i++) {
		selected.push_back(empty_space[i]);
		findMaxRegion(i + 1);
		selected.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 2) fire_pos.push_back({ i, j });
			if (grid[i][j] == 1) fire_wall.push_back({ i, j });
			if (grid[i][j] == 0) empty_space.push_back({ i, j });
		}
	}

	//print();
	findMaxRegion(0);

	cout << max_size << "\n";
	return 0;
}