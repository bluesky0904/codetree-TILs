/*
격자 : n * n, -1 0 그리고 1이상 m이하의 숫자로만 이루어짐
-1 : 검은색 돌
0 : 빨간색 폭탄
1~m : 빨간색과는 다른 서로 다른 색의 폭탄

아래 과정을 더 이상 폭탄 묶음이 없을 때까지 반복
1. 현재 격자에서 크기가 가장 큰 폭탄 묶음을 찾음. 폭탄 묶음이란 2개
이상의 폭탄으로 이루어져 있어야 하며, 모두 같은 색깔의 폭탄으로만
이루어져 있거나 빨간색 폭탄을 포함하여 정확히 2개의 색깔로만 이루어진
폭탄.

다만, 빨간색 폭탄으로만 이루어진 경우는 올바른 폭탄 묶음이 아니며,
모든 폭탄들이 전부 격자 상에서 상하좌우 연결되어 있어야 함.

크기가 가장 큰 폭탄 묶음 = 가장 많은 수의 폭탄들로 이루어진 폭탄 묶음d
여러 개라면 우선순위
(1) 크기가 큰 폭탄 묶음들 중 빨간색 폭탄이 가장 적게 포함된 것
(2) 각 폭탄 묶음의 기준점 중 가장 행이 큰 폭탄 묶음
기준점 = 해당 폭탄 묶음을 이루고 있는 폭탄들 중 빨간색이 아니면서
행이 가장 큰 칸을 의미하며, 만약 행이 가장 큰 폭탄이 여러 개라면,
그 중 열이 가장 작은 칸
(3) 기준점 중 가장 열이 작은 폭탄 묶음

2. 선택된 폭탄 묶음에 해당되는 폭탄들을 전부 제거.
폭탄들이 제거된 이후 중력이 작용하여 위에 있던 폭탄들이 떨어지지만, 
돌은 떨어지지 않음
3. 반시계 방향으로 90도 만큼 격자 판 회전
4. 중력

한 round마다, 폭탄 묶음이 터지면서 폭탄 묶음을 이루고 있는 폭탄의 개수를 C
라 했을 때, C * C만큼의 점수를 얻음.
총 점수 출력
*/
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
		else return a.red_cnt > b.red_cnt;
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
	cout << "/////////////////////(test)///////////////////////";
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
		int cx, cy;tie(cx, cy) = q.front(); q.pop();
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
	bundle.min_col = 1e9;

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
				next_grid[row][col] == -1;
				empty_row = row - 1;
			}
			else {
				next_grid[empty_row][col] = grid[row][col];
				empty_row--;
			}
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
		Explode(x, y); // 이 단계에서 점수 얻어야 함
		Gravity();
		Rotate();
		Gravity();
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