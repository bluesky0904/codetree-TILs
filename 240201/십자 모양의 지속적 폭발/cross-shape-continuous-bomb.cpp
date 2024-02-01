#include <iostream>
using namespace std;

#define MAX_N 200

int n, m;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int c) {
	int bomb_size = 0;
	int bomb_pos = 0;
	for (int i = 0; i < n; i++) {
		if (grid[i][c] != 0) {
			bomb_size = grid[i][c] - 1;
			bomb_pos = i;
			break;
		}
	}

	for (int i = (-1)*bomb_size; i <= bomb_size; i++) {
		if (InRange(bomb_pos + i, c)) grid[bomb_pos + i][c] = 0;
	}

	for (int i = (-1) * bomb_size; i <= bomb_size; i++) {
		if (InRange(bomb_pos, c + i)) grid[bomb_pos][c + i] = 0;
	}

	for (int j = 0; j < n; j++) {
		int idx = n - 1;
		int tmp[MAX_N] = {0,};
		for (int i = n-1; i >= 0; i--) {
			if (grid[i][j] != 0) tmp[idx--] = grid[i][j];
		}
		for (int i = 0; i < n; i++) {
			grid[i][j] = tmp[i];
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int c; cin >> c; c--;
		Simulate(c);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout <<  grid[i][j] << " ";
		}
		cout << "\n";
	}
}