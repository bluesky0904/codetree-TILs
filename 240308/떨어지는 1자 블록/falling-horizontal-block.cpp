#include <iostream>
using namespace std;

#define MAX_N 100

int n, m, k;
int grid[MAX_N][MAX_N];

void Simulate() {
	for (int i = 0; i < n; i++) {
		if (i == n - 1) {
			for (int j = 0; j < m; j++) {
				grid[i][k - 1 + j] = 1;
			}
		}

		bool is_possible = true;
		for (int j = 0; j < m; j++) {
			if (grid[i+1][k - 1 + j] == 1) is_possible = false;
		}

		if (is_possible) {
			continue;
		}
		else {
			for (int j = 0; j < m; j++) {
				grid[i][k - 1 + j] = 1;
			}
			return;
		}
	}
}

int main() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	Simulate();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}