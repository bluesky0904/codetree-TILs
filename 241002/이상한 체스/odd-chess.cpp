#define _CRT_SECURE_NO_WARNINGS
/*

// 비어있음에도 자신의 말을 이용해서 갈 수 없는 체스판의 영역 넓이의 총 합의 최솟값 출력

5 4
0 0 0 0
0 2 0 6
0 0 0 5
0 1 0 0
0 0 0 0

v : 2 5 1
*/

#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

#define GRID_SIZE 8
#define CHESS_TYPE_NUM 5
#define DIR_NUM 4

int n, m;
int ans = GRID_SIZE * GRID_SIZE;
int grid[GRID_SIZE][GRID_SIZE];
vector<pair<int, int>> v;

int piece_dir[GRID_SIZE][GRID_SIZE];
bool visited[GRID_SIZE][GRID_SIZE];

bool can_move[CHESS_TYPE_NUM + 1][DIR_NUM] = {
	{},
	{1, 0, 0, 0},
	{0, 1, 0, 1},
	{1, 1, 0, 0},
	{1, 1, 0, 1},
	{1, 1, 1, 1}
};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

bool CanGo(int x, int y) {
	return InRange(x, y) && grid[x][y] != 6;
}

void Fill(int sx, int sy, int piece_num, int face_dir) {
	int dx[DIR_NUM] = { -1, 0, 1, 0 };
	int dy[DIR_NUM] = { 0, 1, 0, -1 };

	for (int i = 0; i < 4; i++) {
		if (!can_move[piece_num][i]) continue;

		int x = sx, y = sy;
		int move_dir = (i + face_dir) % 4;
		while (true) {
			visited[x][y] = true;
			int nx = x + dx[move_dir], ny = y + dy[move_dir];
			if (CanGo(nx, ny)) {
				x = nx; y = ny;
			}
			else break;
		}
	}
}

int GetArea() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = 0;
		}
	}

	for (int i = 0; i < (int)v.size(); i++) {
		int x, y;
		tie(x, y) = v[i];
		Fill(x, y, grid[x][y], piece_dir[x][y]);
	}

	int area = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j] == 0 && grid[i][j] != 6) area++;
		}
	}

	return area;
}

void FindMinArea(int idx) {
	if (idx == (int)v.size()) {
		ans = min(ans, GetArea());
		return;
	}

	int x, y;
	tie(x, y) = v[idx];
	
	for (int i = 0; i < 4; i++) {
		piece_dir[x][y] = i;
		FindMinArea(idx + 1);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
			if (1 <= grid[i][j] && grid[i][j] <= 5)
				v.push_back(make_pair(i, j));
		}
	}

	FindMinArea(0);

	cout << ans << "\n";
	return 0;
}