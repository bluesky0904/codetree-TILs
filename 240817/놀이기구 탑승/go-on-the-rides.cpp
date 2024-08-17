//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <tuple>
#include <cmath>
using namespace std;

// 친구의 수, 빈칸의 수, 행, 열
typedef tuple<int, int, int, int> Cell;

#define MAX_N 20
#define DIR_NUM 4

int n;
int targets[MAX_N * MAX_N + 1];
int rides[MAX_N + 1][MAX_N + 1];
bool friends[MAX_N + 1][MAX_N + 1];

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

Cell GetCurCell(int num, int x, int y) {
	int friend_cnt = 0, empty_cnt = 0;
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = x + dx[dir], ny = y + dy[dir];
		if (InRange(nx, ny)) {
			if (rides[nx][ny] == 0) empty_cnt++;
			else if(friends[num][rides[nx][ny]]) friend_cnt++;
		}
	}
	return make_tuple(friend_cnt, empty_cnt, -x, -y);
}

void Move(int num) {
	Cell best_cell = make_tuple(0, 0, -(n + 1), -(n + 1));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (rides[i][j] == 0) {
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

	if (cnt == 0) return 0;
	else return (int)pow(10, cnt - 1);
}

int GetTotalScore() {
	int score = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			score += GetScore(i, j);
		}
	}
	return score;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n;
	for (int i = 0; i < n * n; i++) {
		cin >> targets[i];

		for (int j = 1; j <= 4; j++) {
			int num;
			cin >> num;
			friends[targets[i]][num] = true;
		}
	}

	for (int i = 0; i < n * n; i++) Move(targets[i]);

	cout << GetTotalScore() << "\n";

	return 0;
}