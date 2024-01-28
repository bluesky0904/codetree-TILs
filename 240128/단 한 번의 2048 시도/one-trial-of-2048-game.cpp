#include <iostream>
#include <vector>
using namespace std;

#define NONE -1
#define ASCII_NUM 128

int n = 4;

vector<vector<int>> grid(n, vector<int>(n));
vector<vector<int>> next_grid(n, vector<int>(n));

void Rotate() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			next_grid[i][j] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			next_grid[i][j] = grid[n-j-1][i];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = next_grid[i][j];
}

void Drop() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			next_grid[i][j] = 0;

	for (int j = 0; j < n; j++) {
		int keep_num = NONE;
		int idx = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (!grid[i][j]) continue;

			if (keep_num == NONE) keep_num = grid[i][j];
			else if (keep_num == grid[i][j]) {
				next_grid[idx--][j] = 2 * keep_num;
				keep_num = NONE;
			}
			else {
				next_grid[idx--][j] = keep_num;
				keep_num = grid[i][j];
			}
		}
		if (keep_num != NONE) next_grid[idx--][j] = keep_num;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = next_grid[i][j];
}

void Tilt(int dir_num) {
	for (int i = 0; i < dir_num; i++) Rotate();
	Drop();
	for (int i = 0; i < 4- dir_num; i++) Rotate();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> grid[i][j];

	char dir; cin >> dir;
	int dir_num[ASCII_NUM];
	dir_num['D'] = 0;
	dir_num['R'] = 1;
	dir_num['U'] = 2;
	dir_num['L'] = 3;
	Tilt(dir_num[dir]);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	
	return 0;
}