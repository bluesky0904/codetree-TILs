#include <iostream>
#include <tuple>
using namespace std;

#define MAX_N 100
#define ASCII_NUM 128
#define DIR_NUM 4
#define OUT_OF_GRID make_pair(-1,-1)

int n, m;
int x, y;
int u = 1, f = 2, r = 3;
int grid[MAX_N][MAX_N];

int mapper[ASCII_NUM];
int dx[DIR_NUM] = {0,0,-1,1};
int dy[DIR_NUM] = {-1,1,0,0};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> NextPos(int x, int y, int dir) {
	int nx = x + dx[dir], ny = y + dy[dir];
	if (InRange(nx, ny)) return make_pair(nx, ny);
	else return OUT_OF_GRID;
}

void Simulate(int dir) {
	pair<int, int> next_pos = NextPos(x, y, dir);

	if (next_pos == OUT_OF_GRID) return;

	tie(x, y) = next_pos;

	if (dir == 0) tie(u, f, r) = make_tuple(r, f, 7 - u);
	else if (dir == 1) tie(u, f, r) = make_tuple(7 - r, f, u);
	else if (dir == 2) tie(u, f, r) = make_tuple(f, 7 - u, r);
	else if (dir == 3) tie(u, f, r) = make_tuple(7 - f, u, r);

	grid[x][y] = 7 - u;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int r, c;
	cin >> n >> m >> r >> c;
	grid[r - 1][c - 1] = 6;
	x = r - 1, y = c - 1;
	mapper['L'] = 0;
	mapper['R'] = 1;
	mapper['U'] = 2;
	mapper['D'] = 3;

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