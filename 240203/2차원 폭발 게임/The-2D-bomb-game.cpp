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
			for (int i = 0; i < n; i++) {
				if (i + 1 < n && grid[i][col] != 0 && grid[i+1][col] != 0 && grid[i][col] == grid[i + 1][col]) cnt++;
				else {
					if(cnt >= m) explode_pair.push_back({ i - cnt + 1, i });
					cnt = 1;
				}
			}
			
			if (explode_pair.size() == 0) break;

			for (int i = 0; i < explode_pair.size(); i++) {
				for (int row = explode_pair[i].first; row <= explode_pair[i].second; row++) {
					grid[row][col] = 0;
				}
			}

			int tmp[MAX_N] = {0,};
			int idx = n - 1;
			for (int i = n - 1; i >= 0; i--) {
				if (grid[i][col] != 0) tmp[idx--] = grid[i][col];
			}
			for (int i = 0; i < n; i++) {
				grid[i][col] = tmp[i];
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
		int tmp[MAX_N] = { 0, };
		int idx = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (grid[i][col] != 0) tmp[idx--] = grid[i][col];
		}
		for (int i = 0; i < n; i++) {
			grid[i][col] = tmp[i];
		}
	}
}

void Simulate() {
	Explode();
	Rotate();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	while(k--) Simulate();
	Explode();

	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] != 0) ans++;
		}
	}

	cout << ans << "\n";
	return 0;
}