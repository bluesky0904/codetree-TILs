#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_NUM 100
#define DIR_NUM 4

int n, m;

int grid[MAX_NUM][MAX_NUM];
bool visited[MAX_NUM][MAX_NUM];
queue<pair<int, int>> q;

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

int BFS() {
	q.push(make_pair(0, 0));
	visited[0][0] = true;
	while (!q.empty()) {
		int cx, cy;
		tie(cx, cy) = q.front();
		q.pop();
		
		if (cx == n - 1 && cy == m - 1) return 1;

		for (int i = 0; i < DIR_NUM; i++) {
			int nx = cx + dx[i], ny = cy + dy[i];
			if (InRange(nx, ny) && grid[nx][ny] == 1 && !visited[nx][ny]) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
			}
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = false;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	cout << BFS() << "\n";
	return 0;
}