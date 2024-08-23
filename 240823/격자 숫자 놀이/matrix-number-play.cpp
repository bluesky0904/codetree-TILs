#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX 100
#define MAX_N 100

int r, c, k;
int n = 3, m = 3;
int grid[MAX_N + 1][MAX_N + 1];

int RowPlay(int row) {
	vector<pair<int, int>> pairs;
	for (int num = 1; num <= 100; num++) {
		int frequency = 0;
		for (int col = 1; col <= m; col++)
			if (grid[row][col] == num)
				frequency++;
		if (frequency)
			pairs.push_back({ frequency, num });
	}

	for (int col = 1; col <= m; col++)
		grid[row][col] = 0;

	sort(pairs.begin(), pairs.end());

	for (int i = 0; i < (int)pairs.size(); i++) {
		int frequency, num;
		tie(frequency, num) = pairs[i];
		grid[row][2 * i + 1] = num;
		grid[row][2 * i + 2] = frequency;
	}

	return pairs.size() * 2;
}

int ColPlay(int col) {
	vector<pair<int, int>> pairs;
	for (int num = 1; num <= 100; num++) {
		int frequency = 0;
		for (int row = 1; row <= n; row++)
			if (grid[row][col] == num)
				frequency++;
		if (frequency)
			pairs.push_back({ frequency, num });
	}

	for (int row = 1; row <= n; row++)
		grid[row][col] = 0;

	sort(pairs.begin(), pairs.end());

	for (int i = 0; i < (int)pairs.size(); i++) {
		int frequency, num;
		tie(frequency, num) = pairs[i];
		grid[2 * i + 1][col] = num;
		grid[2 * i + 2][col] = frequency;
	}

	return pairs.size() * 2;
}

void Simulate() {
	if (n >= m) {
		int max_col = 0;
		for (int row = 1; row <= n; row++)
			max_col = max(max_col, RowPlay(row));
		m = max_col;
	}
	else {
		int max_row = 0;
		for (int col = 1; col <= m; col++)
			max_row = max(max_row, ColPlay(col));
		n = max_row;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> r >> c >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> grid[i][j];

	int ans = -1;
	for (int t = 0; t <= 100; t++) {
		if (grid[r][c] == k) {
			ans = t;
			break;
		}

		Simulate();
	}

	cout << ans << "\n";
	return 0;
}