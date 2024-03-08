#include <iostream>
#include <tuple>
using namespace std;

#define MAX_N 100
#define ASCII_NUM 128
#define DIR_NUM 4

int n, m;
int grid[MAX_N][MAX_N];
pair<int, int> cur_pos;
tuple<int, int, int> dice;

int mapper[ASCII_NUM];
int dx[DIR_NUM] = {0,0,-1,1};
int dy[DIR_NUM] = {-1,1,0,0};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int dir) {
	int cx, cy;
	int u, f, r;
	tie(cx, cy) = cur_pos;
	tie(u, f, r) = dice;
	int nx = cx + dx[dir], ny = cy + dy[dir];
	if (!InRange(nx, ny)) return;

	if (dir == 0) tie(u, f, r) = make_tuple(r, f, 7 - u);
	else if (dir == 1) tie(u, f, r) = make_tuple(7 - r, f, u);
	else if (dir == 2) tie(u, f, r) = make_tuple(f, 7 - u, r);
	else if (dir == 3) tie(u, f, r) = make_tuple(7 - f, u, r);
	cx = nx, cy = ny;
	grid[cx][cy] = 7 - u;
	cur_pos = make_pair(cx, cy);
	dice = make_tuple(u, f, r);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int r, c;
	cin >> n >> m >> r >> c;
	grid[r - 1][c - 1] = 6;
	cur_pos = make_pair(r - 1, c - 1);
	mapper['L'] = 0;
	mapper['R'] = 1;
	mapper['U'] = 2;
	mapper['D'] = 3;

	dice = make_tuple(1, 2, 3);

	for (int i = 0; i < m; i++) {
		char dir;
		cin >> dir;
		Simulate(mapper[dir]);
	}

	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(grid[i][j] != 0) sum += grid[i][j];
		}
	}
	cout << sum << "\n";
}