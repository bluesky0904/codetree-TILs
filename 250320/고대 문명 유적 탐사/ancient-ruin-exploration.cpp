/*
유적지 : 5 x 5
각 칸에는 다양한 유물 조각이 배치
유물 조각은 총 7가지 종류 : 1 ~ 7

[1] 탐사 진행
3 x 3 격자 선택, 회전
시계방향으로 90도, 180도, 270도 회전 가능
선택된 격자는 항상 회전을 진행해야함

회전 목표
가능한 회전 방법 중
(1) 유물 1차 획득 가치 최대화
(2) 회전 각도 최소
(3) 회전 중심 좌표 열 최소
(4) 회전 중심 좌표 행 최소

[2] 유물 획득
상하좌우로 인접한 같은 종류의 유물 조각은 서로 연결
이 조각들이 3개 이상 연결된 경우, 조각이 모여 유물이 되고 사라짐
유물의 가치는 모인 조각의 개수와 같음

유적의 벽면에는 1부터 7 사이의 숫자가 M개 적혀 있음
이들은 유적에서 조각이 사라졌을 때 새로 생겨나는 조각에 대한 정보를 담고 있음
조각이 사라진 위치에는 유적의 벽면에 적혀있는 순서대로 새로운 조각이 생겨남
새로운 조각은
(1) 열 번호가 작은 순으로 조각이 생겨남
(2) 행 번호가 큰 순으로 조각이 생겨남
단 벽면의 숫자는 충분히 많아서 생겨날 조각의 수가 부족한 경우는 없음
유적의 벽면에 써 있는 숫자를 사용한 이후에는 다시 사용할 수 없으므로 이후 부터는 남은 숫자부터 순서대로 사용

새로운 유물 조각이 생겨난 이후에도 조각들이 3개 이상 연결될 수 있음
이 경우 앞과 같은 방식으로 조각이 모여 유물이 되고 사라짐

[3] 탐사 반복
탐사 진행 ~ 유물 연쇄 획득 과정을 1턴으로 생각 총 K번의 턴에 걸쳐 진행
각 턴마다 획득한 유물의 가치의 총합 출력
아직 K번의 턴을 진행하지 못했지만, 탐사 진행 과정에서 어떠한 방법을 사용하더라도 유물을 획득할 수 없었다면 모든 탐사 종료
이 경우 얻을 수 있는 유물이 존재하지 않음으로, 종료되는 턴에 아무 값도 출력하지 않음에 유의
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int k, m;
int grid[6][6];
int next_grid[6][6];
int tmp[6][6];
bool visited[6][6];
deque<int> new_piece;

void print() {
	cout << "GRID" << "\n";
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "NEW PIECE" << "\n";
	for (int i = 0; i < new_piece.size(); i++) {
		cout << new_piece[i] << " ";
	}
	cout << "\n";
}

bool inRange(int x, int y) {
	return (0 <= x && x < 5 && 0 <= y && y < 5);
}

int nextBFS(int x, int y) {
	int cnt = 1;
	int type = next_grid[x][y];

	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = true;

	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();

		int dx[4] = { -1,0,1,0 };
		int dy[4] = { 0,1,0,-1 };
		for (int dir = 0; dir < 4; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (inRange(nx, ny) && !visited[nx][ny] && next_grid[nx][ny] == type) {
				visited[nx][ny] = true;
				q.push({ nx, ny });
				cnt++;
			}
		}
	}

	return cnt;
}

int rotateGrid(int x, int y, int degree) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			next_grid[i][j] = grid[i][j];
		}
	}

	while (degree--) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				tmp[i][j] = next_grid[i][j];
			}
		}

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int ox = x + i - (x - 1);
				int oy = y + j - (y - 1);
				int rx = oy;
				int ry = 3 - ox - 1; // 여기 5가 아니라 3임

				tmp[rx + (x - 1)][ry + (y - 1)] = next_grid[x + i][y + j]; // i, j 인덱싱 주의하고
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				next_grid[i][j] = tmp[i][j];
			}
		}
	}

	int value = 0;
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (!visited[i][j]) {
				int connected_cnt = nextBFS(i, j);
				if (connected_cnt >= 3) value += connected_cnt;
			}
		}
	}

	return value;
}

bool rotate() {
	int md, mx, my;
	int max_value = -1
		;
	for (int degree = 1; degree <= 3; degree++) {
		for (int col = 1; col <= 3; col++) {
			for (int row = 1; row <= 3; row++) {
				int value = rotateGrid(row, col, degree);
				if (max_value < value) {
					max_value = value;
					md = degree;
					mx = row;
					my = col;
				}
			}
		}
	}

	if (max_value == -1) return false;

	while (md--) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				tmp[i][j] = grid[i][j];
			}
		}

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int ox = mx + i - (mx - 1);
				int oy = my + j - (my - 1);
				int rx = oy;
				int ry = 3 - ox - 1; // 여기 5가 아니라 3임

				tmp[rx + (mx - 1)][ry + (my - 1)] = grid[mx + i][my + j]; // i, j 인덱싱 주의하고
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				grid[i][j] = tmp[i][j];
			}
		}
	}

	return true;
}

int BFS(int x, int y) {
	int cnt = 1;
	int type = grid[x][y];

	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = true;
	next_grid[x][y] = 0;

	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();

		int dx[4] = { -1,0,1,0 };
		int dy[4] = { 0,1,0,-1 };
		for (int dir = 0; dir < 4; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (inRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == type) {
				visited[nx][ny] = true;
				q.push({ nx, ny });
				next_grid[nx][ny] = 0;
				cnt++;
			}
		}
	}

	return cnt;
}

int getScore() {
	int ans = 0;
	while (1) {
		int value = 0;

		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (!visited[i][j]) {

					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++) {
							next_grid[i][j] = grid[i][j];
						}
					}

					int connected_cnt = BFS(i, j);
					if (connected_cnt >= 3) {
						value += connected_cnt;

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								grid[i][j] = next_grid[i][j];
							}
						}
					}
				}
			}
		}

		if (value == 0) break;
		ans += value;

		for (int col = 0; col < 5; col++) {
			for (int row = 4; row >= 0; row--) {
				if (grid[row][col] == 0) {
					grid[row][col] = new_piece.front();
					new_piece.pop_front();
				}
			}
		}
	}
	
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> k >> m;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int x; cin >> x;
		new_piece.push_back(x);
	}

	for (int turn = 1; turn <= k; turn++) {
		if (!rotate()) break;

		int x = getScore();
		if (x == 0) return 0;
		else cout << x << " ";
	}
}