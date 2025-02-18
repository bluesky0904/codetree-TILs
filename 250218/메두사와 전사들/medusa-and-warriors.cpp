/*
1. 메두사의 이동
메두사는 최단 경로를 따라 도로를 따라 한 칸 이동
메두사가 이동한 칸에 전사가 있을 경우 전사는 메두사의 공격을 받고 사라짐
만약 집으로부터 공원까지 여러 최단경로가 가능하다면 상, 하, 좌, 우의 우선순위
메두사의 집으로부터 공원까지 도달하는 경로가 없을 수도 있음

2. 메두사의 시선
메두사는 상, 하, 좌, 우 하나의 방향을 선택해 바라본다.
메두사는 바라보는 방향으로 90도의 시야각을 가지며, 시야각 범위 안에 있는 전사들을 볼 수 있다.

메두사의 시야각 안에 들어와있지만 다른 전사에 가려진 전사의 경우 메두사에게 보이지 않음
특정 전사에 의해 메두사에게 가려지는 범위는 메두사와 해당 전사의 상대적인 위치에 의해 결정
메두사에게 보이지 않는 칸 서술 방식 이해가 잘..

메두사가 본 전사들은 모두 돌로 변해 현재 턴에는 움직일 수 없으며, 이번 턴이 종료되었을 때 돌에서 풀려남
만약 두 명 이상의 전사들이 같은 칸에 위치해있다면 해당 칸의 전사들은 모두 돌로 변함

메두사는 상, 하, 좌, 우 중 전사를 가장 많이 볼 수 있는 방향을 바라봄
같은 수의 전사를 볼 수 있는 방향이 여러 개라면, 상하좌우의 우선순위로 방향을 결정

3. 전사들의 이동
돌로 변하지 않은 전사들은 메두사를 향해 최대 두 칸까지 이동.
전사들은 이동 중 같은 칸을 공유할 수 있음

첫번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 이동
이런 방향이 두 개 이상일 경우 상하좌우의 우선순위로 방향을 선택
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음

두번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 더 이동
이런 방향이 두 개 이상일 경우 좌우상하의 우선순위로 방향을 선택
격자의 바깥으로 나갈 수 없으며 메두사의 시야에 들어오는 곳으로 이동할 수 없음

4. 전사의 공격
메두사와 같은 칸에 도달한 전사는 메두사를 공격
그러나 메두사가 너무 강한 나머지 이기지 못하고 사라짐

위의 네 단계에서 최단경로를 계산할 때는 맨해튼 거리를 기준

위의 네 단계가 반복되어 메두사가 공원에 도달할 때까지
매 턴마다 해당 턴에서 모든 전사가 이동한 거리의 합, 메두사로 인해 돌이 된 전사 수, 메두사를 공격한 전사 수를
공백을 사이에 두고 차례대로 출력하는 프로그램

단, 메두사가 공원에 도착하는 턴에는 0을 출력하고 프로그램 종료
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAX_N 50
#define MAX_M 300
#define DIR_NUM 4

int n, m;
pair<int, int> medu_pos;
pair<int, int> rotate_medu;
pair<int, int> start_pos;
pair<int, int> end_pos;
int back_x[MAX_N][MAX_N];
int back_y[MAX_N][MAX_N];
int medu_dir[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int knight_pos[MAX_N][MAX_N]; // 격자의 숫자는 해당 칸의 기사의 수를 의미
int rotate_knight[MAX_N][MAX_N];
int rotate_tmp[MAX_N][MAX_N];
int is_rock[MAX_N][MAX_N];
int rotate_rock[MAX_N][MAX_N];
int tmp_rock[MAX_N][MAX_N];

int grid[MAX_N][MAX_N];
int medu_sight[MAX_N][MAX_N];
int rotate_sight[MAX_N][MAX_N];
int sight_tmp[MAX_N][MAX_N];

int move_amount, rocked_cnt, attack_cnt;

int dx[DIR_NUM] = {-1, 1, 0, 0};
int dy[DIR_NUM] = {0, 0, -1, 1};

bool inRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

bool isWay() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			back_x[i][j] = back_y[i][j] = medu_dir[i][j] = -1;
			visited[i][j] = false;
		}
	}

	queue<pair<int, int>> q;
	q.push(start_pos);
	visited[start_pos.first][start_pos.second] = true;
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();

		if (cx == end_pos.first && cy == end_pos.second) {
			while (true) {
				int bx = back_x[cx][cy], by = back_y[cx][cy];

				if (cy == by && bx == cx + 1) medu_dir[bx][by] = 0;
				else if (cy == by && cx == bx + 1) medu_dir[bx][by] = 1;
				else if (cx == bx && by == cy + 1) medu_dir[bx][by] = 2;
				else if (cx == bx && cy == by + 1) medu_dir[bx][by] = 3;

				if (bx == start_pos.first && by == start_pos.second) break;

				cx = bx, cy = by;
			}
			return true;
		}

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (inRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 0) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
				back_x[nx][ny] = cx;
				back_y[nx][ny] = cy;
			}
		}
	}

	return false;
}

void meduMove() {
	int dir = medu_dir[medu_pos.first][medu_pos.second];
	medu_pos.first += dx[dir], medu_pos.second += dy[dir];

	if (knight_pos[medu_pos.first][medu_pos.second] > 0) {
		knight_pos[medu_pos.first][medu_pos.second] = 0;
	}
}

int meduDown(int degree) {
	int cnt = 0;
	memset(sight_tmp, 0, sizeof(sight_tmp));

	rotate_medu = medu_pos;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			rotate_knight[i][j] = knight_pos[i][j];
		}
	}
	int rotate_cnt = degree / 90;
	while (rotate_cnt--) {
		rotate_medu = { rotate_medu.second, n - rotate_medu.first - 1 };

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				rotate_tmp[i][j] = 0;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				rotate_tmp[j][n - i - 1] = rotate_knight[i][j];
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				rotate_knight[i][j] = rotate_tmp[i][j];
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = rotate_medu.first + i, ny = rotate_medu.second - i + j;
			if (inRange(nx, ny)) {
				sight_tmp[nx][ny] = 1;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = rotate_medu.first + i, ny = rotate_medu.second - i + j;
			if (inRange(nx, ny) && sight_tmp[nx][ny] == 1 && rotate_knight[nx][ny] > 0) {
				cnt += rotate_knight[nx][ny];

				if (ny < rotate_medu.second) {
					for (int k = 1; k <= n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nk = nx + k, nl = ny - k + l;
							if (inRange(nk, nl)) sight_tmp[nk][nl] = 0;
						}
					}
				}
				else if (ny == rotate_medu.second) {
					for (int k = 1; k <= n; k++) {
						int nk = nx + k;
						if (inRange(nk, ny)) sight_tmp[nk][ny] = 0;
					}
				}
				else if (ny > rotate_medu.second) {
					for (int k = 1; k <= n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nk = nx + k, nl = ny + l;
							if (inRange(nk, nl)) sight_tmp[nk][nl] = 0;
						}
					}
				}
			}
		}
	}

	/*
	cout << "TMP" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << sight_tmp[i][j] << " ";
		}
		cout << "\n";
	}
	*/

	return cnt;
}

void meduSight() {
	int max_cnt = -1, max_degree = -1;
	
	int up_cnt = meduDown(180);
	if (max_cnt < up_cnt) {
		max_cnt = up_cnt;
		max_degree = 180;
	}

	int down_cnt = meduDown(0);
	if (max_cnt < down_cnt) {
		max_cnt = down_cnt;
		max_degree = 0;
	}

	int left_cnt = meduDown(270);
	if (max_cnt < left_cnt) {
		max_cnt = left_cnt;
		max_degree = 270;
	}

	int right_cnt = meduDown(90);
	if (max_cnt < right_cnt) {
		max_cnt = right_cnt;
		max_degree = 90;
	}

	// 메두사 시야 표시, 돌로 변한 기사 표시
	memset(sight_tmp, 0, sizeof(sight_tmp));
	memset(rotate_rock, 0, sizeof(rotate_rock));
	memset(tmp_rock, 0, sizeof(tmp_rock));
	memset(sight_tmp, 0, sizeof(sight_tmp));
	memset(medu_sight, 0, sizeof(medu_sight));

	rotate_medu = medu_pos;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			rotate_knight[i][j] = knight_pos[i][j];
		}
	}
	int rotate_cnt = max_degree / 90;
	while (rotate_cnt--) {
		rotate_medu = { rotate_medu.second, n - rotate_medu.first - 1 };

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				rotate_tmp[i][j] = 0;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				rotate_tmp[j][n - i - 1] = rotate_knight[i][j];
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				rotate_knight[i][j] = rotate_tmp[i][j];
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = rotate_medu.first + i, ny = rotate_medu.second - i + j;
			if (inRange(nx, ny)) {
				sight_tmp[nx][ny] = 1;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 2 * i + 1; j++) {
			int nx = rotate_medu.first + i, ny = rotate_medu.second - i + j;
			if (inRange(nx, ny) && sight_tmp[nx][ny] == 1 && rotate_knight[nx][ny] > 0) {
				rotate_rock[nx][ny] = true;
				rocked_cnt += rotate_knight[nx][ny];

				if (ny < rotate_medu.second) {
					for (int k = 1; k <= n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nk = nx + k, nl = ny - k + l;
							if (inRange(nk, nl)) sight_tmp[nk][nl] = 0;
						}
					}
				}
				else if (ny == rotate_medu.second) {
					for (int k = 1; k <= n; k++) {
						int nk = nx + k;
						if (inRange(nk, ny)) sight_tmp[nk][ny] = 0;
					}
				}
				else if (ny > rotate_medu.second) {
					for (int k = 1; k <= n; k++) {
						for (int l = 0; l < k + 1; l++) {
							int nk = nx + k, nl = ny + l;
							if (inRange(nk, nl)) sight_tmp[nk][nl] = 0;
						}
					}
				}
			}
		}
	}

	int recovery_cnt = 4 - (max_degree / 90);
	while (recovery_cnt--) {
		rotate_medu = { rotate_medu.second, n - rotate_medu.first - 1 };

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				rotate_sight[i][j] = 0;
				tmp_rock[i][j] = 0;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				rotate_sight[j][n - i - 1] = sight_tmp[i][j];
				tmp_rock[j][n - i - 1] = rotate_rock[i][j];
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				sight_tmp[i][j] = rotate_sight[i][j];
				rotate_rock[i][j] = tmp_rock[i][j];
			}
		}
	}

	medu_pos = rotate_medu;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			medu_sight[i][j] = sight_tmp[i][j];
			is_rock[i][j] = rotate_rock[i][j];
		}
	}
}

/*
3. 전사들의 이동
돌로 변하지 않은 전사들은 메두사를 향해 최대 두 칸까지 이동.
전사들은 이동 중 같은 칸을 공유할 수 있음

첫번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 이동
이런 방향이 두 개 이상일 경우 상하좌우의 우선순위로 방향을 선택
격자의 바깥으로 나갈 수 없으며, 메두사의 시야에 들어오는 곳으로는 이동할 수 없음

두번째 이동
메두사와의 거리를 줄일 수 있는 방향으로 한 칸 더 이동
이런 방향이 두 개 이상일 경우 좌우상하의 우선순위로 방향을 선택
격자의 바깥으로 나갈 수 없으며 메두사의 시야에 들어오는 곳으로 이동할 수 없음

4. 전사의 공격
메두사와 같은 칸에 도달한 전사는 메두사를 공격
그러나 메두사가 너무 강한 나머지 이기지 못하고 사라짐

위의 네 단계에서 최단경로를 계산할 때는 맨해튼 거리를 기준
*/

int next_knight_pos[MAX_N][MAX_N];
int getDist(int x1, int y1, int x2, int y2) {
	return (abs(x1 - x2) + abs(y1 - y2));
}

void knightMove() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_knight_pos[x][y] = 0;
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (knight_pos[x][y] == 0) continue;
			if (is_rock[x][y] == 1) {
				next_knight_pos[x][y] = knight_pos[x][y];
				continue;
			}
			
			int cx = x, cy = y;
			
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = cx + dx[dir], ny = cy + dy[dir];
				if (inRange(nx, ny) && medu_sight[nx][ny] == 0 && getDist(medu_pos.first, medu_pos.second, cx, cy) > getDist(medu_pos.first, medu_pos.second, nx, ny)) {
					cx = nx, cy = ny;
					move_amount += knight_pos[x][y];
					break;
				}
			}

			int oppoDir[] = { 2, 3, 0, 1};
			for (int dir : oppoDir) {
				int nx = cx + dx[dir], ny = cy + dy[dir];
				if (inRange(nx, ny) && medu_sight[nx][ny] == 0 && getDist(medu_pos.first, medu_pos.second, cx, cy) > getDist(medu_pos.first, medu_pos.second, nx, ny)) {
					cx = nx, cy = ny;
					move_amount += knight_pos[x][y];
					break;
				}
			}

			if (cx == medu_pos.first && cy == medu_pos.second) {
				attack_cnt += knight_pos[x][y];
			}
			else{
				next_knight_pos[cx][cy] += knight_pos[x][y];
			}
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			knight_pos[x][y] = next_knight_pos[x][y];
		}
	}
}

void print(){
	/*
	cout << "MEDU DIR" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << medu_dir[i][j] << " ";
		}
		cout << "\n";
	}
	*/

	cout << "MEDU POS" << "\n";
	cout << medu_pos.first << " " << medu_pos.second << "\n";
	cout << "MEDU SIGHT" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << medu_sight[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "KNIGHT POS" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << knight_pos[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "IS ROCK" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << is_rock[i][j] << " ";
		}
		cout << "\n";
	}
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m;
	cin >> start_pos.first >> start_pos.second;
	cin >> end_pos.first >> end_pos.second;

	medu_pos = start_pos;
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		knight_pos[x][y]++;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	int turn = 0;
	while (true) {
		turn++;
		memset(is_rock, 0, sizeof(is_rock));
		//cout << "TURN :" << turn << "\n";
		if (!isWay()) {
			cout << -1 << "\n";
			return 0;
		}

		move_amount = rocked_cnt = attack_cnt = 0;
		//print();
		
		//cout << "meduMove" << "\n";
		meduMove();
		//print();

		if (medu_pos == end_pos) {
			cout << 0 << "\n";
			return 0;
		}

		//cout << "meduSight" << "\n";
		meduSight();
		//print();

		//cout << "knightMove" << "\n";
		knightMove();
		//print();

		cout << move_amount << " " << rocked_cnt << " " << attack_cnt << "\n";
	}

	return 0;
}