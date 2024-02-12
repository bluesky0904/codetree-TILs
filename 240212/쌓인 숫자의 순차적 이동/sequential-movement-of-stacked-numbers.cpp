#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 20
#define DIR_NUM 8
#define OUT_OF_GRID make_pair(-1,-1)
int n, m;
vector<int> grid[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,-1,-1,0,1,1,1,0};
int dy[DIR_NUM] = {1,0,-1,-1,-1,0,1,1};

pair<int, int> GetNumPos(int num) {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int i = 0; i < grid[x][y].size(); i++) {
				if (grid[x][y][i] == num) return make_pair(x, y);
			}
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> GetNextPos(pair<int, int> pos) {
	int x, y;
	tie(x, y) = pos;
	int max_val = -1;
	int mx, my;
	pair<int, int> max_pos = OUT_OF_GRID;
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = x + dx[dir], ny = y + dy[dir];
		if (InRange(nx, ny)) {
			for (int i = 0; i < grid[nx][ny].size(); i++) {
				if (grid[nx][ny][i] > max_val) {
					max_val = grid[nx][ny][i];
					max_pos = make_pair(nx, ny);
				}
			}
		}
	}
	return max_pos;
}

void Move(pair<int, int> pos, pair<int, int> next_pos, int num) {
	int x, y;
	tie(x, y) = pos;
	int nx, ny;
	tie(nx, ny) = next_pos;

	bool to_move = false;
	for (int i = 0; i < grid[x][y].size(); i++) {
		if (grid[x][y][i] == num) to_move = true;
		if (to_move) grid[nx][ny].push_back(grid[x][y][i]);
	}

	while (grid[x][y].back() != num) grid[x][y].pop_back();
	grid[x][y].pop_back();
}

void Simulate(int num) {
	pair<int, int> pos = GetNumPos(num);
	pair<int, int> next_pos = GetNextPos(pos);
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

	for (int i = 0; i < m; i++) {
		int num; cin >> num;
		Simulate(num);
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (grid[x][y].size() == 0) cout << "None" << "\n";
			else {
				for (int i = grid[x][y].size() - 1; i >= 0; i--) {
					cout << grid[x][y][i] << " ";
				}
				cout << "\n";
			}
		}
	}
	return 0;
}