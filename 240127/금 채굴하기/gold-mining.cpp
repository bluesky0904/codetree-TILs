#include <iostream>
#include <vector>
using namespace std;

int n, m;

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int GetNumOfGold(vector<vector<int>>& grid, int x, int y) {
	int max_gold = 0;
	for (int k = 0; k <= n; k++) {
		int num_of_gold = 0;
		for (int dx = -k; dx <= k; dx++) {
			for (int dy = -k; dy <= k; dy++) {
				if (abs(dx) + abs(dy) <= k && InRange(x + dx, y + dy)) num_of_gold += grid[x + dx][y + dy];
			}
		}
		if (num_of_gold * m >= k * k + (k + 1) * (k + 1)) max_gold = max(max_gold, num_of_gold);
	}
	return max_gold;
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

	int max_gold = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num_of_gold = GetNumOfGold(grid, i, j);
			max_gold = max(max_gold, num_of_gold);
		}
	}
	cout << max_gold << "\n";
}