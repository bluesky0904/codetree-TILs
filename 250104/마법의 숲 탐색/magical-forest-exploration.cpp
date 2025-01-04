/*
정령 : K명, 각자 골렘을 타고 숲을 탐색
	   각 골렘은 십자 모양의 구조를 가지고 있으며, 중앙 칸을 포함해 총 5칸을 차지
	   골렘의 중앙을 제외한 4칸 중 한 칸은 골렘의 출구
	   정령은 어떤 방향에서든 골렘에 탑승할 수 있지만 골렘에서 내릴 때에는 정해진 출구를 통해서만 가능
	   i번째로 숲을 탐색하는 골렘은 숲의 가장 북쪽에서 시작해 골렘의 중앙이 ci열이 되도록 하는 위치에서 내려옴
	   초기 골렘의 출구는 di 방향에 위치

마법의 숲 : R x C, 1-based grid, 숲의 북쪽을 통해서만 숲에 들어올 수 있음

골렘은 숲을 탐색하기 위해 다음과 같은 우선순위로 이동
더 이상 움직이지 못할 때까지 해당 과정을 반복
1. 남쪽으로 한 칸 내려감
아래의 세 칸들이 비어있을 때에만 남쪽으로 내려갈 수 있음

2. (1)의 방법으로 이동할 수 없으면 서쪽 방향으로 회전하면서 내려감
왼쪽 세 칸과 아래 두 칸이 비어있을 때에만 서쪽 방향으로 회전하면서 내려갈 수 있음
출구가 반시계 방향으로 이동

3. (1)과 (2)의 방법으로 이동할 수 없으면 동쪽 방향으로 회전하면서 내려감
오른쪽 세 칸과 아래 두 칸이 비어있을 때에만 동쪽 방향으로 회전하면서 내려갈 수 있음
출구가 시계 방향으로 이동

골렘이 이동할 수 있는 가장 남쪽에 도달해 더이상 이동할 수 없으면
정령은 골렘 내에서 상하좌우 인접한 칸으로 이동이 가능.
단, 만약 현재 위치하고 있는 골렘의 출구가 다른 골렘과 인접하고 있다면 해당 출구를 통해 다른 골렘으로 이동

정령은 갈 수 있는 모든 칸 중 가장 남쪽의 칸으로 이동하고 이동 종료

각 정령이 도달하게 되는 최종 위치를 누적

만약 골렘이 최대한 남쪽으로 이동했지만 골렘의 몸 일부가 여전히 숲을 벗어난 상태라면, 해당 골렘을 포함해
숲에 위치한 모든 골렘들은 숲을 빠져나간 뒤 다음 골렘부터 새롭게 숲의 탐색을 시작
단, 이 경우에는 정령이 도달하는 최종 위치를 답에 포함하지 않음

골렘들이 숲에 진입함에 따라 각 정령들이 최종적으로 위치한 행의 총합을 구하는 프로그램 작성
숲이 다시 텅 비게 돼도 행의 총합은 누적
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_SIZE 70
#define DIR_NUM 4

int n, m, k;
int grid[MAX_SIZE + 3][MAX_SIZE];
bool out_pos[MAX_SIZE + 3][MAX_SIZE];
bool visited[MAX_SIZE + 3][MAX_SIZE];
int ans = 0;

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool InRange(int x, int y) {
	return (0 <= x && x < n + 3 && 0 <= y && y < m);
}

bool DownPossible(int cur_row, int cur_col) {
	if (!InRange(cur_row + 1, cur_col - 1) || grid[cur_row + 1][cur_col - 1] != 0) return false;
	if (!InRange(cur_row + 2, cur_col) || grid[cur_row + 2][cur_col] != 0) return false;
	if (!InRange(cur_row + 1, cur_col + 1) || grid[cur_row + 1][cur_col + 1] != 0) return false;

	return true;
}

bool LeftPossible(int cur_row, int cur_col) {
	if (!InRange(cur_row - 1, cur_col - 1) || grid[cur_row - 1][cur_col - 1] != 0) return false;
	if (!InRange(cur_row, cur_col - 2) || grid[cur_row][cur_col - 2] != 0) return false;
	if (!InRange(cur_row + 1, cur_col - 1) || grid[cur_row + 1][cur_col - 1] != 0) return false;

	if (!InRange(cur_row + 1, cur_col - 2) || grid[cur_row + 1][cur_col - 2] != 0) return false;
	if (!InRange(cur_row + 2, cur_col - 1) || grid[cur_row + 2][cur_col - 1] != 0) return false;

	return true;
}

bool RightPossible(int cur_row, int cur_col) {
	if (!InRange(cur_row - 1, cur_col + 1) || grid[cur_row - 1][cur_col + 1] != 0) return false;
	if (!InRange(cur_row, cur_col + 2) || grid[cur_row][cur_col + 2] != 0) return false;
	if (!InRange(cur_row + 1, cur_col + 1) || grid[cur_row + 1][cur_col + 1] != 0) return false;

	if (!InRange(cur_row + 1, cur_col + 2) || grid[cur_row + 1][cur_col + 2] != 0) return false;
	if (!InRange(cur_row + 2, cur_col + 1) || grid[cur_row + 2][cur_col + 1] != 0) return false;

	return true;
}

void Reset() {
	for (int i = 0; i < n + 3; i++) {
		for (int j = 0; j < m; j++) {
			grid[i][j] = 0;
			out_pos[i][j] = false;
		}
	}
}

int BFS(int cur_row, int cur_col, int idx) {
	int max_row = -1;

	queue<pair<int, int>> q;
	for (int i = 0; i < n + 3; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = false;
		}
	}
	
	q.push({ cur_row, cur_col });
	visited[cur_row][cur_col] = true;
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();

		max_row = max(max_row, cx);

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == grid[cx][cy] || out_pos[cx][cy])) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}
	
	return max_row;
}

void Down(int col, int dir, int idx) {
	int cur_row = 0;
	int cur_col = col, cur_dir = dir;
	for (int row = 1; row < n + 3; row++) {
		if (DownPossible(row, cur_col)) continue;
		else if (LeftPossible(row, cur_col)) {
			cur_col--;
			cur_dir = (cur_dir + 3) % DIR_NUM;
		}
		else if (RightPossible(row, cur_col)) {
			cur_col++;
			cur_dir = (cur_dir + 1) % DIR_NUM;
		}
		else {
			cur_row = row;
			break;
		}
	}

	if (0 <= cur_row && cur_row <= 2) {
		Reset();
		return;
	}

	grid[cur_row][cur_col] = idx;
	for (int dir = 0; dir < DIR_NUM; dir++) {
		grid[cur_row + dx[dir]][cur_col + dy[dir]] = idx;
	}
	out_pos[cur_row + dx[cur_dir]][cur_col + dy[cur_dir]] = true;

	ans += (BFS(cur_row, cur_col, idx) - 2);
}

void Print() {
	for (int i = 0; i < n + 3; i++) {
		for (int j = 0; j < m; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;

	//Print();

	for (int i = 1; i <= k; i++) {
		int c, d; cin >> c >> d;
		Down(c - 1, d, i);
		//Print();
	}

	cout << ans << "\n";
	return 0;
}