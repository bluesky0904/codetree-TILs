#include <iostream>
#include <utility>
#include <tuple>

#define MAX_N 100
#define ASCII_NUM 128
#define DIR_NUM 4
#define OUT_OF_GRID make_pair(-1, -1)

using namespace std;

int n, m;
int x, y;
int grid[MAX_N][MAX_N];

int u = 1, f = 2, r = 3;

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> NextPos(int x, int y, int move_dir) {
	int dx[DIR_NUM] = {0,0,-1,1};
	int dy[DIR_NUM] = {1,-1,0,0};
	int nx = x + dx[move_dir], ny = y + dy[move_dir];
	if (InRange(nx, ny)) return make_pair(nx, ny);
	else return OUT_OF_GRID;
}

void Simulate(int move_dir) {
	pair<int, int> next_pos = NextPos(x, y, move_dir);
	if (next_pos == OUT_OF_GRID) return;
	tie(x, y) = next_pos;

	if (move_dir == 0) tie(u, f, r) = make_tuple(7 - r, f, u);
	else if (move_dir == 1) tie(u, f, r) = make_tuple(r, f, 7 - u);
	else if (move_dir == 2) tie(u, f, r) = make_tuple(f, 7-u, r);
	else tie(u, f, r) = make_tuple(7-f, u, r);

	int down = 7 - u;
	grid[x][y] = down;
}

int main() {
	cin >> n >> m >> x >> y; x--; y--;
	
	int dir_mapper[ASCII_NUM];
	dir_mapper['R'] = 0;
	dir_mapper['L'] = 1;
	dir_mapper['U'] = 2;
	dir_mapper['D'] = 3;

	grid[x][y] = 6;
	for (int i = 0; i < m; i++) {
		char char_dir; cin >> char_dir;
		Simulate(dir_mapper[char_dir]);
	}

	int ans = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ans += grid[i][j];

	cout << ans;
	return 0;
}