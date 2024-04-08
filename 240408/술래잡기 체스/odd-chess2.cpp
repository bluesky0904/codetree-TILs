#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define GRID_SIZE 4
#define DIR_NUM 8
#define EMPTY make_pair(-1,-1)
#define TAG make_pair(-2, -2)

int dx[DIR_NUM] = { -1,-1,0,1,1,1,0,-1 };
int dy[DIR_NUM] = { 0,-1,-1,-1,0,1,1,1 };

int max_score = 0;
pair<int, int> grid[GRID_SIZE][GRID_SIZE];

void Print() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			cout << "{" << grid[x][y].first << ", " << grid[x][y].second << "}" << " ";
		}
		cout << "\n";
	}
	cout << "----------------------------\n";
}

bool InRange(int x, int y) {
	return 0 <= x && x < GRID_SIZE && 0 <= y && y < GRID_SIZE;
}

bool MovePossible(int tag_x, int tag_y, int tag_dir) {
	for (int dist = 1; dist <= 3; dist++) {
		int nx = tag_x + dx[tag_dir] * dist, ny = tag_y + dy[tag_dir] * dist;
		if (InRange(nx, ny) && grid[nx][ny] != EMPTY) return true;
	}
	return false;
}

void MoveRunner(int num) {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if (grid[x][y].first == num) {
				int dir = grid[x][y].second;
				for (int i = 0; i < DIR_NUM; i++) {
					int nx = x + dx[(dir + i) % 8], ny = y + dy[(dir + i) % 8];
					if (InRange(nx, ny) && grid[nx][ny] != TAG) {
						grid[x][y].second = dir + i;
						pair<int, int> temp = grid[nx][ny];
						grid[nx][ny] = grid[x][y];
						grid[x][y] = temp;
						return;
					}
				}
			}
		}
	}
}

void MoveAllRunner() {
	for (int num = 1; num <= GRID_SIZE * GRID_SIZE; num++) {
		MoveRunner(num);
	}
}

void FindMaxScore(int tag_x, int tag_y, int tag_dir, int score) {
	if (!MovePossible(tag_x, tag_y, tag_dir)) {
		max_score = max(max_score, score);
		return;
	}

	for (int i = 1; i < GRID_SIZE; i++) {
		int nx = tag_x + dx[tag_dir] * i, ny = tag_y + dy[tag_dir] * i;
		if (InRange(nx, ny) && grid[nx][ny] != EMPTY) {

			pair<int, int> next_grid[GRID_SIZE][GRID_SIZE];
			for (int x = 0; x < GRID_SIZE; x++) {
				for (int y = 0; y < GRID_SIZE; y++) {
					next_grid[x][y] = grid[x][y];
				}
			}

			grid[tag_x][tag_y] = EMPTY;
			pair<int, int> temp = grid[nx][ny];
			grid[nx][ny] = TAG;
			MoveAllRunner();
			FindMaxScore(nx, ny, temp.second, score + temp.first);

			for (int x = 0; x < GRID_SIZE; x++) {
				for (int y = 0; y < GRID_SIZE; y++) {
					grid[x][y] = next_grid[x][y];
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			int p, d;
			cin >> p >> d;
			grid[x][y] = make_pair(p, d - 1);
		}
	}
	
	pair<int, int> temp = grid[0][0];
	grid[0][0] = TAG;
	MoveAllRunner();
	FindMaxScore(0, 0, temp.second, max_score + temp.first);

	cout << max_score << "\n";
	return 0;
}