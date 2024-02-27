// 뱀이 없는 경우 1, 뱀이 있는 경우 0
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_NUM 100
#define DIR_NUM 4

int n, m;

queue<tuple<int, int, int>> q;
int grid[MAX_NUM][MAX_NUM];
int visited[MAX_NUM][MAX_NUM];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

int BFS() {
	q.push(make_tuple(0, 0, 0));
	visited[0][0] = true;
	while (!q.empty()) {
		int cx, cy, cnt;
		tie(cx, cy, cnt) = q.front();
		q.pop();

		if (cx == n - 1 && cy == m - 1) return cnt;

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 1) {
				q.push(make_tuple(nx, ny, cnt + 1));
				visited[nx][ny] = true;
			}
		}
	}

	return -1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	cout << BFS() << "\n";
	return 0;
}