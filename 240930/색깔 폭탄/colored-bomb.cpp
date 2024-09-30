#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

struct Bundle {
	int max_cnt, red_cnt, max_row, min_col;
};

bool Cmp(Bundle a, Bundle b) {
	if (a.max_cnt == b.max_cnt) {
		if (a.red_cnt == b.red_cnt) {
			if (a.max_row == b.max_row) {
				return a.min_col < b.min_col;
			}
			else return a.max_row > b.max_row;
		}
		else return a.red_cnt < b.red_cnt;
	}
	else return a.max_cnt > b.max_cnt;
}

int n, m;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];

int ans = 0;

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

void Print() {
	cout << "/////////////////////(test)///////////////////////\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

Bundle BFS(int x, int y) {
	Bundle bundle;
	int total_cnt = 0, red_cnt = 0;
	int color = grid[x][y];

	queue<pair<int, int>> q;
	bool visited[MAX_N][MAX_N] = { false };
	q.push({ x, y });
	visited[x][y] = true;
	total_cnt++;

	while (!q.empty()) {
		int cx, cy; tie(cx, cy) = q.front(); q.pop();
		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == color || grid[nx][ny] == 0)) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
				if (grid[nx][ny] == 0) red_cnt++;
				total_cnt++;
			}
		}
	}
	bundle.max_cnt = total_cnt;
	bundle.red_cnt = red_cnt;
	bundle.max_row = x;
	bundle.min_col = y;

	return bundle;
}

pair<int, int> FindMaxBomb() {
	Bundle bundle;
	bundle.max_cnt = -1;
	bundle.red_cnt = -1;
	bundle.max_row = -1;
	bundle.min_col = n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == -2 || grid[i][j] == -1 || grid[i][j] == 0) continue;
			Bundle bfs_bundle = BFS(i, j);
			if (Cmp(bfs_bundle, bundle)) bundle = bfs_bundle;
		}
	}

	if (bundle.max_cnt < 2) return make_pair(-1, -1);
	else return make_pair(bundle.max_row, bundle.min_col);
}

void Explode(int x, int y) {
	int total_cnt = 0;
	int color = grid[x][y];


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = grid[i][j];
		}
	}

	queue<pair<int, int>> q;
	bool visited[MAX_N][MAX_N] = { false };
	q.push({ x, y });
	visited[x][y] = true;
	next_grid[x][y] = -2;
	total_cnt++;

	while (!q.empty()) {
		int cx, cy; tie(cx, cy) = q.front(); q.pop();
		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == color || grid[nx][ny] == 0)) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
				next_grid[nx][ny] = -2;
				total_cnt++;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}

	ans += (total_cnt * total_cnt);
}

void Gravity() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = -2;
		}
	}

	for (int col = 0; col < n; col++) {
		int empty_row = n - 1;
		for (int row = n- 1; row >= 0; row--) {
			if (grid[row][col] == -2) continue;
			else if (grid[row][col] == -1) {
				next_grid[row][col] = -1;
				empty_row = row - 1;
			}
			else {
				next_grid[empty_row][col] = grid[row][col];
				empty_row--;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

void Rotate() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = -2;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[n-j-1][i] = grid[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

bool Simulate(){
	int x, y;
	tie(x, y) = FindMaxBomb();
	if (x == -1 && y == -1) return false;
	else {
		Print();
		Explode(x, y); // 이 단계에서 점수 얻어야 함
		Print();
		Gravity();
		Print();
		Rotate();
		Print();
		Gravity();
		Print();
		return true;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	while (1) {
		if (!Simulate()) break;
	}

	cout << ans << "\n";
	return 0;
}