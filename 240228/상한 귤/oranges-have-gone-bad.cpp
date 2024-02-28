// 0은 해당 칸에 아무것도 놓여있지 않음
// 1은 해당 칸에 귤이 놓여있음
// 2는 해당 칸에 상한 귤이 처음부터 놓여 있음

#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n, k;

queue<tuple<int, int, int>> q;
int grid[MAX_N][MAX_N];
int rslt[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void BFS() {
	while (!q.empty()) {
		int cx, cy, cnt;
		tie(cx, cy, cnt) = q.front();
		q.pop();
		
		if (grid[cx][cy] == 2) rslt[cx][cy] = cnt;

		for (int i = 0; i < DIR_NUM; i++) {
			int nx = cx + dx[i], ny = cy + dy[i];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 1) {
				q.push(make_tuple(nx, ny, cnt + 1));
				visited[nx][ny] = true;
				grid[nx][ny] = 2;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0) rslt[i][j] = -1;
			if (grid[i][j] == 1) rslt[i][j] = -2;
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 2) q.push(make_tuple(i, j, 0));
			rslt[i][j] = 0;
		}
	}
	BFS();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << rslt[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}