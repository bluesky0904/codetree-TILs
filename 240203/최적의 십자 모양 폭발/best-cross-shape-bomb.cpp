#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 50
#define DIR_NUM 4

int n;
int grid[MAX_N][MAX_N];
int explode_grid[MAX_N][MAX_N];
int drop_grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,-1,0,1};

void InitializeExplodeGrid() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			explode_grid[i][j] = grid[i][j];
		}
	}
}

void InitializeVisited() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Explode(int x, int y, int bomb_size) {
	for (int i = (-1) * bomb_size; i <= bomb_size; i++) {
		if (InRange(x + i, y)) explode_grid[x + i][y] = 0;
	}
	for (int i = (-1) * bomb_size; i <= bomb_size; i++) {
		if (InRange(x, y + i)) explode_grid[x][y + i] = 0;
	}
}

void Drop() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			drop_grid[i][j] = 0;
		}
	}

	for (int j = 0; j < n; j++) {
		int idx = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (explode_grid[i][j] != 0) drop_grid[idx--][j] = explode_grid[i][j];
		}

		for (int i = 0; i < n; i++) {
			explode_grid[i][j] = drop_grid[i][j];
		}
	}
}

int GetPairs() {
	int cnt = 0;
	InitializeVisited();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = true;
			if (explode_grid[i][j] == 0) continue;
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int ni = i + dx[dir];
				int nj = j + dy[dir];
				if (InRange(ni, nj) && !visited[ni][nj] && explode_grid[i][j] == explode_grid[ni][nj]) {
					cnt++;
					visited[ni][nj] = true;
				}
			}
		}
	}
	return cnt;
}

int Simulate(int x, int y) {
	Explode(x, y, explode_grid[x][y] - 1);
	Drop();
	return GetPairs();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	int max_pair = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			InitializeExplodeGrid();
			max_pair = max(max_pair, Simulate(i, j));
		}
	}
	cout << max_pair << "\n";
}