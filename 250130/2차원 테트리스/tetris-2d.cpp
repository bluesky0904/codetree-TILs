/*
격자 0-based

타일들
 
점수

행이나 열이 타일로 가득 찬 경우가 없을 때까지 점수를 획득하는 과정이 모두 진행된 후, 연한 칸에 블록이 있는 경우를 처리
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#define MAX_N 6
#define MAX_M 4
#define TILE_TYPE 3

int n = 6, m = 4;
int k;
int score;
int board[2][MAX_N][MAX_M];
int shapes[TILE_TYPE + 1][2][2] = {
	{},

	{{1,0},
	{0,0}},

	{{1,1},
	{0,0}},

	{{1,0},
	{1,0}},
};

bool inRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

bool canGo(int b_num, int t_num, int x, int y) {
	for (int dx = 0; dx < 2; dx++) {
		for (int dy = 0; dy < 2; dy++) {
			if (shapes[t_num][dx][dy]) {
				int nx = x + dx, ny = y + dy;
				if (!inRange(nx, ny) || board[b_num][nx][ny] == 1) return false;
			}
		}
	}
	return true;
}

void put(int b_num, int t_num, int x, int y) {
	for (int dx = 0; dx < 2; dx++) {
		for (int dy = 0; dy < 2; dy++) {
			if (shapes[t_num][dx][dy]) {
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

void downOneLine(int b_num, int line) {
	for (int col = 0; col < m; col++) {
		board[b_num][line][col] = 0;
	}

	for (int row = line; row >= 1; row--) { // row >= 1 유의
		for (int col = 0; col < m; col++) {
			board[b_num][row][col] = board[b_num][row - 1][col];
			board[b_num][row - 1][col] = 0;
		}
	}
}

void processDark(int b_num) {
	int row = n - 1;

	while(row >= 2){
		if (isFilled(b_num, row)) {
			downOneLine(b_num, row);
			score++;
		}
		else row--;
	}
}

bool blockExist(int b_num, int row) {
	for (int col = 0; col < m; col++) {
		if (board[b_num][row][col] == 1) return true;
	}
	return false;
}

void processLight(int b_num) {
	int delete_cnt = 0;

	if (blockExist(b_num, 0)) delete_cnt++;
	if (blockExist(b_num, 1)) delete_cnt++;

	while (delete_cnt--) {
		downOneLine(b_num, n - 1);
	}
}

void print() {
	cout << "YELLOW GRID" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			cout << board[0][x][y] << " ";
		}
		cout << "\n";
	}
	cout << "RED GRID" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			cout << board[1][x][y] << " ";
		}
		cout << "\n";
	}
}

void drop(int b_num, int t_num, int col) {
	for (int row = 0; row < n; row++) {
		if (!canGo(b_num, t_num, row + 1, col)) { // row 아님
			put(b_num, t_num, row, col); // row - 1 아님
			break;
		}
	}
	//print();

	processDark(b_num);
	//print();

	processLight(b_num);
	//print();
}

int remainCnt() {
	int cnt = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[0][i][j] == 1) cnt++;
			if (board[1][i][j] == 1) cnt++;
		}
	}
	return cnt;
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> k;
	score = 0;

	for (int i = 1; i <= k; i++) {
		//cout << "TURN :" << i << "\n";

		int t, x, y; cin >> t >> x >> y;

		drop(0, t, y);

		if (t == 1) drop(1, 1, m - x - 1); // t 아님
		else if (t == 2) drop(1, 3, m - x - 1); // t 아님
		else if (t == 3) drop(1, 2, m - (x + 1) - 1); // t 아님 회전시키면서 블록 종류도 바뀜
	}

	cout << score << "\n";
	cout << remainCnt() << "\n";
	return 0;
}

/*
직사각형에서의 회전 및 격자 변환
n = 6, m = 4
0 0 0 0 0 (1, 3) (x, y)
0 0 0 1 0
0 0 0 1 0
0 0 0 0 0

0 0 0 0 (3, 1) (y, m - (x + 1) - 1)
0 0 0 0
0 0 0 0
0 1 1 0
0 0 0 0
*/