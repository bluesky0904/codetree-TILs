#include <iostream>
#include <tuple>
#include <queue>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4
#define NOT_EXISTS make_pair(-1,-1);

int n, k;

int grid[MAX_N][MAX_N];
pair<int, int> curr_cell;
queue<pair<int, int>> q;
bool visited[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int target_num) {
	return InRange(x, y) && !visited[x][y] && grid[x][y] < target_num;
}

void InitializeVisited() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}
}

void BFS() {
	int cx, cy;
	tie(cx, cy) = curr_cell;
	q.push(curr_cell);
	visited[cx][cy] = true;

	int target_num = grid[cx][cy];

	while (!q.empty()) {
		pair<int, int> curr_pos = q.front();
		int cx, cy;
		tie(cx, cy) = curr_pos;
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (CanGo(nx, ny, target_num)) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
			}
		}
	}
}

bool NeedUpdate(pair<int, int> best_pos, pair<int, int> new_pos) {
	if (best_pos == NOT_EXISTS) return true;

	int bx, by;
	tie(bx, by) = best_pos;

	int nx, ny;
	tie(nx, ny) = new_pos;

	return make_tuple(grid[nx][ny], -nx, -ny) > make_tuple(grid[bx][by], -bx, -by);
}

bool Move() {
	InitializeVisited();
	BFS();
	pair<int, int> best_pos = NOT_EXISTS;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!visited[i][j] || make_pair(i, j) == curr_cell) continue;
			pair<int, int> new_pos = make_pair(i, j);
			if (NeedUpdate(best_pos, new_pos)) best_pos = new_pos;
		}
	}
	if (best_pos == NOT_EXISTS) return false;
	else {
		curr_cell = best_pos;
		return true;
	}
}

int main() {
	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	int r, c;
	cin >> r >> c;
	curr_cell = make_pair(r - 1, c - 1);

	while (k--) {
		bool is_moved = Move();
		if (!is_moved) break;
	}

	int fx, fy;
	tie(fx, fy) = curr_cell;
	cout << fx + 1 << " " << fy + 1;
}