#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n, k, m;
int max_visited = -1;

vector<pair<int, int>> stone;
vector<pair<int, int>> start_pos;
queue<pair<int, int>> q;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1, 0, 1, 0};
int dy[DIR_NUM] = {0, 1, 0, -1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void BFS() {
	while (!q.empty()) {
		int cx, cy;
		tie(cx, cy) = q.front();
		q.pop();
		for (int i = 0; i < DIR_NUM; i++) {
			int nx = cx + dx[i], ny = cy + dy[i];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 0) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}
}

int CountVisited() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == true) cnt++;
		}
	}
	return cnt;
}

void InitializeVisited() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}
}

void FindMaxVisited(int cnt, int curr_idx) {
	if (cnt == m) {
		InitializeVisited();
		for (int i = 0; i < start_pos.size(); i++) {
			int x, y;
			tie(x, y) = start_pos[i];
			q.push({ x, y });
			visited[x][y] = true;
		}
		BFS();
		if (CountVisited() > max_visited) max_visited = CountVisited();
		return;
	}

	if (curr_idx == (int)stone.size()) return;

	FindMaxVisited(cnt, curr_idx + 1);

	grid[stone[curr_idx].first][stone[curr_idx].second] = 0;
	FindMaxVisited(cnt + 1, curr_idx + 1);
	grid[stone[curr_idx].first][stone[curr_idx].second] = 1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 1) stone.push_back(make_pair(i, j));
		}
	}

	for (int i = 0; i < k; i++) {
		int r, c;
		cin >> r >> c;
		start_pos.push_back({ r - 1, c - 1 });
	}

	FindMaxVisited(0, 0);

	cout << max_visited << "\n";
}