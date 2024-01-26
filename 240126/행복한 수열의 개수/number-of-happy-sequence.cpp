#include <iostream>
#include <vector>
using namespace std;

int n, m;

bool IsGoodNumCol(vector<vector<int>>& grid, int row) {
	int cnt = 1;
	for (int i = 0; i < n-1; i++) {
		if (grid[row][i] == grid[row][i + 1]) {
			cnt++;
		}
		else {
			if (cnt >= m) return true;
			cnt = 1;
		}
	}
	if (cnt >= m) return true;
	return false;
}

bool IsGoodNumRow(vector<vector<int>>& grid, int col) {
	int cnt = 1;
	for (int i = 0; i < n - 1; i++) {
		if (grid[i][col] == grid[i+1][col]) {
			cnt++;
		}
		else {
			if (cnt >= m) return true;
			cnt = 1;
		}
	}
	if (cnt >= m) return true;
	return false;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (IsGoodNumCol(grid, i)) ans++;
		if (IsGoodNumRow(grid, i)) ans++;
	}
	cout << ans << "\n";
	return 0;
}