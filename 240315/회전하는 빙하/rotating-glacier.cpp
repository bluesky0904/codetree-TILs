// 인접 회전성
// 빙하를 회전하는 범위를 레벨이라고 함
// 레벨이 L일 때 2^L * 2^L만큼 격자를 선택하여 2^(L-1) * 2^(L-1)만큼 잘라 4등분하여 회전시키게 됨
// 회전 방향 = 시계 방향
// 회전이 끝나고 난 뒤에는 빙하에 속한 얼음이 녹음
// 한 칸을 기준으로 상하좌우 인접한 칸에 얼음이 3개 이상 있는 경우에는 녹지 않음
// 그렇지 않은 경우에는 -1
// 얼음이 녹는 것은 동시에 진행됨
// 남아있는 빙하의 총 양, 가장 큰 얼음 군집의 크기 출력
#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;

#define MAX_NUM 64
#define DIR_NUM 4

int n, q;
int grid_size;
int max_glac = 0;

queue<pair<int, int>> que;
int grid[MAX_NUM][MAX_NUM];
int next_grid[MAX_NUM][MAX_NUM];
int visited[MAX_NUM][MAX_NUM];

int dx[DIR_NUM] = {0,1,0,-1};
int dy[DIR_NUM] = {1,0,-1,0};

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

	// 묶어서 생각하기 보다는 각각의 grid가 어떻게 이동하는지를 생각해보자
	// 90도 시계방향 회전 로직 next_grid[x][y] = grid[n - y - 1][x]
	// dx, dy 테크닉으로 해결하자
	int box_size = (int)pow(2, level);
	int half_size = box_size / 2;
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
				if (cnt < 3) next_grid[x][y] = grid[x][y] - 1;
				else next_grid[x][y] = grid[x][y];
			}
		}
	}

	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

void Print() {
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "--------------------------------\n";
}

void Simulate(int level) {
	Rotate(level);
	//Print();

	Melt();
	//Print();
}

int CountGrid() {
	int sum = 0;
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			sum += grid[i][j];
		}
	}
	return sum;
}

int BFS(int x, int y) {
	int cnt = 1;
	que.push({ x, y });
	visited[x][y] = true;
	while (!que.empty()) {
		int cx, cy;
		tie(cx, cy) = que.front();
		que.pop();
		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] > 0) {
				que.push({ nx, ny });
				visited[nx][ny] = true;
				cnt++;
			}
		}
	}
	return cnt;
}

void FindMaxGlac() {
	for (int x = 0; x < grid_size; x++) {
		for (int y = 0; y < grid_size; y++) {
			if (!visited[x][y] && grid[x][y] > 0) {
				max_glac = max(max_glac, BFS(x, y));
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	grid_size = (int)pow(2, n);

	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			cin >> grid[i][j];
		}
	}

	while (q--) {
		int level;
		cin >> level;
		Simulate(level);
	}

	cout << CountGrid() << "\n";
	FindMaxGlac();
	cout << max_glac << "\n";
	return 0;
}