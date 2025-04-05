/*
마을 : N x N, 0 based index, 도로 0, 도로가 아닌 곳 1
메두사 : 위치
메두사는 집 (Sr, Sc) -> 공원 (Er, Ec)
오직 도로만을 따라 최단 경로로 이동
메두사의 집과 공원은 항상 도로위에 있고 집과 공원의 좌표는 다름을 가정

용사 : M명, 위치, 돌 여부
같은 칸에 다른 용사들이 위치할 수 있음
메두사를 향해 최단 경로로 이동
전사들은 도로와 비도로를 구분하지 않고 어느 칸이든 이동할 수 있음
메두사의 집에 전사들이 초기부터 위치하는 경우는 없음

메두사는 전사들이 움직이기 전에 그들을 바라봄으로써 돌로 만들어 움직임을 멈출 수 있음

턴
1. 메두사의 이동
메두사는 도로를 따라 한 칸 이동하며 공원까지 최단 경로를 따름
메두사가 이동한 칸에 전사가 있을 경우 전사는 메두사에게 공격을 받고 사라짐
만약 집으로부터 공원까지 여러 최단경로가 가능하다면 상, 하, 좌, 우의 우선순위를 따름
메두사의 집으로부터 공원까지 도달하는 경로가 없을 수도 있음에 유의

2. 메두사의 시선
메두사는 상, 하, 좌, 우 하나의 방향을 선택해 바라봄
메두사는 바라보는 방향으로 90도의 시야각을 가지며, 시야각 범위 안에 있는 전사들을 볼 수 있음
메두사의 시야각 안에 들어와있지만 다른 전사에 가려진 전사의 경우 메두사에게 보이지 않음
특정 전사에 의해 메두사에게 가려지는 범위는 메두사와 해당 전사의 상대적인 위치에 의해 결정
상하좌우 대각선 8방향을 나누었을 때, 메두사로부터 8방향 중 한 방향에 전사가 위치해있다면, 그 전사가 동일한 방향으로 바라본 범위에 포함된 모든 칸은 메두사에게 보이지 않음

메두사가 본 전사들은 모두 돌로 변해 현재 턴에는 움직일 수 없으며, 이번 턴이 종료되었을 때 돌에서 풀려남
만약 두 명 이상의 전사들이 같은 칸에 위치해있다면 해당 칸의 전사들은 모두 돌로 변하게 됨

메두사는 상, 하, 좌, 우 중 전사를 가장 많이 볼 수 있는 방향을 바라봄
같은 수의 전사를 볼 수 있는 방향이 여러 개라면, 상하좌우의 우선순위로 방향을 결정

3. 전사들의 이동
돌로 변하지 않은 전사들은 메두사를 향해 최대 두 칸까지 이동
전사들은 이동 중 같은 칸을 공유할 수 있음
첫번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 이동. 이런 방향이 두 개 이상일 경우 "상하좌우"의 우선순위
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음
두번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 더 이동. 이런 방향이 두 개 이상일 경우 "좌우상하"의 우선순위
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음

4. 전사의 공격
메두사와 같은 칸에 도달한 전사는 메두사를 공격
그러나 메두사가 너무 강한 나머지 이기지 못하고 사라짐

위의 네 단계에서 최단경로를 계산할 때는 맨해튼 거리를 기준
위의 네 단계가 반복되어 메두사가 공원에 도달할 때까지 매 턴마다 해당 턴에 [모든 전사가 이동한 거리의 합] [메두사로 인해 돌이 된 전사의 수] [메두사를 공격한 전사의 수] 출력
단, 메두사가 공원에 도착하는 턴에는 0을 출력하고 프로그램 종료
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 50;
const int MAXM = 300;

int N, M; // 마을의 크기 N, 전사의 수 M
int sr, sc, er, ec; // 집 위치, 공원 위치

int medu_x, medu_y;
int medu_sight[MAXN + 10][MAXN + 10];
int tmp_sight[MAXN + 10][MAXN + 10];
int stunned[MAXN + 10][MAXN + 10];

int medu_dir[MAXN + 10][MAXN + 10];
bool visited[MAXN + 10][MAXN + 10];
int back_x[MAXN + 10][MAXN + 10];
int back_y[MAXN + 10][MAXN + 10];

int village[MAXN + 10][MAXN + 10];
int knight_pos[MAXN + 10][MAXN + 10];
int next_pos[MAXN + 10][MAXN + 10];

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

int knight_move_dist, stone_knight_cnt, medu_attack_cnt;

void print() {
	cout << "medu pos : " << medu_x << " " << medu_y << "\n";
	cout << "knight pos" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << knight_pos[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "medu sight" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << medu_sight[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

bool inRange(int x, int y) {
	return (x >= 0 && x < N && y >= 0 && y < N);
}

bool isPossible() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
			back_x[i][j] = -1;
			back_y[i][j] = -1;
			medu_dir[i][j] = -1;
		}
	}
	queue<pair<int, int>> q;

	q.push({ sr, sc }); // 도착점에서 bfs를 시작
	visited[sr][sc] = true;

	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		
		if (cx == er && cy == ec) {

			while (1) {
				int bx = back_x[cx][cy];
				int by = back_y[cx][cy];

				for (int dir = 0; dir < 4; dir++) {
					if (bx + dx[dir] == cx && by + dy[dir] == cy) {
						medu_dir[bx][by] = dir;
						break;
					}
				}

				cx = bx;
				cy = by;

				if (cx == sr && cy == sc) return true;
			}
		}
		

		for (int dir = 0; dir < 4; dir++) { // 목적지에서 출발하니까 우선순위 반대로 적용했어야 했음 시발
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];

			if (inRange(nx, ny) && !visited[nx][ny] && village[nx][ny] == 0) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
				back_x[nx][ny] = cx;
				back_y[nx][ny] = cy;
			}
		}
	}

	return false;
}

void moveMedu() {
	int dir = medu_dir[medu_x][medu_y];
	medu_x += dx[dir];
	medu_y += dy[dir];

	if (knight_pos[medu_x][medu_y] != 0) knight_pos[medu_x][medu_y] = 0;
}

/*
2. 메두사의 시선
메두사는 상, 하, 좌, 우 하나의 방향을 선택해 바라봄
메두사는 바라보는 방향으로 90도의 시야각을 가지며, 시야각 범위 안에 있는 전사들을 볼 수 있음
메두사의 시야각 안에 들어와있지만 다른 전사에 가려진 전사의 경우 메두사에게 보이지 않음
특정 전사에 의해 메두사에게 가려지는 범위는 메두사와 해당 전사의 상대적인 위치에 의해 결정
상하좌우 대각선 8방향을 나누었을 때, 메두사로부터 8방향 중 한 방향에 전사가 위치해있다면, 그 전사가 동일한 방향으로 바라본 범위에 포함된 모든 칸은 메두사에게 보이지 않음

메두사가 본 전사들은 모두 돌로 변해 현재 턴에는 움직일 수 없으며, 이번 턴이 종료되었을 때 돌에서 풀려남
만약 두 명 이상의 전사들이 같은 칸에 위치해있다면 해당 칸의 전사들은 모두 돌로 변하게 됨

메두사는 상, 하, 좌, 우 중 전사를 가장 많이 볼 수 있는 방향을 바라봄
같은 수의 전사를 볼 수 있는 방향이 여러 개라면, 상하좌우의 우선순위로 방향을 결정
*/

int meduUp(int real) {
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmp_sight[i][j] = 0;
		}
	}

	for (int row = 1; row <= N; row++) {
		for (int col = 0; col < 2 * row + 1; col++) {
			int cx = medu_x - row;
			int cy = medu_y - row + col;
			if (inRange(cx, cy)) tmp_sight[cx][cy] = 1;
		}
	}

	for (int row = 1; row <= N; row++) {
		for (int col = 0; col < 2 * row + 1; col++) {
			int cx = medu_x - row;
			int cy = medu_y - row + col;

			if (inRange(cx, cy) && knight_pos[cx][cy] != 0 && tmp_sight[cx][cy] == 1) {
				if (cy < medu_y) {
					for (int rrow = 1; rrow <= N; rrow++) {
						for (int ccol = 0; ccol < rrow + 1; ccol++) {
							int ccx = cx - rrow;
							int ccy = cy - rrow + ccol;
							if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;

						}
					}
				}
				else if (cy > medu_y) {
					for (int rrow = 1; rrow <= N; rrow++) {
						for (int ccol = 0; ccol < rrow + 1; ccol++) {
							int ccx = cx - rrow;
							int ccy = cy + ccol;
							if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;
						}
					}
				}
				else {
					for (int rrow = 1; rrow <= N; rrow++) {
						int ccx = cx - rrow;
						int ccy = cy;
						if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;
					}
				}
			}
		}
	}

	/*
	cout << "up tmp" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << tmp_sight[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	*/

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (knight_pos[i][j] != 0 && tmp_sight[i][j] == 1) cnt += knight_pos[i][j];
		}
	}

	if (real) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				medu_sight[i][j] = tmp_sight[i][j];
			}
		}
	}

	return cnt;
}

int meduDown(int real) {
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmp_sight[i][j] = 0;
		}
	}

	for (int row = 1; row <= N; row++) {
		for (int col = 0; col < 2 * row + 1; col++) {
			int cx = medu_x + row;
			int cy = medu_y - row + col;
			if (inRange(cx, cy)) tmp_sight[cx][cy] = 1;
		}
	}
	
	for (int row = 1; row <= N; row++) {
		for (int col = 0; col < 2 * row + 1; col++) {
			int cx = medu_x + row;
			int cy = medu_y - row + col;

			if (inRange(cx, cy) && knight_pos[cx][cy] != 0 && tmp_sight[cx][cy] == 1) {
				if (cy < medu_y) {
					for (int rrow = 1; rrow <= N; rrow++) {
						for (int ccol = 0; ccol < rrow + 1; ccol++) {
							int ccx = cx + rrow;
							int ccy = cy - rrow + ccol;
							if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;

						}
					}
				}
				else if (cy > medu_y) {
					for (int rrow = 1; rrow <= N; rrow++) {
						for (int ccol = 0; ccol < rrow + 1; ccol++) {
							int ccx = cx + rrow;
							int ccy = cy + ccol;
							if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;
						}
					}
				}
				else {
					for (int rrow = 1; rrow <= N; rrow++) {
						int ccx = cx + rrow;
						int ccy = cy;
						if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;
					}
				}
			}
		}
	}

	/*
	cout << "down tmp" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << tmp_sight[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	*/

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (knight_pos[i][j] != 0 && tmp_sight[i][j] == 1) cnt += knight_pos[i][j];
		}
	}

	if (real) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				medu_sight[i][j] = tmp_sight[i][j];
			}
		}
	}

	return cnt;
}

int meduLeft(int real) {
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmp_sight[i][j] = 0;
		}
	}

	for (int col = 1; col <= N; col++) {
		for (int row = 0; row < 2 * col + 1; row++) {
			int cx = medu_x - col + row;
			int cy = medu_y - col;
			if (inRange(cx, cy)) tmp_sight[cx][cy] = 1;
		}
	}

	for (int col = 1; col <= N; col++) {
		for (int row = 0; row < 2 * col + 1; row++) {
			int cx = medu_x - col + row;
			int cy = medu_y - col;

			if (inRange(cx, cy) && knight_pos[cx][cy] != 0 && tmp_sight[cx][cy] == 1) {
				if (cx < medu_x) {
					for (int ccol = 1; ccol <= N; ccol++) {
						for (int rrow = 0; rrow < ccol + 1; rrow++) {
							int ccx = cx - ccol + rrow;
							int ccy = cy - ccol;
							if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;

						}
					}
				}
				else if (cx > medu_x) {
					for (int ccol = 1; ccol <= N; ccol++) {
						for (int rrow = 0; rrow < ccol + 1; rrow++) {
							int ccx = cx + rrow;
							int ccy = cy - ccol;
							if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;
						}
					}
				}
				else {
					for (int ccol = 1; ccol <= N; ccol++) {
						int ccx = cx;
						int ccy = cy - ccol;
						if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;
					}
				}
			}
		}
	}

	/*
	cout << "left tmp" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << tmp_sight[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	*/

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (knight_pos[i][j] != 0 && tmp_sight[i][j] == 1) cnt += knight_pos[i][j];
		}
	}

	if (real) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				medu_sight[i][j] = tmp_sight[i][j];
			}
		}
	}

	return cnt;
}

int meduRight(int real) {
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmp_sight[i][j] = 0;
		}
	}

	for (int col = 1; col <= N; col++) {
		for (int row = 0; row < 2 * col + 1; row++) {
			int cx = medu_x - col + row;
			int cy = medu_y + col;
			if (inRange(cx, cy)) tmp_sight[cx][cy] = 1;
		}
	}

	for (int col = 1; col <= N; col++) {
		for (int row = 0; row < 2 * col + 1; row++) {
			int cx = medu_x - col + row;
			int cy = medu_y + col;

			if (inRange(cx, cy) && knight_pos[cx][cy] != 0 && tmp_sight[cx][cy] == 1) {
				if (cx < medu_x) {
					for (int ccol = 1; ccol <= N; ccol++) {
						for (int rrow = 0; rrow < ccol + 1; rrow++) {
							int ccx = cx - ccol + rrow;
							int ccy = cy + ccol;
							if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;

						}
					}
				}
				else if (cx > medu_x) {
					for (int ccol = 1; ccol <= N; ccol++) {
						for (int rrow = 0; rrow < ccol + 1; rrow++) {
							int ccx = cx + rrow;
							int ccy = cy + ccol;
							if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;
						}
					}
				}
				else {
					for (int ccol = 1; ccol <= N; ccol++) {
						int ccx = cx;
						int ccy = cy + ccol;
						if (inRange(ccx, ccy)) tmp_sight[ccx][ccy] = 0;
					}
				}
			}
		}
	}

	/*
	cout << "right tmp" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << tmp_sight[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	*/

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (knight_pos[i][j] != 0 && tmp_sight[i][j] == 1) cnt += knight_pos[i][j];
		}
	}

	if (real) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				medu_sight[i][j] = tmp_sight[i][j];
			}
		}
	}

	return cnt;
}

void meduSight() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			stunned[i][j] = 0;
			medu_sight[i][j] = 0;
		}
	}
	int max_cnt = 0;
	int max_dir = 0;

	int up_cnt = meduUp(0);
	if (max_cnt < up_cnt) {
		max_cnt = up_cnt;
		max_dir = 0;
	}

	int down_cnt = meduDown(0);
	if (max_cnt < down_cnt) {
		max_cnt = down_cnt;
		max_dir = 1;
	}

	int left_cnt = meduLeft(0);
	if (max_cnt < left_cnt) {
		max_cnt = left_cnt;
		max_dir = 2;
	}

	int right_cnt = meduRight(0);
	if (max_cnt < right_cnt) {
		max_cnt = right_cnt;
		max_dir = 3;
	}

	if (max_dir == 0) meduUp(1);
	else if (max_dir == 1) meduDown(1);
	else if (max_dir == 2) meduLeft(1);
	else if (max_dir == 3) meduRight(1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (medu_sight[i][j] == 1 && knight_pos[i][j] != 0) {
				stunned[i][j] = 1;
				stone_knight_cnt += knight_pos[i][j];
			}
		}
	}
}

/*
3. 전사들의 이동
돌로 변하지 않은 전사들은 메두사를 향해 최대 두 칸까지 이동
전사들은 이동 중 같은 칸을 공유할 수 있음
첫번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 이동. 이런 방향이 두 개 이상일 경우 "상하좌우"의 우선순위
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음
두번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 더 이동. 이런 방향이 두 개 이상일 경우 "좌우상하"의 우선순위
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음

4. 전사의 공격
메두사와 같은 칸에 도달한 전사는 메두사를 공격
그러나 메두사가 너무 강한 나머지 이기지 못하고 사라짐

위의 네 단계에서 최단경로를 계산할 때는 맨해튼 거리를 기준
위의 네 단계가 반복되어 메두사가 공원에 도달할 때까지 매 턴마다 해당 턴에 [모든 전사가 이동한 거리의 합] [메두사로 인해 돌이 된 전사의 수] [메두사를 공격한 전사의 수] 출력
단, 메두사가 공원에 도착하는 턴에는 0을 출력하고 프로그램 종료
*/

int getDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void moveKnight() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			next_pos[i][j] = 0;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (knight_pos[i][j] == 0) continue;
			if (stunned[i][j] == 1) {
				next_pos[i][j] += knight_pos[i][j];
				continue;
			}

			int cx = i;
			int cy = j;
			int nx = cx;
			int ny = cy;

			int cur_dist = getDist(cx, cy, medu_x, medu_y);
			int md = -1;
			for (int dir = 0; dir < 4; dir++) {
				nx = cx + dx[dir];
				ny = cy + dy[dir];

				if (inRange(nx, ny) && medu_sight[nx][ny] == 0 && getDist(nx, ny, medu_x, medu_y) < cur_dist) {
					md = dir;
					break;
				}
			}

			if (md != -1) {
				cx += dx[md];
				cy += dy[md];
				
				knight_move_dist += knight_pos[i][j];
				if (cx == medu_x && cy == medu_y) {
					medu_attack_cnt += knight_pos[i][j];
					continue;;
				}
			}

			cur_dist = getDist(cx, cy, medu_x, medu_y); 
			md = -1;
			nx = cx + dx[1];
			ny = cy + dy[1];
			if (inRange(nx, ny) && medu_sight[nx][ny] == 0 && getDist(nx, ny, medu_x, medu_y) < cur_dist) {
				md = 1;
			}
			nx = cx + dx[0];
			ny = cy + dy[0];
			if (inRange(nx, ny) && medu_sight[nx][ny] == 0 && getDist(nx, ny, medu_x, medu_y) < cur_dist) {
				md = 0;
			}
			nx = cx + dx[3];
			ny = cy + dy[3];
			if (inRange(nx, ny) && medu_sight[nx][ny] == 0 && getDist(nx, ny, medu_x, medu_y) < cur_dist) {
				md = 3;
			}
			nx = cx + dx[2];
			ny = cy + dy[2];
			if (inRange(nx, ny) && medu_sight[nx][ny] == 0 && getDist(nx, ny, medu_x, medu_y) < cur_dist) {
				md = 2;
			}

			if (md != -1) {
				cx += dx[md];
				cy += dy[md];
				knight_move_dist += knight_pos[i][j];
				if (cx == medu_x && cy == medu_y) {
					medu_attack_cnt += knight_pos[i][j];
					continue;;
				}
			}

			next_pos[cx][cy] += knight_pos[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			knight_pos[i][j] = next_pos[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> N >> M;
	cin >> sr >> sc >> er >> ec;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			knight_pos[i][j] = 0;
		}
	}
	for (int i = 1; i <= M; i++) {
		int r, c; cin >> r >> c;
		knight_pos[r][c]++;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> village[i][j];
		}
	}

	medu_x = sr;
	medu_y = sc;

	if (!isPossible()) { // 메두사가 집->공원 이동 가능한지
		cout << -1 << "\n";
		return 0;
	}

	for (int turn = 1;; turn++) { // break, return 없이 이렇게만 작성하면 무한루프 빠질 수 밖에 없음
		//cout << "turn : " << turn << "\n";
		
		knight_move_dist = 0;
		stone_knight_cnt = 0;
		medu_attack_cnt = 0;
		
		//cout << "moveMedu" << "\n";
		moveMedu();
		//print();

		if (medu_x == er && medu_y == ec) {
			cout << 0 << "\n";
			return 0;
		}

		//cout << "meduSight" << "\n";
		meduSight();
		//print();

		//cout << "moveKnight" << "\n";
		moveKnight();
		//print();

		cout << knight_move_dist << " " << stone_knight_cnt << " " << medu_attack_cnt << "\n";
	}
}