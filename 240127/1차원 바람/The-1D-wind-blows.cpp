#include <iostream>
#include <vector>
using namespace std;

int N, M, Q;

bool InRange(int r) {
	return 0 <= r && r < N;
}

void Simulate(vector<vector<int>>& grid, vector<bool>& check, int r, char d) {
	check[r] = true;
	if (d == 'L') {
		int tmp = grid[r][M - 1];
		for (int i = M - 1; i > 0; i--) {
			grid[r][i] = grid[r][i-1];
		}
		grid[r][0] = tmp;
	}
	else {
		int tmp = grid[r][0];
		for (int i = 0; i < M-1; i++) {
			grid[r][i] = grid[r][i + 1];
		}
		grid[r][M-1] = tmp;
	}
	for (int i = 0; i < M; i++) {
		if (InRange(r + 1) && !check[r+1] && grid[r][i] == grid[r + 1][i]) {
			if (d == 'L') Simulate(grid, check, r + 1, 'R');
			else Simulate(grid, check, r + 1, 'L');
		}
		if (InRange(r - 1) && !check[r-1]  && grid[r][i] == grid[r - 1][i]) {
			if (d == 'L') Simulate(grid, check, r - 1, 'R');
			else Simulate(grid, check, r - 1, 'L');
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M >> Q;
	vector<vector<int>> grid(N, vector<int>(M));
	vector<bool> check(N, false);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> grid[i][j];
		}
	}
	
	for (int i = 0; i < Q; i++) {
		check = vector<bool>(N, false);
		int r;
		char d;
		cin >> r >> d;
		r--;
		Simulate(grid, check, r, d);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}