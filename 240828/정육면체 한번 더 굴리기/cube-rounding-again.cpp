#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n, m;
int ans = 0;
int grid[MAX_N][MAX_N];

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

int cx, cy, cd;
int u, f, r;

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void moveDice() {
	int nx = cx + dx[cd];
	int ny = cy + dy[cd];
	if (!InRange(nx, ny)) {
		cd = (cd + 2) % 4;
		cx += dx[cd];
		cy += dy[cd];
	}
	else {
		cx = nx;
		cy = ny;
	}

	if (cd == 0) {
		int tmp_u = u, tmp_f = f;
		f = 7 - tmp_u;
		u = tmp_f;
	}
	else if (cd == 1) {
		int tmp_u = u,tmp_r = r;
		u = 7 - tmp_r;
		r = tmp_u;
	}
	else if (cd == 2) {
		int tmp_u = u, tmp_f = f;
		u = 7 - tmp_f;
		f = tmp_u;
	}
	else {
		int tmp_u = u, tmp_r = r;
		r = 7 - tmp_u;
		u = tmp_r;
	}
}

void BFS(int x, int y, int num) {
	queue<pair<int, int>> q;
	q.push({ x,y });
	bool visited[MAX_N][MAX_N] = {false};
	visited[x][y] = true;
	int cnt = 1;
	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == num) {
				visited[nx][ny] = true;
				q.push({ nx,ny });
				cnt++;
			}
		}
	}

	ans += cnt * num;
}

void getScore() {
	int x = cx;
	int y = cy;
	int num = grid[x][y];

	BFS(x, y, num);
}

void chageDir() {
	if (7 - u > grid[cx][cy]) {
		cd = (cd + 1) % 4;
	}
	else if(7 - u < grid[cx][cy]) {
		cd = (cd + 3) % 4;
	}
}

void Simulate() {
	moveDice();
	getScore();
	chageDir();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	tie(cx, cy, cd) = make_tuple(0, 0, 1);
	tie(u, f, r) = make_tuple(1, 2, 3);
	while (m--) Simulate();

	cout << ans << '\n';
	return 0;
}