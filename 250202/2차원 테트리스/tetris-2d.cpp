#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#define MAX_N 6
#define MAX_M 4
#define PIECE_NUM 3

int shape[PIECE_NUM + 1][2][2] = {
	{},

	{{1, 0},
	{0, 0}},

	{{1, 1},
	{0, 0}},

	{{1, 0},
	{1, 0}},
};

int k;
int n = 6, m = 4;
int score;
int board[2][MAX_N][MAX_M];

bool inRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

bool canGo(int b_num, int t_num, int x, int y) {
	for (int dx = 0; dx < 2; dx++) {
		for (int dy = 0; dy < 2; dy++) {
			if (shape[t_num][dx][dy] == 1) {
				int nx = x + dx, ny = y + dy;
				if (!inRange(nx, ny) || board[b_num][nx][ny] == 1) return false;
			}
		}
	}
	return true;
}

void setBlock(int b_num, int t_num, int x, int y){
	for (int dx = 0; dx < 2; dx++) {
		for (int dy = 0; dy < 2; dy++) {
			if (shape[t_num][dx][dy] == 1) {
				int nx = x + dx, ny = y + dy;
				board[b_num][nx][ny] = 1;
			}
		}
	}
}

bool isFilled(int b_num, int row) {
	for (int col = 0; col < m; col++) {
		if (board[b_num][row][col] == 0) return false;
	}
	return true;
}

void downOneLine(int b_num, int target_row) { // 무조건 마지막 줄을 내리는 것이 아니라 target_row를 내렸어야 함
	for (int col = 0; col < m; col++) {
		board[b_num][target_row][col] = 0;
	}

	for (int row = target_row; row >= 1; row--) {
		for (int col = 0; col < m; col++) {
			board[b_num][row][col] = board[b_num][row - 1][col];
			board[b_num][row - 1][col] = 0;
		}
	}
}

void processDark(int b_num) {
	int row = n - 1;

	while (row >= 2) {
		if (isFilled(b_num, row)) {
			downOneLine(b_num, row);
			score++;
		}
		else row--;
	}
}

bool isAnyBlock(int b_num, int row) {
	for (int col = 0; col < m; col++) {
		if (board[b_num][row][col] == 1) return true;
	}
	return false;
}

void processLight(int b_num) {
	int down_cnt = 0;
	
	if (isAnyBlock(b_num, 0)) down_cnt++;
	if (isAnyBlock(b_num, 1)) down_cnt++;

	while (down_cnt--) {
		downOneLine(b_num, n -1);
	}
}

void drop(int b_num, int t_num, int col) {
	for (int row = 1; row <= n; row++) {
		if (!canGo(b_num, t_num, row, col)) {
			setBlock(b_num, t_num, row - 1, col);
			break; // 블럭을 배치했으면 break 해주어야죠?
		}
	}

	processDark(b_num);
	processLight(b_num);
}

int countRemain() {
	int cnt = 0;

	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_M; j++) {
			if (board[0][i][j] == 1) cnt++;
			if (board[1][i][j] == 1) cnt++;
		}
	}

	return cnt;
}

void print() {
	cout << "YELLOW BOARD" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			cout << board[0][x][y] << " ";
		}
		cout << "\n";
	}

	cout << "RED BOARD" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			cout << board[1][x][y] << " ";
		}
		cout << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> k;

	score = 0;
	for (int turn = 1; turn <= k; turn++) {
		//cout << "TURN " << turn << "\n";
		int t, x, y; cin >> t >> x >> y;

		drop(0, t, y); // 노란색 grid

		if (t == 1) drop(1, 1, m - x - 1);
		else if (t == 2) drop(1, 3, m - x - 1);
		else drop(1, 2, m - (x + 1) - 1);

		//print();
	}

	cout << score << "\n";
	cout << countRemain() << "\n";
	return 0;
}