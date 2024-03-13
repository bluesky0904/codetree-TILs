#include <iostream>
using namespace std;

#define MAX_N 20
#define DIR_NUM 8

int n, m, k, c;
int eradicated_trees;

int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];
int herbicide_grid[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,1,1,1,0,-1,-1,-1};

void InitializeHerbicideGrid() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			herbicide_grid[x][y] = 0;
		}
	}
}

void InitializeNextGrid() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y] = 0;
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void HerbicideDisappear() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (herbicide_grid[x][y] > 0) herbicide_grid[x][y]--;
		}
	}
}

void TreeGrowth() {
	InitializeNextGrid();

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (grid[x][y] > 0) {
				int cnt = 0;
				for (int dir = 0; dir < DIR_NUM; dir += 2) {
					int nx = x + dx[dir], ny = y + dy[dir];
					if (InRange(nx, ny) && grid[nx][ny] > 0) cnt++;
				}
				next_grid[x][y] = grid[x][y] + cnt;
			}
			if (grid[x][y] == -1) next_grid[x][y] = -1;
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void TreeReproduce() {
	InitializeNextGrid();

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (grid[x][y] > 0 && herbicide_grid[x][y] == 0) {
				int cnt = 0;
				next_grid[x][y] = grid[x][y];

				for (int dir = 0; dir < DIR_NUM; dir += 2) {
					int nx = x + dx[dir], ny = y + dy[dir];
					if (InRange(nx, ny) && herbicide_grid[nx][ny] == 0 && grid[nx][ny] == 0) cnt++;
				}

				if (cnt > 0) {
					int reproduce_cnt = grid[x][y] / cnt;

					for (int dir = 0; dir < DIR_NUM; dir += 2) {
						int nx = x + dx[dir], ny = y + dy[dir];
						if (InRange(nx, ny) && herbicide_grid[nx][ny] == 0 && grid[nx][ny] == 0) {
							next_grid[nx][ny] += reproduce_cnt;
						}
					}
				}
			}
			if (grid[x][y] == -1) next_grid[x][y] = -1;
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void SpreadHerbicide() {
	int max_cnt = -1;
	int mx = -1, my = -1;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (grid[x][y] > 0) {
				int cnt = grid[x][y];
				for (int dir = 1; dir < DIR_NUM; dir += 2) {
					int spread_limit = k;
					int cx = x, cy = y;
					while (spread_limit--) {
						int nx = cx + dx[dir], ny = cy + dy[dir];
						if (InRange(nx, ny)) {
							cx += dx[dir], cy += dy[dir];
							if (herbicide_grid[nx][ny] > 0 || grid[nx][ny] == 0 || grid[nx][ny] == -1) break;
							else cnt += grid[nx][ny];
						}
						else break;
					}
				}
				if (max_cnt < cnt) {
					max_cnt = cnt;
					mx = x;
					my = y;
				}
			}
		}
	}

	if (mx != -1 && my != -1) {
		herbicide_grid[mx][my] = c + 1;
		grid[mx][my] = 0;
		for (int dir = 1; dir < DIR_NUM; dir += 2) {
			int spread_limit = k;
			int cx = mx, cy = my;
			while (spread_limit--) {
				int nx = cx + dx[dir], ny = cy + dy[dir];
				if (InRange(nx, ny)) {
					herbicide_grid[nx][ny] = c + 1;
					cx += dx[dir], cy += dy[dir];
					if (grid[nx][ny] == 0 || grid[nx][ny] == -1) break;
					else grid[nx][ny] = 0;
				}
				else break;
			}
		}
	}

	if(mx != -1 && my != -1) eradicated_trees += max_cnt;
}

void Print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << herbicide_grid[i][j] << " ";
		}
		cout << "\n";
	}

	cout << eradicated_trees << "\n";
	cout << "------------------------\n";
}

void Simulate() {

	HerbicideDisappear();
	//Print();

	TreeGrowth();
	//Print();

	TreeReproduce();
	//Print();

	SpreadHerbicide();
	//Print();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k >> c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	InitializeHerbicideGrid();

	while (m--) Simulate();
	
	cout << eradicated_trees << "\n";
	return 0;
}