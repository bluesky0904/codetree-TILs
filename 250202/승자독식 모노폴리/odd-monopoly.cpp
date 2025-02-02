#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tuple>
using namespace std;

#define MAX_N 20
#define MAX_M 400
#define DIR_NUM 4
#define EMPTY make_pair(401, 401)
#define EMPTY_NUM 401

int n, m, k;
int grid[MAX_N + 1][MAX_N + 1];
pair<int, int> pos[MAX_M + 1];
pair<int, int> player[MAX_N + 1][MAX_N + 1];
pair<int, int> next_player[MAX_N + 1][MAX_N + 1];
pair<int, int> contract[MAX_N + 1][MAX_N + 1];
int dir_priority[MAX_M + 1][DIR_NUM][DIR_NUM];

int dx[DIR_NUM] = { -1,1,0,0 };
int dy[DIR_NUM] = { 0,0,-1,1 };

bool isOver() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (player[i][j] == EMPTY) continue;

			int num;
			tie(num, ignore) = player[i][j];
			if (num != 1) return false;
		}
	}
	return true;
}

bool inRange(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

void movePlayer(int idx, int x, int y) {
	int cx = x, cy = y, cd = player[cx][cy].second;

	for (int cnt = 0; cnt < DIR_NUM; cnt++) {
		int pd = dir_priority[idx][cd][cnt];
		int nx = cx + dx[pd], ny = cy + dy[pd];
		if (inRange(nx, ny) && contract[nx][ny] == EMPTY) { // 여기 왜 or로 처리한거지??
			if (next_player[nx][ny] == EMPTY) {
				next_player[nx][ny] = { idx, pd };
				return;
			}
			else {
				if (idx < next_player[nx][ny].first) {
					next_player[nx][ny] = { idx, pd };
					return;
				}
				else {
					return;
				}
			}
		}
	}

	for (int cnt = 0; cnt < DIR_NUM; cnt++) {
		int pd = dir_priority[idx][cd][cnt];
		int nx = cx + dx[pd], ny = cy + dy[pd];
		if (inRange(nx, ny) && contract[nx][ny].first == idx) { // 왜 or로 처리하셨어요?
			if (next_player[nx][ny] == EMPTY) {
				next_player[nx][ny] = { idx, pd };
				return;
			}
			else {
				if (idx < next_player[nx][ny].first) {
					next_player[nx][ny] = { idx, pd };
					return;
				}
				else {
					return;
				}
			}
		}
	}
}

void moveAllPlayer() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			next_player[i][j] = EMPTY;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int num;
			tie(num, ignore) = player[i][j];
			if (num == EMPTY_NUM) continue;
			
			movePlayer(num, i, j);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			player[i][j] = next_player[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (next_player[i][j] == EMPTY) continue;
			contract[i][j] = {next_player[i][j].first, k + 1};
		}
	}
}

void reduceTurn() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (contract[i][j] == EMPTY) continue;
			int idx, remain_turn;
			tie(idx, remain_turn) = contract[i][j];

			//cout << "여기 왜 안돌아가냐?\n";

			if (remain_turn > 1) {
				
				contract[i][j] = { idx, remain_turn - 1 };
			}
			else if (remain_turn == 1) {
				contract[i][j] = EMPTY;
			}
		}
	}
}

void print() {
	cout << "PLAYER" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if(player[i][j] == EMPTY) cout << "{ } ";
			else cout << "{" << player[i][j].first << " " << player[i][j].second << "} ";
 		}
		cout << "\n";
	}
	cout << "CONTRACT" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (contract[i][j] == EMPTY) cout << "{ } ";
			else cout << "{" << contract[i][j].first << " " << contract[i][j].second << "} ";
		}
		cout << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			player[i][j] = EMPTY;
			contract[i][j] = EMPTY;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] > 0) {
				pos[grid[i][j]] = { i, j };
				contract[i][j] = { grid[i][j], k };
			}
		}
	}

	for (int i = 1; i <= m; i++) {
		int dir; cin >> dir; dir--;
		int x, y;
		tie(x, y) = pos[i];
		player[x][y] = { i, dir };
	}

	for (int i = 1; i <= m; i++) {
		for (int cur_d = 0; cur_d < DIR_NUM; cur_d++) {
			for (int cnt = 0; cnt < DIR_NUM; cnt++) {
				int dir; cin >> dir; dir--;
				dir_priority[i][cur_d][cnt] = dir;
			}
		}
	}

	int turn = 0;
	while (1) {
		turn++;
		if (turn >= 1000) {
			cout << -1 << "\n";
			return 0;
		}

		moveAllPlayer();
		
		reduceTurn();

		if (isOver()) {
			cout << turn << "\n";
			return 0;
		}
	}
}