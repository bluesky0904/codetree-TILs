#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;

bool InRange(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

int GetNumOfGold(vector<vector<int>>& grid, int row_s, int row_e, int col_s, int col_e) {
	int num_of_gold = 0;
	for (int i = row_s; i <= row_e; i++) {
		for (int j = col_s; j <= col_e; j++) {
			num_of_gold += grid[i][j];
		}
	}
	return num_of_gold;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	vector<vector<int>> grid(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> grid[i][j];
		}
	}

	int max_gold = 0;
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			if (InRange(row + 2, col + 2)) {
				int num_of_gold = GetNumOfGold(grid, row, row+2, col, col+2);
				max_gold = max(max_gold, num_of_gold);
			}
		}
	}
	cout << max_gold << "\n";
}