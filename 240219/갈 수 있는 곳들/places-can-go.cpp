#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n, k;

int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
queue<pair<int, int>> q;

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

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
			if (InRange(nx, ny) && grid[nx][ny] == 0 && !visited[nx][ny]) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
			}
		}
	}
}

int CountVisited() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j]) cnt++;
		}
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int r, c;
		cin >> r >> c;
		r--; c--;
		q.push(make_pair(r, c));
		visited[r][c] = true;
	}

	BFS();

	cout << CountVisited() << "\n";
}