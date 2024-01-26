#include <iostream>
#include <vector>
using namespace std;

int n, m;
int shape[6][3][3] = {
	{{1, 0, 0},
	{1, 1, 0},
	{0, 0, 0}},

	{{1, 1, 0},
	{1, 0, 0},
	{0, 0, 0}},

	{{1, 1, 0},
	{0, 1, 0},
	{0, 0, 0}},

	{{0, 1, 0},
	{1, 1, 0},
	{0, 0, 0}},

	{{1, 1, 1},
	{0, 0, 0},
	{0, 0, 0}},

	{{1, 0, 0},
	{1, 0, 0},
	{1, 0, 0}},
};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

int GetNum(vector<vector<int>>& grid, int x, int y) {
	int max_num = 0;
	for (int i = 0; i < 6; i++) {
		int num = 0;
		for (int dx = 0; dx < 3; dx++) {
			for (int dy = 0; dy < 3; dy++) {
				if (shape[i][dx][dy] == 1 && InRange(x + dx, y + dy)) num += grid[x + dx][y + dy];
			}
		}
		max_num = max(max_num, num);
	}
	return max_num;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	int max_num = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int num = GetNum(grid, i, j);
			max_num = max(max_num, num);
		}
	}
	cout << max_num << "\n";
}