#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
vector<vector<int>> grid;

void Simulate(pair<int, int> block) {
	for (int i = 0; i < n; i++) {
		if (grid[0][i] != 0) return;
	}

	for (int i = 1; i < n; i++) {
		for (int j = block.first; j <= block.second; j++) {
			if (grid[i][j] != 0) {
				for (int k = block.first; k <= block.second; k++) {
					grid[i - 1][k] = 1;
				}
				return;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m >> k; k--;
	grid.resize(n, vector<int>(n));
	pair<int, int> block = { k, k + m - 1 };

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	Simulate(block);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout <<  grid[i][j] << " ";
		}
		cout << "\n";
	}
}