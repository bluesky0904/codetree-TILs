#include <iostream>
#include <tuple>
#include <cmath>
using namespace std;

typedef tuple<int, int, int, int> Cell;

#define MAX_N 20
#define MAX_NUM 400
#define DIR_NUM 4
#define EMPTY 0

int n;
int target_num[MAX_NUM + 1];
int rides[MAX_N + 1][MAX_N + 1];
bool friends[MAX_NUM + 1][MAX_NUM + 1];

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool InRange(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

Cell GetCurCell(int num, int x, int y) {
	int friend_cnt = 0, empty_cnt = 0;
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = x + dx[dir], ny = y + dy[dir];
		if (InRange(nx, ny)) {
			if (rides[nx][ny] == EMPTY) empty_cnt++;
			else if (friends[num][rides[nx][ny]]) friend_cnt++;
		}
	}
	return make_tuple(friend_cnt, empty_cnt, -x, -y);
}

void Move(int num) {
	Cell best_cell = make_tuple(0, 0, -(n + 1), -(n + 1));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (rides[i][j] == EMPTY) {
				Cell cur_cell = GetCurCell(num, i, j);

				if (best_cell < cur_cell) best_cell = cur_cell;
			}
		}
	}
	int x, y;
	tie(ignore, ignore, x, y) = best_cell;
	rides[-x][-y] = num;
}

int GetScore(int x, int y) {
	int cnt = 0;
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = x + dx[dir], ny = y + dy[dir];
		if (InRange(nx, ny) && friends[rides[x][y]][rides[nx][ny]]) cnt++;
	}
	return (int)pow(10, cnt - 1);
}

int GetTotalScore() {
	int score = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			score += GetScore(i, j);
		}
	}
	return score;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n * n; i++) {
		cin >> target_num[i];

		for (int j = 1; j <= 4; j++) {
			int num;
			cin >> num;
			friends[target_num[i]][num] = true;
		}
	}

	for (int i = 1; i <= n * n; i++) Move(target_num[i]);

	cout << GetTotalScore() << "\n";
}