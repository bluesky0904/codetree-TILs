/*
숲
정령

숲의 동쪽, 서쪽, 남쪽은 벽으로 막혀 있고 정령들은 숲의 북쪽을 통해서만 숲에 들어옴
총 K명의 정령은 각자 골렘을 타고 숲을 탐색
각 골렘은 십자 모양의 구조, 중앙 칸을 포함해 총 5칸 차지
골렘의 중앙을 제외한 4칸 중 한 칸은 골렘의 출구
정령은 어떤 방향에서든 골렘에 탑승할 수 있지만 골렘에서 내릴 때에는 정해진 출구를 통해서만 내릴 수 있음

골렘의 이동
(1) 남쪽으로 한 칸 내려감
초록색 칸들이 비어있을 때에만 남쪽으로 내려갈 수 있음

(2) (1)의 방법으로 이동할 수 없으면 서쪽 방향으로 회전하면서 내려감
초록색 칸들이 비어있을 때에만 서쪽 방향으로 회전하면서 내려갈 수 있음
이때 서쪽 방향으로 한 칸 이동을 한 뒤 내려가기 때문에 골렘을 기준으로 서쪽 한 칸이 모두 비어있어야 함
또한 출구가 반시계방향으로 이동

(3) (1)과 (2)의 방법으로 이동할 수 없으면 동쪽 방향으로 회전하면서 내려감
초록색 칸들이 비어있을 때에만 동쪽 방향으로 회전하면서 내려감
이때 동쪽 방향으로 한 칸 이동을 한 뒤 내려가기 때문에 골렘을 기준으로 동쪽 한 칸이 모두 비어있어야 함
또한 출구가 시계방향으로 이동

골렘이 이동할 수 있는 가장 남쪽에 도달해 더 이상 이동할 수 없으면 정령은 골렘 내에서 상하좌우로 인접한 칸으로 이동
현재 위치하고 있는 골렘의 출구가 다른 골렘과 인접하고 있다면 해당 출구를 통해 다른 골렘으로 이동할 수 있음
정령은 갈 수 있는 모든 칸 중 가장 남쪽의 칸으로 이동하고 이동을 완전히 종료.
이때 정령의 위치가 해당 정령의 최종 위치

정령의 최종 위치의 행 번호의 합

만약 골렘이 최대한 남쪽으로 이동했지만 골렘의 몸 일부가 여전히 숲을 벗어난 상태라면,
해당 골렘을 포함해 숲에 위치한 모든 골렘들은 숲을 빠져나간 뒤 다음 골렘부터 새롭게 숲을 탐색
단, 이 경우에는 정령이 도달하는 최종 위치를 답에 포함시키지 않음

골렘들이 숲에 진입함에 따라 각 정령들이 최종적으로 위치한 행의 총합을 구하기
숲이 다시 텅 비게 돼도 행의 총합은 누적되는 것에 유의
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int GRIDSIZE = 70;

int r, c, k;
int grid[GRIDSIZE + 4][GRIDSIZE + 1]; // 1 based index
int is_exit[GRIDSIZE + 4][GRIDSIZE + 1]; // 탈출구 표시
bool visited[GRIDSIZE + 4][GRIDSIZE + 1];

int ans;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool inRange(int x, int y) {
	return (x >= 1 && x <= r + 3 && y >= 1 && y <= c);
}

bool isBatch(int row, int col) {
	for (int dir = 0; dir < 4; dir++) {
		int nx = row + dx[dir];
		int ny = col + dy[dir];

		if (!inRange(nx, ny) || grid[nx][ny] != 0) return false;
	}
	return true;
}

bool isPossible(int row, int col) {
	if (!inRange(row + 1, col - 1) || grid[row + 1][col - 1] != 0) return false;
	if (!inRange(row + 2, col) || grid[row + 2][col] != 0) return false;
	if (!inRange(row + 1, col + 1) || grid[row + 1][col + 1] != 0) return false;

	return true;
}

bool isLeftPossible(int row, int col) {

	if (!inRange(row - 1, col - 1) || grid[row - 1][col - 1] != 0) return false;
	if (!inRange(row, col - 2) || grid[row][col - 2] != 0) return false;
	if (!inRange(row + 1, col - 1) || grid[row + 1][col - 1] != 0) return false;

	return true;
}

bool isRightPossible(int row, int col) {
	if (!inRange(row - 1, col + 1) || grid[row - 1][col + 1] != 0) return false;
	if (!inRange(row, col + 2) || grid[row][col + 2] != 0) return false;
	if (!inRange(row + 1, col + 1) || grid[row + 1][col + 1] != 0) return false;

	return true;
}

bool isReset() {
	for (int row = 1; row <= 3; row++) {
		for (int col = 1; col <= c; col++) {
			if (grid[row][col] != 0) return true;
		}
	}
	return false;
}

/*
골렘의 이동
(1) 남쪽으로 한 칸 내려감
초록색 칸들이 비어있을 때에만 남쪽으로 내려갈 수 있음

(2) (1)의 방법으로 이동할 수 없으면 서쪽 방향으로 회전하면서 내려감
초록색 칸들이 비어있을 때에만 서쪽 방향으로 회전하면서 내려갈 수 있음
이때 서쪽 방향으로 한 칸 이동을 한 뒤 내려가기 때문에 골렘을 기준으로 서쪽 한 칸이 모두 비어있어야 함
또한 출구가 반시계방향으로 이동

(3) (1)과 (2)의 방법으로 이동할 수 없으면 동쪽 방향으로 회전하면서 내려감
초록색 칸들이 비어있을 때에만 동쪽 방향으로 회전하면서 내려감
이때 동쪽 방향으로 한 칸 이동을 한 뒤 내려가기 때문에 골렘을 기준으로 동쪽 한 칸이 모두 비어있어야 함
또한 출구가 시계방향으로 이동
*/

int BFS(int x, int y) {
	memset(visited, 0, sizeof(visited));
	queue<pair<int, int>> q;
	int max_row = x;

	q.push({ x, y });
	visited[x][y] = true;
	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];

			if (inRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == grid[cx][cy] || grid[nx][ny] != 0 && is_exit[cx][cy] == 1)) {
				visited[nx][ny] = true;
				q.push({ nx, ny });
				if (max_row < nx) max_row = nx;
			}
		}
	}

	return max_row;
}

void moveCross(int s_col, int dir, int id) {
	int cur_row = 2;
	int cur_col = s_col;
	int cur_dir = dir;

	while (1) {
		if (isPossible(cur_row, cur_col)) {
			cur_row++;
		}
		else if (isLeftPossible(cur_row, cur_col) && isPossible(cur_row, cur_col - 1)) {
			cur_row++;
			cur_col--;
			cur_dir = (cur_dir + 3) % 4;
		}
		else if (isRightPossible(cur_row, cur_col) && isPossible(cur_row, cur_col + 1)) {
			cur_row++;
			cur_col++;
			cur_dir = (cur_dir + 1) % 4;
		}
		else {
			break;
		}
	}

	// 격자 채우고
	grid[cur_row][cur_col] = id;
	for (int dir = 0; dir < 4; dir++) {
		int nx = cur_row + dx[dir];
		int ny = cur_col + dy[dir];

		grid[nx][ny] = id;
	}
	is_exit[cur_row + dx[cur_dir]][cur_col + dy[cur_dir]] = 1;

	// 범위 넘어가면 삭제
	if (isReset()) {
		for (int i = 1; i <= r + 3; i++) {
			for (int j = 1; j <= c; j++) {
				grid[i][j] = 0;
				is_exit[i][j] = 0;
			}
		}
		return;
	}

	//cout << BFS(cur_row, cur_col) - 3 << "\n";
	ans += (BFS(cur_row, cur_col) - 3);
}

void print() {
	cout << "grid" << "\n";
	for (int i = 1; i <= r + 3; i++) {
		for (int j = 1; j <= c; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "exit" << "\n";
	for (int i = 1; i <= r + 3; i++) {
		for (int j = 1; j <= c; j++) {
			cout << is_exit[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> r >> c >> k;

	ans = 0;
	for (int i = 1; i <= k; i++) {
		int col, dir; cin >> col >> dir;
		moveCross(col, dir, i);
		//print();
	}

	cout << ans << "\n";
	return 0;
}