/*
격자 : n * n 0-based
	해당 칸의 주인 / 독점 계약이 유효한 턴 수
플레이어 : m명. 각자 격자칸에서 한 자리를 차지하게 됨
			번호 / 위치 / 방향

턴이 한 번 진행될 때 각 플레이어들은 한 칸씩 이동
해당 칸에 이동했을 때 플레이어는 해당 칸을 독점 계약
초기 상태에 위치한 땅 역시 해당 플레이어의 독점 계약 칸

독점 계약은 k만큼의 턴 동안만 유효. k턴이 지나게 되면 해당 칸은 다시 주인이 없는 칸으로 돌아감

각 플레이어는 각 방향별로 이동 우선순위를 가짐. 
우선 플레이어는 본인에게 인접한 상하좌우 4칸 중 아무도 독점계약을 맺지 않은 칸으로 이동
만약 그러한 칸이 없을 경우 인접한 4방향 중 본인이 독점계약한 땅으로 이동
이때 이동할 수 있는 칸이 여러개일 수 있음으로 이동 우선순위에 따라 움직일 칸을 결정
플레이어가 보고 있는 방향은 그 직전에 이동한 방향

모든 플레이어가 이동한 후 한 칸에 여러 플레이어가 있을 경우
가장 작은 번호를 가진 플레이어만 살아남고 나머지 플레이어는 게임에서 사라짐

우측 상단 숫자 : 해당 칸의 주인
우측 하단 숫자 : 독점 계약이 유효한 턴 수

이 과정이 계속 반복될 때 1번 플레이어만 살아남기까지 걸린 턴의 수를 계산
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tuple>
using namespace std;

#define MAX_N 20
#define MAX_M 400
#define DIR_NUM 4
#define OUT_OF_GRID make_pair(-1, -1)

int n, m, k;
pair<int, int > grid[MAX_N][MAX_N];  // 각 격자의 주인과 남은 턴 수
pair<int, int> p_pos[MAX_M + 1]; // 플레이어들의 위치
pair<int, int> next_pos[MAX_M + 1]; // 플레이어들의 위치
int p_dir[MAX_M + 1]; // 플레이어들의 방향
int next_dir[MAX_M + 1]; // 플레이어들의 방향
int dir_priority[MAX_M + 1][DIR_NUM][DIR_NUM];

int dx[DIR_NUM] = { -1,1,0,0 };
int dy[DIR_NUM] = { 0,0,-1,1 };

void print() {
	cout << "GRID" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cout << "{";
			cout << grid[x][y].first << " " << grid[x][y].second;
			cout << "} ";
		}
		cout << "\n";
	}
	
	cout << "PLAYER INFO" << "\n";
	for (int i = 1; i <= m; i++) {
		cout << i << " : " << p_pos[i].first << " " << p_pos[i].second <<  " " << p_dir[i] << "\n";
	}

	/*
	cout << "DIR PRIORITY" << "\n";
	for (int i = 1; i <= m; i++) {
		for (int cur_dir = 0; cur_dir < DIR_NUM; cur_dir++) {
			for (int cnt = 0; cnt < DIR_NUM; cnt++) {
				cout << dir_priority[i][cur_dir][cnt] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
	*/
}

bool isOver() {
	for (int i = 2; i <= m; i++) {
		if (p_pos[i] != OUT_OF_GRID) return false;
	}
	return true;
}

/*
턴이 한 번 진행될 때 각 플레이어들은 한 칸씩 이동
해당 칸에 이동했을 때 플레이어는 해당 칸을 독점 계약
초기 상태에 위치한 땅 역시 해당 플레이어의 독점 계약 칸

독점 계약은 k만큼의 턴 동안만 유효.k턴이 지나게 되면 해당 칸은 다시 주인이 없는 칸으로 돌아감

각 플레이어는 각 방향별로 이동 우선순위를 가짐.
우선 플레이어는 본인에게 인접한 상하좌우 4칸 중 아무도 독점계약을 맺지 않은 칸으로 이동
만약 그러한 칸이 없을 경우 인접한 4방향 중 본인이 독점계약한 땅으로 이동
이때 이동할 수 있는 칸이 여러개일 수 있음으로 이동 우선순위에 따라 움직일 칸을 결정
플레이어가 보고 있는 방향은 그 직전에 이동한 방향

모든 플레이어가 이동한 후 한 칸에 여러 플레이어가 있을 경우
가장 작은 번호를 가진 플레이어만 살아남고 나머지 플레이어는 게임에서 사라짐
*/

bool inRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

void movePlayer(int idx) {
	// 플레이어의 위치와 방향 같이 관리!
	int cx, cy, cd;
	tie(cx, cy) = p_pos[idx];
	cd = p_dir[idx];

	for (int i = 0; i < DIR_NUM; i++) {
		int nd = dir_priority[idx][cd][i];
		int nx = cx + dx[nd], ny = cy + dy[nd];
		if (inRange(nx, ny) && grid[nx][ny].first == 0) {
			next_pos[idx] = { nx, ny };
			next_dir[idx] = nd;
			return;
		}
	}

	for (int i = 0; i < DIR_NUM; i++) {
		int nd = dir_priority[idx][cd][i];
		int nx = cx + dx[nd], ny = cy + dy[nd];
		if (inRange(nx, ny) && grid[nx][ny].first == idx) {
			next_pos[idx] = { nx, ny };
			next_dir[idx] = nd;
			return;
		}
	}
}

void collide() {
	for (int i = 1; i < m; i++) {
		for (int j = i + 1; j <= m; j++) {
			if (next_pos[i] == OUT_OF_GRID || next_pos[j] == OUT_OF_GRID) continue;

			if (next_pos[i] == next_pos[j]) {
				p_pos[j] = OUT_OF_GRID;
				
				p_pos[i] = next_pos[i];
				p_dir[i] = next_dir[i];
				grid[p_pos[i].first][p_pos[i].second] = { i, k + 1};
			}
		}
	}
}

void moveAllPlayer() {
	for (int i = 1; i <= m; i++) {
		next_pos[i] = OUT_OF_GRID;
		next_dir[i] = -1;
	}

	for (int i = 1; i <= m; i++) {
		if (p_pos[i] == OUT_OF_GRID) continue;
		movePlayer(i);
	}

	for (int i = 1; i <= m; i++) {
		if (next_pos[i] != OUT_OF_GRID) {
			p_pos[i] = next_pos[i];
			p_dir[i] = next_dir[i];
			grid[p_pos[i].first][p_pos[i].second] = { i, k + 1 };
		}
	}
	
	collide();
}

void reduceTurn() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (grid[x][y].first == 0) continue;

			grid[x][y].second--;

			if (grid[x][y].second == 0) {
				grid[x][y].first = 0;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);

	cin >> n >> m >> k;

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = {0, 0};
		}
	}

	for (int i = 1; i <= m; i++) {
		p_pos[i] = OUT_OF_GRID;
		p_dir[i] = -1;
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			int num; cin >> num;
			if (num > 0) {
				grid[x][y] = { num, k };
				p_pos[num] = { x, y };
			}
		}
	}

	for (int i = 1; i <= m; i++) {
		int dir; cin >> dir;
		p_dir[i] = dir - 1;
	}

	for (int i = 1; i <= m; i++) {
		for (int cur_dir = 0; cur_dir < DIR_NUM; cur_dir++) {
			for (int cnt = 0; cnt < DIR_NUM; cnt++) {
				int dir; cin >> dir;
				dir_priority[i][cur_dir][cnt] = dir - 1;
			}
		}
	}

	//print();
	
	int turn = 0;
	while (1) {
		turn++;
		//cout << "///////////// " << turn << " /////////////" << "\n";

		//if (turn > 20) return 0;

		if (turn >= 1000) {
			cout << -1 << "\n";
			return 0;
		}
		if (isOver()) {
			cout << turn - 1 << "\n";
			return 0;
		}

		moveAllPlayer();
		//print();

		reduceTurn();
		//print();
	}
}
