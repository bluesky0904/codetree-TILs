// 각 구슬은 일정 속도를 갖고 정해진 방향으로 움직임
// 구슬이 벽에 부딪히면 움직이는 방향이 반대로 뒤집힘, 이때 시간이 전혀 소요되지 않음
// 동일한 위치에 구슬이 k개를 넘는다면 우선 순위가 높은 구슬 k개만 살아남고 나머지는 전부 사라짐
// 구슬의 속도가 빠른 구슬일수록, 속도가 일치할 경우 구슬의 번호가 더 큰 구슬일수록 우선순위가 높다

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define DIR_NUM 4
#define MAX_N 50
#define ASCII_NUM 128

typedef tuple<int, int, int> Marble;


int n, m, t, k;
vector<Marble> grid[MAX_N][MAX_N];
vector<Marble> next_grid[MAX_N][MAX_N];
int mapper[ASCII_NUM];
int dx[DIR_NUM] = { -1, 0, 0, 1 };
int dy[DIR_NUM] = { 0, 1, -1, 0 };

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

Marble NextPos(int x, int y, int vnum, int move_dir) {
	while (vnum--) {
		int nx = x + dx[move_dir], ny = y + dy[move_dir];
		if (!InRange(nx, ny)) {
			move_dir = 3 - move_dir;
			nx = x + dx[move_dir]; ny = y + dy[move_dir];
		}
		x = nx; y = ny;
	}
	return make_tuple(x, y, move_dir);
}


void MoveAll() {
	for(int x = 0; x < n; x++)
		for(int y = 0; y < n; y++)
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				int v, num, move_dir;
				tie(v, num, move_dir) = grid[x][y][i];

				int nx, ny, ndir;
				tie(nx, ny, ndir) = NextPos(x, y, -v, move_dir);
				next_grid[nx][ny].push_back(make_tuple(v, num, ndir));
			}
}

void SelectMarbles(){
	for (int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			while (next_grid[i][j].size() > k) {
				sort(next_grid[i][j].begin(), next_grid[i][j].end());
				next_grid[i][j].pop_back();
			}
}

void Simulate() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			next_grid[i][j].clear();

	MoveAll();

	SelectMarbles();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = next_grid[i][j];
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> t >> k;

	mapper['U'] = 0;
	mapper['R'] = 1;
	mapper['L'] = 2;
	mapper['D'] = 3;

	for (int i = 0; i < m; i++) {
		int r, c, v; char d;
		cin >> r >> c >> d >> v;
		grid[r - 1][c - 1].push_back(make_tuple(-v, -(i + 1), mapper[d]));
	}

	while (t--) Simulate();

	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ans += (int)grid[i][j].size();

	cout << ans;
}