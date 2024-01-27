#include <iostream>
#include <vector>
using namespace std;

int n;

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(vector<vector<int>>& grid, int r, int c) {
	int bomb_size = grid[r][c] - 1;
	grid[r][c] = 0;
	for (int i = (-1) * bomb_size; i <= bomb_size; i++) {
		if(InRange(r, c+i)) grid[r][c + i] = 0;
	}
	for (int i = (-1) * bomb_size; i <= bomb_size; i++) {
		if(InRange(r+i, c)) grid[r+i][c] = 0;
	}

	for (int col = 0; col < n; col++) {
		vector<int> tmp(n, 0);
		int idx = n - 1;
		for (int row = n - 1; row >= 0; row--) {
			if (grid[row][col] != 0) {
				tmp[idx--] = grid[row][col];
			}
		}
		for (int row = 0; row < n; row++) {
			grid[row][col] = tmp[row];
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	vector<vector<int>> grid(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}
	int r, c; cin >> r >> c;
	Simulate(grid, r-1, c-1);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}