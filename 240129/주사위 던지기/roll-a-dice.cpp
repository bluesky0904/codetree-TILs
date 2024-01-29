#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define DIR_NUM 4
#define ASCII_NUM 128

int n, m;
int r, c;
vector<vector<int>> grid;
tuple<int, int, int> dice; // 바닥, 오른쪽, 위

int dx[DIR_NUM] = {0,0,-1,1};
int dy[DIR_NUM] = {-1,1,0,0};

//dice = make_tuple(6, 3, 5);  바닥, 오른쪽, 위

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int dir) {

	if (!InRange(r + dx[dir], c + dy[dir])) return;

	if (dir == 0) { // 왼쪽
		int bottom_side = 7 - get<1>(dice);
		int right_side = get<0>(dice);
		int up_side = get<2>(dice); 
		dice = make_tuple(bottom_side, right_side, up_side);
	}
	else if(dir == 1) { // 오른쪽
		int bottom_side = get<1>(dice);
		int right_side = 7 - get<0>(dice);
		int up_side = get<2>(dice);
		dice = make_tuple(bottom_side, right_side, up_side);
	}
	else if (dir == 2) { // 위쪽
		int bottom_side = get<2>(dice);
		int right_side = get<1>(dice);
		int up_side = 7 - get<0>(dice);
		dice = make_tuple(bottom_side, right_side, up_side);
	}
	else if (dir == 3) { // 아래쪽
		int bottom_side = 7 - get<2>(dice);
		int right_side = get<1>(dice);
		int up_side = get<0>(dice);
		dice = make_tuple(bottom_side, right_side, up_side);
	}

	r += dx[dir];
	c += dy[dir];
	grid[r][c] = get<0>(dice);
	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	cin >> r >> c;
	r--; c--;
	grid.resize(n, vector<int>(n, 0));
	dice = make_tuple(6, 3, 5);
	grid[r][c] = 6;

	int dir[ASCII_NUM];
	dir['L'] = 0;
	dir['R'] = 1;
	dir['U'] = 2;
	dir['D'] = 3;

	for (int i = 0; i < m; i++) {
		char dir_char; cin >> dir_char;
		Simulate(dir[dir_char]);
	}

	int grid_sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(grid[i][j] != 0) grid_sum += grid[i][j];
		}
	}
	cout << grid_sum << "\n";
}