// [객체 관리]
// 술래말 하나, 도둑말 여러개 (1 ~ 16 번호를 가짐)
// 술래말이 도둑말을 잡을 때마다 잡은 도둑말의 방향을 가짐
// [알고리즘]
// 1. (0, 0)에 있는 도둑말을 잡으며 시작
// 2. 도둑말, 번호가 작은 순서대로 이동,
// 빈칸 || 다른 도둑말이 있는 칸(해당 말과 위치 교체) -> 이동 가능
// 술래말이 있는 칸 || 격자 벗어남 -> 이동 불가
// 이동할 수 있을 때까지 45도 반시계 회전, 이동 불가하면 원위치

#include <iostream>
#include <iomanip>
#include <tuple>
using namespace std;

#define GRID_SIZE 4
#define DIR_NUM 8
#define EMPTY make_pair(-1, -1)
#define CAT make_pair(-2, -2)

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,-1,-1,-1,0,1,1,1};

int max_score = 0;
pair<int, int> grid[GRID_SIZE][GRID_SIZE];

void Print() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			cout << "{" << grid[x][y].first << ", " << grid[x][y].second << "}" << " ";
		}
		cout << "\n";
	}
	cout << "-----------------------\n";
}

bool InRange(int x, int y) {
	return (0 <= x && x < GRID_SIZE && 0 <= y && y < GRID_SIZE);
}

tuple<int, int, int> GetNextPos(int x, int y, int dir) {
	int nx = x + dx[dir], ny = y + dy[dir];
	if (InRange(nx, ny) && grid[nx][ny] != CAT) return make_tuple(nx, ny, dir);
	else {
		for (int i = 1; i < DIR_NUM; i++) {
			int nx = x + dx[(dir + i) % 8], ny = y + dy[(dir + i) % 8];
			if (InRange(nx, ny) && grid[nx][ny] != CAT) {
				grid[x][y].second = (dir + i) % 8;
				return make_tuple(nx, ny, (dir + i) % 8);
			}
		}
		return make_tuple(x, y, dir);
	}
}

void MoveRunner(int move_num) {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if (grid[x][y].first == move_num) {
				int nx, ny, ndir;
				tie(nx, ny, ndir) = GetNextPos(x, y, grid[x][y].second);
				if (make_pair(nx, ny) == make_pair(x, y)) continue;
				else if (grid[nx][ny] == EMPTY) {
					grid[nx][ny] = grid[x][y];
					grid[x][y] = EMPTY;
				}
				else {
					pair<int, int> tmp = grid[nx][ny];
					grid[nx][ny] = grid[x][y];
					grid[x][y] = tmp;
				}
				return;
			}
		}
	}
}

void MoveAllRunner() {
	for (int move_num = 1; move_num <= 16; move_num++) {
		MoveRunner(move_num);
	}
}

// 3. 술래말의 이동
// 이동 가능한 방향의 어느 칸이나 이동할 수 있음
// 한번에 여러개의 칸도 이동할 수 있음
// 술래말이 잡고자하는 도둑말로 이동할 때 지나는 칸들의 말들은 잡지 않음
// 술래말은 도둑말이 있는 곳으로만 이동
// 술래말이 이동할 수 있는 곳에 도둑말이 더이상 존재하지 않으면 게임 종료
// 적절하게 도둑말을 선택하여 점수의 최댓값을 얻고 싶다

bool MovePossible(int cat_x, int cat_y, int cat_dir) {
	for (int i = 1; i <= 4; i++) {
		int nx = cat_x + dx[cat_dir] * i, ny = cat_y + dy[cat_dir] * i;
		if (InRange(nx, ny) && grid[nx][ny] != EMPTY) return true;
	}
	return false;
}

void FindMaxScore(int cat_x, int cat_y, int cat_dir, int score) {
	if (!MovePossible(cat_x, cat_y, cat_dir)) {
		max_score = max(max_score, score);
		return;
	}

	for (int i = 1; i <= 4; i++) {
		int nx = cat_x + dx[cat_dir] * i, ny = cat_y + dy[cat_dir] * i;
		if (InRange(nx, ny) && grid[nx][ny] != EMPTY) {
			pair<int, int> next_grid[GRID_SIZE][GRID_SIZE];
			for (int x = 0; x < GRID_SIZE; x++) {
				for (int y = 0; y < GRID_SIZE; y++) {
					next_grid[x][y] = grid[x][y];
				}
			}

			pair<int, int> tmp = grid[nx][ny]; 
			grid[nx][ny] = CAT;
			grid[cat_x][cat_y] = EMPTY;
			MoveAllRunner();
			FindMaxScore(nx, ny, tmp.second, score + tmp.first);

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
			grid[x][y] = {p, d - 1};
		}
	}

	int init_score, init_dir;
	tie(init_score, init_dir) = grid[0][0];
	grid[0][0] = CAT;
	MoveAllRunner();
	//Print();

	FindMaxScore(0, 0, init_dir, init_score);
	cout << max_score << "\n";
	return 0;
}