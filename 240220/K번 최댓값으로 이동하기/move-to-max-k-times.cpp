#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4
#define NOT_EXISTS make_pair(-1,-1)

int n, k;

pair<int, int> curr_pos;
queue<pair<int, int>> q;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

void InitializeVisited() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void BFS() {
	int cx, cy;
	tie(cx, cy) = curr_pos;
	int curr_num = grid[cx][cy];
	q.push(curr_pos);
	visited[cx][cy] = true;
	while (!q.empty()) {
		int cx, cy;
		tie(cx, cy) = q.front();
		q.pop();
		for (int i = 0; i < DIR_NUM; i++) {
			int nx = cx + dx[i], ny = cy + dy[i];
			if (InRange(nx, ny) && !visited[nx][ny] && curr_num > grid[nx][ny]) {
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
			if (!visited[i][j] || make_pair(i, j) == curr_pos) continue;
			pair<int, int> new_pos = make_pair(i, j);
			if (NeedUpdate(best_pos, new_pos)) best_pos = new_pos;
		}
	}

	if (best_pos == NOT_EXISTS) return false;
	else {
		curr_pos = best_pos;
		return true;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}
	int r, c;
	cin >> r >> c;
	curr_pos = make_pair(r - 1, c - 1);

	while (k--) {
		bool to_move = Move();
		if (!to_move) break;
	}

	cout << curr_pos.first + 1 << " " << curr_pos.second + 1 << "\n";
}