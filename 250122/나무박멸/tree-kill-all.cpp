/* 
n * n 격자 : 나무, 벽, 0-based
제초제 위치 및 유효기간


제초제를 뿌려 나무의 성장을 억제
제초제의 경우 k의 범위만큼 대각선으로 퍼지며, 벽이 있는 경우 가로막혀 전파되지 않음

1. 인접한 네 개의 칸 중 나무가 있는 칸의 수만큼 나무가 성장
성장은 모든 나무에게 동시에 일어남

2. 기존에 있었던 나무들은 인접한 4개의 칸 중 벽, 다른 나무, 제초제 모두 없는 칸에 번식을 진행
이때 각 칸의 나무 그루 수에서 총 번식이 가능한 칸의 개수만큼 나누어진 그루 수만큼 번식
나눌 때 생기는 나머지는 버림
번식의 과정은 모든 나무에서 동시에 일어남

격자
-1 -> 살충제o 살충제x
0 ->  살충제o 살충제x
양수 -> 살충제x 

3. 각 칸 중 제초제를 뿌렸을 때 나무가 가장 많이 박멸되는 칸에 제초제를 뿌림
나무가 없는 칸에 제초제를 뿌리면 박멸되는 나무가 전혀 없는 상태로 끝이 나지만,
나무가 있는 칸에 제초제를 뿌리게 되면 4개의 대각선 방향으로 k칸만큼 전파
단 전파되는 도중 벽이 있거나 나무가 아얘 없는 칸이 있는 경우, 그 칸까지는 제초제가 뿌려지며
이후의 칸으로는 제초제가 전파되지 않음
제초제가 뿌려진 칸에는 c년만큼 제초제가 남아있다가 c+1년째가 될 때 사라지게 됨
제초제가 뿌려진 곳에 다시 제초제가 뿌려지는 경우에는 새로 뿌려진 해로부터 다시 c년 동안 제초제가 유지

제초제를 뿌릴 우선순위
박멸시키는 나무의 수 > 행 최소 > 열 최소

각 3개의 과정이 1년에 걸쳐 진행된다고 했을 때, m년 동안 총 박멸한 나무의 그루 수를 구하기
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n, m, k, c;
int removed_cnt; // 총 제거된 나무수
int grid[MAX_N][MAX_N]; // 나무, 벽
int next_grid[MAX_N][MAX_N]; // 나무, 벽 동시 처리를 위한 배열
int plant_killer[MAX_N][MAX_N]; // 제초제

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

int dx_d[DIR_NUM] = {-1, 1, 1, -1};
int dy_d[DIR_NUM] = {1, 1, -1, -1};

bool inRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

void grow() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0) continue;
			if (grid[i][j] == -1) {
				next_grid[i][j] = -1;
				continue;
			}

			int cx = i, cy = j;
			int cnt = 0;
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = cx + dx[dir], ny = cy + dy[dir];
				if (inRange(nx, ny) && grid[nx][ny] > 0) cnt++;
			}
			if (cnt > 0) next_grid[cx][cy] = grid[cx][cy] + cnt;
			else next_grid[cx][cy] = grid[cx][cy];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

void reproduce(int time) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0) continue;
			if (grid[i][j] == -1) {
				next_grid[i][j] = -1;
				continue;
			}

			int cx = i, cy = j;
			int cnt = 0;
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = cx + dx[dir], ny = cy + dy[dir];
				if (inRange(nx, ny) && grid[nx][ny] == 0 && plant_killer[nx][ny] <= time) cnt++;
			}

			if (cnt > 0) {
				int reproduce_amount = grid[cx][cy] / cnt;

				for (int dir = 0; dir < DIR_NUM; dir++) {
					int nx = cx + dx[dir], ny = cy + dy[dir];
					if (inRange(nx, ny) && grid[nx][ny] == 0 && plant_killer[nx][ny] <= time) {
						next_grid[nx][ny] += reproduce_amount;
					}
				}
			}

			next_grid[cx][cy] = grid[cx][cy];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

void print() {
	cout << "GRID" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}

int getTreeCnt(int x, int y) {
	int cnt = grid[x][y];
	for (int dir = 0; dir < DIR_NUM; dir++) {
		for (int dist = 1; dist <= k; dist++) {
			int nx = x + dx_d[dir] * dist, ny = y + dy_d[dir] * dist;
			if (inRange(nx, ny) && grid[nx][ny] > 0) {
				cnt += grid[nx][ny];
			}
			else break;
		}
	}
	return cnt;
}

void doKill(int x, int y, int time) {
	grid[x][y] = 0;
	plant_killer[x][y] = time + 2;

	for (int dir = 0; dir < DIR_NUM; dir++) {
		for (int dist = 1; dist <= k; dist++) {
			int nx = x + dx_d[dir] * dist, ny = y + dy_d[dir] * dist;
			if (inRange(nx, ny) && grid[nx][ny] > 0) {
				grid[nx][ny] = 0;
				plant_killer[nx][ny] = time + 2;
			}
			else {
				if (inRange(nx, ny)) {
					grid[nx][ny] = 0;
					plant_killer[nx][ny] = time + 2;
					break;
				}
			}
		}
	}
}

void kill(int time) {
	int max_cnt = -1, max_x = 0, max_y = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0 || grid[i][j] == -1) continue;
			int tree_cnt = getTreeCnt(i, j);
			if (max_cnt < tree_cnt) {
				max_cnt = tree_cnt;
				max_x = i, max_y = j;
			}
		}
	}

	// 제초제를 실제로 뿌리는 작업
	doKill(max_x, max_y, time);
	removed_cnt += max_cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m >> k >> c;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	//print();
	removed_cnt = 0;
	for (int t = 1; t <= m; t++) {
		grow();
		//cout << t << " " << "GROW RESULT" << "\n";
		//print();

		reproduce(t);
		//cout << t << " " << "REPRODUCE RESULT" << "\n";
		//print();

		kill(t);
		//cout << t << " " << "KILL RESULT" << "\n";
		//print();
	}

	cout << removed_cnt << "\n";
	return 0;
}