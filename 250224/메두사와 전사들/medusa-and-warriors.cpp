/*
메두사 : 도로만을 따라 최단 경로로 공원까지 이동, 시야각
마을 : 0 ~ N -1, N x N, 도로는 0, 도로가 아닌 곳은 1
	   집 (Sr, Sc) -> 공원 (Er, Ec)
기사 : M명, 위치, 돌 여부, 메두사를 향해 최단 경로로 이동. 도로와 비도로를 구분하지 않고 이동

메두사와 전사들의 이동은 매턴마다 다음 순서에 맞춰 차례로 진행
1. 메두사의 이동
메두사는 도로를 따라 한 칸 이동, 공원까지 최단 경로
메두사가 이동한 칸에 전사가 있을 경우 메두사에게 공격을 받고 사라짐
만약 집으로부터 공원까지 여러 최단경로가 가능하다면 상하좌우의 우선순위
메두사의 집으로부터 공원까지 도달하는 경로가 없을 수도 없음

2. 메두사의 시선
메두사는 상하좌우 하나의 방향을 선택해 바라봄
메두사는 바라보는 방향으로 90도의 시야각을 가지며
시야각 범위 안에 있는 전사들을 볼 수 있음
메두사의 시야각 안에 들어와있지만 다른 전사에 가려진 전사의 경우 메두사에게 보이지 않음
메두사가 본 전사들은 모두 돌로 변해 현재 턴에는 움직일 수 없으며, 이번 턴이 종료되었을 때 돌에서 풀려남
만약 두 명 이상의 전사들이 같은 칸에 위치해있다면 해당 칸의 전사들은 모두 돌로 변하게 됨

이때 메두사는 상하좌우 중 전사를 가장 많이 볼 수 있는 방향을 바라봄
같은 수의 전사를 볼 수 있는 방향이 여러 개라면, 상하좌우의 우선순위로 방향을 결정

3. 전사들의 이동
돌로 변하지 않은 전사들은 메두사를 향해 최대 두 칸까지 이동
전사들은 이동 중 같은 칸을 공유할 수 있음

첫 번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 이동
이런 방향이 두 개 이상일 경우 상하좌우의 우선순위로 방향을 선택
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음

두 번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 더 이동
이런 방향이 두 개 이상일 경우 "좌우상하"의 우선순위로 방향을 선택
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음

4. 전사의 공격
메두사와 같은 칸에 도달한 전사는 메두사를 공격
그러나 메두사가 너무 강한 나머지 이기지 못하고 사라짐

위의 네 단계에서 최단경로를 계산할 때는 맨해튼 거리를 기준

위의 네 단계가 반복되어 메두사가 공원에 도달할 때까지 매 턴마다
해당 턴에서 모든 전사가 이동한 거리의 합, 메두사로 인해 돌이 된 전사의 수, 메두사를 공격한 전사의 수를 출력
메두사가 공원에 도착하는 턴에는 0을 출력하고 종료
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;

#define MAX_N 50
#define DIR_NUM 4

int n, m;
int grid[MAX_N][MAX_N];

pair<int, int> medu_pos;
pair<int, int> start_pos;
pair<int, int> end_pos;
int medu_dir[MAX_N][MAX_N];
int medu_sight[MAX_N][MAX_N];
int tmp_sight[MAX_N][MAX_N];

int knight_cnt[MAX_N][MAX_N];
int knight_next[MAX_N][MAX_N];
int is_rocked[MAX_N][MAX_N];

int move_amount, rocked_cnt, attack_cnt;

int dx[DIR_NUM] = { -1,1,0,0 };
int dy[DIR_NUM] = { 0,0,-1,1 };

bool visited[MAX_N][MAX_N];
int back_x[MAX_N][MAX_N];
int back_y[MAX_N][MAX_N];

bool inRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

bool isWay() {
	memset(visited, false, sizeof(visited));
	queue<pair<int, int>> q;

	q.push(start_pos);
	visited[start_pos.first][start_pos.second] = true;
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();

		if (cx == end_pos.first && cy == end_pos.second) {
			while (true) {
				int bx = back_x[cx][cy], by = back_y[cx][cy];

				for (int dir = 0; dir < DIR_NUM; dir++) {
					if (bx + dx[dir] == cx && by + dy[dir] == cy) {
						medu_dir[bx][by] = dir;
						break;
					}
				}
				
				cx = bx, cy = by;
				if (cx == start_pos.first && cy == start_pos.second) break;
			}

			return true;
		}

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (inRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 0) {
				q.push({nx, ny});
				visited[nx][ny] = true;
				back_x[nx][ny] = cx;
				back_y[nx][ny] = cy;
			}
		}
	}

	return false;
}

void meduMove() {
	int cx = medu_pos.first, cy = medu_pos.second;
	int dir = medu_dir[cx][cy];
	cx += dx[dir], cy += dy[dir];
	medu_pos.first = cx, medu_pos.second = cy;

	if (knight_cnt[cx][cy] > 0) knight_cnt[cx][cy] = 0;
}

/*
2. 메두사의 시선
메두사는 상하좌우 하나의 방향을 선택해 바라봄
메두사는 바라보는 방향으로 90도의 시야각을 가지며
시야각 범위 안에 있는 전사들을 볼 수 있음
메두사의 시야각 안에 들어와있지만 다른 전사에 가려진 전사의 경우 메두사에게 보이지 않음
메두사가 본 전사들은 모두 돌로 변해 현재 턴에는 움직일 수 없으며, 이번 턴이 종료되었을 때 돌에서 풀려남
만약 두 명 이상의 전사들이 같은 칸에 위치해있다면 해당 칸의 전사들은 모두 돌로 변하게 됨

이때 메두사는 상하좌우 중 전사를 가장 많이 볼 수 있는 방향을 바라봄
같은 수의 전사를 볼 수 있는 방향이 여러 개라면, 상하좌우의 우선순위로 방향을 결정
*/

int meduUpCnt(bool is_test) {
	memset(tmp_sight, 0, sizeof(tmp_sight));

	int cnt = 0;
	int mx = medu_pos.first, my = medu_pos.second;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = mx - i, ny = my - i + j;
			if (inRange(nx, ny)) (is_test? tmp_sight[nx][ny] = 1 : medu_sight[nx][ny] = 1);
		}
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = mx - i, ny = my - i + j;
			if (inRange(nx, ny) && knight_cnt[nx][ny] > 0 && (tmp_sight[nx][ny] == 1 || medu_sight[nx][ny] == 1)) {
				cnt += knight_cnt[nx][ny];
				if (!is_test) {
					is_rocked[nx][ny] = 1;
					rocked_cnt += knight_cnt[nx][ny];
				}

				if (ny < my) {
					for (int k = 1; k < n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nnx = nx - k, nny = ny - k + l;
							if (inRange(nnx, nny)) (is_test?tmp_sight[nnx][nny] = 0:medu_sight[nnx][nny] = 0);
						}
					}
				}
				else if (ny == my) {
					for (int k = 1; k < n; k++) {
						int nnx = nx - k, nny = ny;
						if (inRange(nnx, nny)) (is_test?tmp_sight[nnx][nny] = 0:medu_sight[nnx][nny] = 0);
					}
				}
				else {
					for (int k = 1; k < n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nnx = nx - k, nny = ny + l;
							if (inRange(nnx, nny)) (is_test?tmp_sight[nnx][nny] = 0:medu_sight[nnx][nny] = 0);
						}
					}
				}
			}
		}
	}

	return cnt;
}

int meduDownCnt(bool is_test) {
	memset(tmp_sight, 0, sizeof(tmp_sight));

	int cnt = 0;
	int mx = medu_pos.first, my = medu_pos.second;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = mx + i, ny = my - i + j;
			if (inRange(nx, ny)) (is_test ? tmp_sight[nx][ny] = 1 : medu_sight[nx][ny] = 1);
		}
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = mx + i, ny = my - i + j;
			if (inRange(nx, ny) && knight_cnt[nx][ny] > 0 && (tmp_sight[nx][ny] == 1 || medu_sight[nx][ny] == 1)) {
				cnt += knight_cnt[nx][ny];
				if (!is_test) {
					is_rocked[nx][ny] = 1;
					rocked_cnt += knight_cnt[nx][ny];
				}

				if (ny < my) {
					for (int k = 1; k < n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nnx = nx + k, nny = ny - k + l;
							if (inRange(nnx, nny)) (is_test ? tmp_sight[nnx][nny] = 0 : medu_sight[nnx][nny] = 0);
						}
					}
				}
				else if (ny == my) {
					for (int k = 1; k < n; k++) {
						int nnx = nx + k, nny = ny;
						if (inRange(nnx, nny)) (is_test ? tmp_sight[nnx][nny] = 0 : medu_sight[nnx][nny] = 0);
					}
				}
				else {
					for (int k = 1; k < n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nnx = nx + k, nny = ny + l;
							if (inRange(nnx, nny))(is_test ? tmp_sight[nnx][nny] = 0 : medu_sight[nnx][nny] = 0);
						}
					}
				}
			}
		}
	}

	return cnt;
}

int meduLeftCnt(bool is_test) {
	memset(tmp_sight, 0, sizeof(tmp_sight));

	int cnt = 0;
	int mx = medu_pos.first, my = medu_pos.second;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = mx - i + j, ny = my - i;
			if (inRange(nx, ny)) (is_test?tmp_sight[nx][ny] = 1:medu_sight[nx][ny] = 1);
		}
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = mx - i + j, ny = my - i;
			if (inRange(nx, ny) && knight_cnt[nx][ny] > 0 && (tmp_sight[nx][ny] == 1 || medu_sight[nx][ny] == 1)) {
				cnt += knight_cnt[nx][ny];
				if (!is_test) {
					is_rocked[nx][ny] = 1;
					rocked_cnt += knight_cnt[nx][ny];
				}

				if (nx < mx) {
					for (int k = 1; k < n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nnx = nx - k + l, nny = ny - k;
							if (inRange(nnx, nny)) (is_test ? tmp_sight[nnx][nny] = 0 : medu_sight[nnx][nny] = 0);
						}
					}
				}
				else if (nx == mx) {
					for (int k = 1; k < n; k++) {
						int nnx = nx, nny = ny - k;
						if (inRange(nnx, nny)) (is_test ? tmp_sight[nnx][nny] = 0 : medu_sight[nnx][nny] = 0);
					}
				}
				else {
					for (int k = 1; k < n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nnx = nx + l, nny = ny - k;
							if (inRange(nnx, nny)) (is_test ? tmp_sight[nnx][nny] = 0 : medu_sight[nnx][nny] = 0);
						}
					}
				}
			}
		}
	}

	return cnt;
}

int meduRightCnt(bool is_test) {
	memset(tmp_sight, 0, sizeof(tmp_sight));

	int cnt = 0;
	int mx = medu_pos.first, my = medu_pos.second;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = mx - i + j, ny = my + i;
			if (inRange(nx, ny)) (is_test ? tmp_sight[nx][ny] = 1 : medu_sight[nx][ny] = 1);
		}
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = mx - i + j, ny = my + i;
			if (inRange(nx, ny) && knight_cnt[nx][ny] > 0 && (tmp_sight[nx][ny] == 1 || medu_sight[nx][ny] == 1)) {
				cnt += knight_cnt[nx][ny];
				if (!is_test) {
					is_rocked[nx][ny] = 1;
					rocked_cnt += knight_cnt[nx][ny];
				}

				if (nx < mx) {
					for (int k = 1; k < n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nnx = nx - k + l, nny = ny + k;
							if (inRange(nnx, nny)) (is_test ? tmp_sight[nnx][nny] = 0 : medu_sight[nnx][nny] = 0);
						}
					}
				}
				else if (nx == mx) {
					for (int k = 1; k < n; k++) {
						int nnx = nx, nny = ny + k;
						if (inRange(nnx, nny)) (is_test ? tmp_sight[nnx][nny] = 0 : medu_sight[nnx][nny] = 0);
					}
				}
				else {
					for (int k = 1; k < n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nnx = nx + l, nny = ny + k;
							if (inRange(nnx, nny)) (is_test ? tmp_sight[nnx][nny] = 0 : medu_sight[nnx][nny] = 0);
						}
					}
				}
			}
		}
	}

	return cnt;
}

void meduSee() {
	int max_cnt = -1, max_dir = -1;
	
	int up_cnt = meduUpCnt(true);
	if (max_cnt < up_cnt) {
		max_cnt = up_cnt;
		max_dir = 0;
	}

	int down_cnt = meduDownCnt(true);
	if (max_cnt < down_cnt) {
		max_cnt = down_cnt;
		max_dir = 1;
	}

	
	int left_cnt = meduLeftCnt(true);
	if (max_cnt < left_cnt) {
		max_cnt = left_cnt;
		max_dir = 2;
	}

	int right_cnt = meduRightCnt(true);
	if (max_cnt < right_cnt) {
		max_cnt = right_cnt;
		max_dir = 3;
	}

	memset(medu_sight, 0, sizeof(medu_sight));
	if (max_dir == 0) meduUpCnt(false);
	else if (max_dir == 1) meduDownCnt(false);
	else if (max_dir == 2) meduLeftCnt(false);
	else meduRightCnt(false);
}

/*
3. 전사들의 이동
돌로 변하지 않은 전사들은 메두사를 향해 최대 두 칸까지 이동
전사들은 이동 중 같은 칸을 공유할 수 있음

첫 번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 이동
이런 방향이 두 개 이상일 경우 상하좌우의 우선순위로 방향을 선택
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음

두 번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 더 이동
이런 방향이 두 개 이상일 경우 "좌우상하"의 우선순위로 방향을 선택
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음

4. 전사의 공격
메두사와 같은 칸에 도달한 전사는 메두사를 공격
그러나 메두사가 너무 강한 나머지 이기지 못하고 사라짐

위의 네 단계에서 최단경로를 계산할 때는 맨해튼 거리를 기준

위의 네 단계가 반복되어 메두사가 공원에 도달할 때까지 매 턴마다
해당 턴에서 모든 전사가 이동한 거리의 합, 메두사로 인해 돌이 된 전사의 수, 메두사를 공격한 전사의 수를 출력
메두사가 공원에 도착하는 턴에는 0을 출력하고 종료
*/
int getDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void knightMove() {
	memset(knight_next, 0, sizeof(knight_next));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (knight_cnt[i][j] == 0) continue; // break가 아니고 continue 필요힘
			if (is_rocked[i][j]) {
				knight_next[i][j] += knight_cnt[i][j]; // =이 아니라 +=
				continue;
			}

			int cx = i, cy = j;
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = cx + dx[dir], ny = cy + dy[dir];
				if (inRange(nx, ny) && medu_sight[nx][ny] == 0 && getDist(medu_pos.first, medu_pos.second, cx, cy) > getDist(medu_pos.first, medu_pos.second, nx, ny)) {
					cx = nx, cy = ny;
					move_amount += knight_cnt[i][j];
					break;
				}
			}

			int oppo_dir[] = {2,3,0,1};
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = cx + dx[oppo_dir[dir]], ny = cy + dy[oppo_dir[dir]]; // 이 부분 실수 주의
				if (inRange(nx, ny) && medu_sight[nx][ny] == 0 && getDist(medu_pos.first, medu_pos.second, cx, cy) > getDist(medu_pos.first, medu_pos.second, nx, ny)) {
					cx = nx, cy = ny;
					move_amount += knight_cnt[i][j];
					break;
				}
			}

			if (cx == medu_pos.first && cy == medu_pos.second) attack_cnt += knight_cnt[i][j];
			else knight_next[cx][cy] += knight_cnt[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			knight_cnt[i][j] = knight_next[i][j];
		}
	}
}

void print() {
	cout << "MEDU POS : " << medu_pos.first << " " << medu_pos.second << "\n";
	cout << "MEDU SIGHT" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << medu_sight[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "KNIGHT CNT" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << knight_cnt[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "IS ROCKED" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << is_rocked[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("input.txt", "r", stdin);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			knight_cnt[i][j] = 0;
		}
	}

	cin >> n >> m;
	cin >> start_pos.first >> start_pos.second;
	cin >> end_pos.first >> end_pos.second;

	for (int i = 0; i < m; i++) {
		int r, c; cin >> r >> c;
		knight_cnt[r][c]++;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	medu_pos = start_pos;
	int turn = 0;
	while (true) {
		turn++;
		//cout << "TURN : " << turn << "\n";

		if (!isWay()) {
			cout << -1 << "\n";
			return 0;
		}

		move_amount = rocked_cnt = attack_cnt = 0;
		memset(is_rocked, 0, sizeof(is_rocked));

		//cout << "meduMove" << "\n";
		meduMove();
		if (medu_pos == end_pos) {
			cout << 0 << "\n";
			return 0;
		}
		//print();

		//cout << "meduSee" << "\n";
		meduSee();
		//print();

		//cout << "knightMove" << "\n";
		knightMove();
		//print();

		cout << move_amount << " " << rocked_cnt << " " << attack_cnt << "\n";
	}

	return 0;
}