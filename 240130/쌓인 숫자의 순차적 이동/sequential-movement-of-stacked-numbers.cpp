#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 20
#define DIR_NUM 8
#define OUT_OF_GRID make_pair(-1,-1)

int n, m;
vector<int> grid[MAX_N][MAX_N];

pair<int, int> GetPos(int num) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < grid[i][j].size(); k++) {
				if (grid[i][j][k] == num) return make_pair(i, j);
			}
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> NextPos(pair<int, int> pos) {
	int dx[DIR_NUM] = {-1, -1, -1, 0, 1, 1, 1, 0};
	int dy[DIR_NUM] = {1, 0, -1, -1, -1, 0, 1, 1};
	int x, y; tie(x, y) = pos;
	int max_val = -1;
	pair<int, int> max_pos = OUT_OF_GRID;
	for (int i = 0; i < DIR_NUM; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (InRange(nx, ny)) {
			for (int k = 0; k < grid[nx][ny].size(); k++) {
				if (grid[nx][ny][k] > max_val) {
					max_val = grid[nx][ny][k];
					max_pos = make_pair(nx, ny);
				}
			}
		}
	}
	return max_pos;
}

void Move(pair<int, int> pos, pair<int, int> next_pos, int num) {
	int x, y; tie(x, y) = pos;
	int nx, ny; tie(nx, ny) = next_pos;

	bool to_move = false;
	for (int i = 0; i < grid[x][y].size(); i++) {
		if (grid[x][y][i] == num) to_move = true;
		if (to_move) grid[nx][ny].push_back(grid[x][y][i]);
	}

	while (grid[x][y].back() != num) {
		grid[x][y].pop_back();
	}
	grid[x][y].pop_back();
}

void Simulate(int num) {
	pair<int, int> pos = GetPos(num);
	pair<int, int> next_pos = NextPos(pos);
	if (next_pos != OUT_OF_GRID) Move(pos, next_pos, num);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num; cin >> num;
			grid[i][j].push_back(num);
		}
	}

	while (m--) {
		int num; cin >> num;
		Simulate(num);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j].size() == 0) cout << "None" << "\n";
			else {
				for (int k = grid[i][j].size() - 1; k >= 0; k--) {
					cout << grid[i][j][k] << " ";
				}
				cout << "\n";
			}
		}
	}
	return 0;
}