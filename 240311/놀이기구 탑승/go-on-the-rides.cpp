#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n;

int grid[MAX_N + 1][MAX_N + 1];
int favorite_students[MAX_N * MAX_N + 1][5];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int num) {
	int mx = -1, my = -1;
	int max_favorite_students_cnt = -1;
	int max_empty_cnt = -1;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (grid[row][col] == 0) {
				int favorite_students_cnt = 0;
				int empty_cnt = 0;
				for (int dir = 0; dir < DIR_NUM; dir++) {
					int nx = row + dx[dir], ny = col + dy[dir];
					if (InRange(nx, ny)) {
						if (grid[nx][ny] == 0) empty_cnt++;
						else {
							for (int i = 1; i <= 4; i++) {
								if (grid[nx][ny] == favorite_students[num][i]) {
									favorite_students_cnt++;
									break;
								}
							}
						}
					}
				}
				if (max_favorite_students_cnt < favorite_students_cnt || (max_favorite_students_cnt == favorite_students_cnt && max_empty_cnt < empty_cnt)) {
					mx = row;
					my = col;
					max_favorite_students_cnt = favorite_students_cnt;
					max_empty_cnt = empty_cnt;
				}
			}
		}
	}
	if(mx != -1 && my != -1) grid[mx][my] = num;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n * n; i++) {
		int student_num;
		cin >> student_num;
		for (int j = 1; j <= 4; j++) {
			cin >> favorite_students[student_num][j];
		}

		Simulate(student_num);
	}

	int score = 0;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			int cnt = 0;
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = row + dx[dir], ny = col + dy[dir];
				if (InRange(nx, ny)) {
					for (int i = 1; i <= 4; i++) {
						if (grid[nx][ny] == favorite_students[grid[row][col]][i]) {
							cnt++;
							break;
						}
					}
				}
			}
			if (cnt == 0) continue;
			else if (cnt == 1) score += 1;
			else if (cnt == 2) score += 10;
			else if (cnt == 3) score += 100;
			else if (cnt == 4) score += 1000;
		}
	}

	cout << score << "\n";
	return 0;
}