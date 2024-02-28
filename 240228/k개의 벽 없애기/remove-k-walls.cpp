#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n, k;
pair<int, int> start_pos;
pair<int, int> end_pos;
int min_time = INT_MAX;

int grid[MAX_N][MAX_N];
int new_grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
vector<pair<int, int>> wall;
vector<pair<int, int>> selected;

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Initialize() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			new_grid[i][j] = grid[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}
}

int BFS() {
	Initialize();

	for (int i = 0; i < selected.size(); i++) {
		int x, y;
		tie(x, y) = selected[i];
		new_grid[x][y] = 0;
	}

	int x, y;
	tie(x, y) = start_pos;
	queue<tuple<int, int, int>> q;
	q.push(make_tuple(x, y, 0));
	visited[x][y] = true;
	while (!q.empty()) {
		int cx, cy, cnt;
		tie(cx, cy, cnt) = q.front();
		q.pop();

		if (make_pair(cx, cy) == end_pos) return cnt;

		for (int i = 0; i < DIR_NUM; i++) {
			int nx = cx + dx[i], ny = cy + dy[i];
			if (InRange(nx, ny) && !visited[nx][ny] && new_grid[nx][ny] == 0) {
				q.push(make_tuple(nx, ny, cnt + 1));
				visited[nx][ny] = true;
			}
		}
	}
	return INT_MAX;
}

void FindMinTime(int curr_idx, int cnt) {
	if (cnt == k) {
		min_time = min(min_time, BFS());
		return;
	}

	if (curr_idx == wall.size()) return;

	FindMinTime(curr_idx + 1, cnt);
	selected.push_back(wall[curr_idx]);
	FindMinTime(curr_idx + 1, cnt + 1);
	selected.pop_back();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 1) wall.push_back(make_pair(i, j));
		}
	}

	int r, c;
	cin >> r >> c;
	start_pos = make_pair(r - 1, c - 1);
	cin >> r >> c;
	end_pos = make_pair(r - 1, c - 1);
	
	FindMinTime(0, 0);

	if (min_time == INT_MAX) min_time = -1;
	cout << min_time << "\n";
	return 0;
}