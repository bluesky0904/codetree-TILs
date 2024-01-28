#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 4
#define ASCII_NUM 128
#define NONE -1

int n = 4;

vector<vector<int>> grid(MAX_N, vector<int>(MAX_N));
vector<vector<int>> next_grid(MAX_N, vector<int>(MAX_N));


void Rotate() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			next_grid[i][j] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			next_grid[i][j] = grid[n - j - 1][i];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = next_grid[i][j];
}

void Drop() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			next_grid[i][j] = 0;

	for (int j = 0; j < n; j++) {
		int keep_num = NONE, next_row = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (!grid[i][j]) continue;

			if (keep_num == NONE) keep_num = grid[i][j];
			else if (keep_num == grid[i][j]) {
				next_grid[next_row--][j] = keep_num * 2;
				keep_num = NONE;
			}
			else {
				next_grid[next_row--][j] = keep_num;
				keep_num = grid[i][j];
			}
		}
		if (keep_num != NONE) next_grid[next_row--][j] = keep_num;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = next_grid[i][j];
}

void Tilt(int move_dir) {
	for (int i = 0; i < move_dir; i++) Rotate();

	Drop();

	for (int i = 0; i < 4 - move_dir; i++) Rotate();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	char dir;
	cin >> dir;

	int dir_mapper[ASCII_NUM];
	dir_mapper['D'] = 0;
	dir_mapper['R'] = 1;
	dir_mapper['U'] = 2;
	dir_mapper['L'] = 3;

	Tilt(dir_mapper[dir]);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}