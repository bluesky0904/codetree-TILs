#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100

int n, m, k;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];

void Explode() {
	for (int col = 0; col < n; col++) {
		while (true) {
			int cnt = 1;
			vector<pair<int, int>> explode_pair;
			for (int row = 0; row < n; row++) {
				if (grid[row][col] == 0) continue;
				if (row + 1 < n && grid[row][col] == grid[row + 1][col]) cnt++;
				else {
					if (cnt >= m) explode_pair.push_back({row - cnt + 1,row});
					cnt = 1;
				}
			}

			if (explode_pair.size() == 0) break;

			for (int i = 0; i < explode_pair.size(); i++) {
				for (int j = explode_pair[i].first; j <= explode_pair[i].second; j++) grid[j][col] = 0;
			}

			int temp[MAX_N] = { 0, };
			int idx = n - 1;
			for (int row = n - 1; row >= 0; row--) {
				if (grid[row][col] != 0) temp[idx--] = grid[row][col];
			}

			for (int row = 0; row < n; row++) {
				grid[row][col] = temp[row];
			}
		}
	}
}

void Rotate() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = grid[n - j - 1][i];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}

	for (int col = 0; col < n; col++) {
		int temp[MAX_N] = { 0, };
		int idx = n - 1;
		for (int row = n - 1; row >= 0; row--) {
			if (grid[row][col] != 0) temp[idx--] = grid[row][col];
		}

		for (int row = 0; row < n; row++) {
			grid[row][col] = temp[row];
		}
	}
}

void Simulate() {
	Explode();
	Rotate();
	Explode();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	while (k--) Simulate();

	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] != 0) ans++;
		}
	}

	cout << ans << "\n";
}