#include <iostream>
#include <tuple>
#include <queue>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

int n, m;
int ans = 0;
int cx, cy, cd;
int u, f, r;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void RollDice() {
	// cx, cy, cd 변수 관리
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
	// u, f, r 변수 관리
	if (cd == 0) {
		int tmp_u = u, tmp_f = f, tmp_r = r;
		u = tmp_f;
		f = 7 - tmp_u;
		r = tmp_r;
	}
	else if (cd == 1) {
		int tmp_u = u, tmp_f = f, tmp_r = r;
		u = 7 - tmp_r;
		f = tmp_f;
		r = tmp_u;
	}
	else if (cd == 2) {
		int tmp_u = u, tmp_f = f, tmp_r = r;
		u = 7 - tmp_f;
		f = tmp_u;
		r = tmp_r;
	}
	else if (cd == 3) {
		int tmp_u = u, tmp_f = f, tmp_r = r;
		u = tmp_r;
		f = tmp_f;
		r = 7 - tmp_u;
	}
}

void BFS(int x, int y, int num) {
	bool visited[MAX_N][MAX_N] = {false, };
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	visited[x][y] = true;
	while(!q.empty()){
		int cur_x, cur_y;
		tie(cur_x, cur_y) = q.front();
		q.pop();
		for (int i = 0; i < DIR_NUM; i++) {
			int nx = cur_x + dx[i];
			int ny = cur_y + dy[i];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == num) {
				visited[nx][ny] = true;
				q.push(make_pair(nx, ny));
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j]) cnt++;
		}
	}
	ans += cnt * num;
}

void GetScore() {
	int x = cx, y = cy;
	int num = grid[x][y];
	BFS(x, y, num);
}

void ChangeDir() {
	if (7 - u > grid[cx][cy]) {
		cd = (cd + 1) % 4;
	}
	else if (7 - u < grid[cx][cy]) {
		cd = (cd + 3) % 4;
	}
}

void Simulate() {
	RollDice();
	GetScore();
	ChangeDir();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	tie(cx, cy, cd) = make_tuple(0, 0, 1);
	tie(u, f, r) = make_tuple(1, 2, 3);
	while (m--) Simulate();
	cout << ans << "\n";
	return 0;
}