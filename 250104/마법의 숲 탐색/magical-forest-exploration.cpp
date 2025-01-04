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
			if (InRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == grid[cx][cy] || (grid[nx][ny] != 0 &&out_pos[cx][cy]))) {
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