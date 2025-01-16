/*
참가자 M명 : 위치 
미로 : N x N / (1, 1)
		빈 칸 : 참가자가 이동 가능한 칸
		벽 : 참가자가 이동할 수 없는 칸 / 1이상 9이하의 내구도를 가짐 / 회전할 때 내구도가 1씩 깎임 / 내구도가 0이 되면 빈칸
		출구 : 참가자가 해당 칸에 도달하면, 즉시 탈출

1초마다 모든 참가자는 한 칸씩 움직임.
(x1, y1) (x2, y2)의 최단 거리는 |x1-x2|+|y1-y2|
모든 참가자는 동시에 움직임
상하좌우로 움직일 수 있으며, 벽이 없는 곳(0, 출구)으로 이동 가능
움직인 칸은 현재 머물러 있던 칸보다 출구까지의 최단거리가 가까워야 함
움직일 수 있는 칸이 2개 이상이라면 상하로 움직이는 것을 우선시
참가자가 움직일 수 없는 상황이라면 움직이지 않음
한 칸에 2명 이상의 참가자가 있을 수 있음

모든 참가자가 이동을 끝냈으면 미로가 회전
한 명 이상의 참가자와 출구를 포함한 가장 작은 정사각형을 잡음 > r 최소 > c 최소
선택된 정사각형은 시계방향으로 90도 회전하며, 회전된 벽은 내구도가 1씩 깎임

K초 동안 위의 과정을 계속 반복
만약 K초 전에 모든 참가자가 탈출에 성공한다면, 게임이 끝남
게임이 끝났을 때, 모든 참가자들의 이동 거리 합과 출구 좌표를 출력하는 프로그램
*/
#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 10
#define MAX_M 10
#define DIR_NUM 4

int n, m, k;
int grid[MAX_N + 1][MAX_N + 1];
int next_grid[MAX_N + 1][MAX_N + 1];

pair<int, int> player[MAX_M + 1];
bool is_live[MAX_M + 1];
pair<int, int> exit_pos;

int move_dist;

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

int GetDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

bool InRange(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

void MovePlayer() {
	for (int i = 1; i <= m; i++) {
		if (!is_live[i]) continue;
		int x = player[i].first, y = player[i].second;

		int nx = x + dx[0], ny = y + dy[0];
		if (InRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(x, y, exit_pos.first, exit_pos.second) > GetDist(nx, ny, exit_pos.first, exit_pos.second))) {
			player[i].first = nx, player[i].second = ny;
			move_dist++;
			if (nx == exit_pos.first && ny == exit_pos.second) is_live[i] = false;
			continue;
		}

		nx = x + dx[2], ny = y + dy[2];
		if (InRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(x, y, exit_pos.first, exit_pos.second) > GetDist(nx, ny, exit_pos.first, exit_pos.second))) {
			player[i].first = nx, player[i].second = ny;
			move_dist++;
			if (nx == exit_pos.first && ny == exit_pos.second) is_live[i] = false;
			continue;
		}

		nx = x + dx[1], ny = y + dy[1];
		if (InRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(x, y, exit_pos.first, exit_pos.second) > GetDist(nx, ny, exit_pos.first, exit_pos.second))) {
			player[i].first = nx, player[i].second = ny;
			move_dist++;
			if (nx == exit_pos.first && ny == exit_pos.second) is_live[i] = false;
			continue;
		}

		nx = x + dx[3], ny = y + dy[3];
		if (InRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(x, y, exit_pos.first, exit_pos.second) > GetDist(nx, ny, exit_pos.first, exit_pos.second))) {
			player[i].first = nx, player[i].second = ny;
			move_dist++;
			if (nx == exit_pos.first && ny == exit_pos.second) is_live[i] = false;
			continue;
		}
	}
}

bool ExistCheck(int size, int x, int y) {
	int ex = exit_pos.first, ey = exit_pos.second;

	if (!(x <= ex && ex <= x + size - 1 && y <= ey && ey <= y + size - 1)) return false;

	for (int i = 1; i <= m; i++) {
		if (!is_live[i]) continue;
		int px = player[i].first, py = player[i].second;

		if (x <= px && px <= x + size - 1 && y <= py && py <= y + size - 1) return true;
	}

	return false;
}

/*
0 0 0 0 0 (2, 5) (x, y)
0 0 0 0 1
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 1 0 (5, 4) (y, n - x + 1)

*/

void RotateGrid() {
	for (int size = 2; size <= n; size++) {
		for (int x = 1; x <= n - size + 1; x++) {
			for (int y = 1; y <= n - size + 1; y++) {
				if (!ExistCheck(size, x, y)) continue;

				// 출구 회전
				int ox = exit_pos.first - x + 1 , oy = exit_pos.second - y + 1;
				int rx = oy, ry = size - ox + 1;
				exit_pos.first = rx + x - 1;
				exit_pos.second = ry + y - 1;

				// 플레이어 회전
				for (int i = 1; i <= m; i++) {
					if (!is_live[i]) continue;
					int px = player[i].first, py = player[i].second;
					if (!(x <= px && px <= x + size - 1 && y <= py && py <= y + size - 1)) continue;
					int ox = px - x + 1, oy = py - y + 1;
					int rx = oy, ry = size - ox + 1;
					player[i].first = rx + x - 1;
					player[i].second = ry + y - 1;
				}

				// 그리드 회전
				for (int row = x; row <= x + size - 1; row++) {
					for (int col = y; col <= y + size - 1; col++) {
						next_grid[row][col] = 0;
					}
				}

				for (int row = x; row <= x + size - 1; row++) {
					for (int col = y; col <= y + size - 1; col++) {
						if (grid[row][col] == 0) continue;
						int ox = row - x + 1, oy = col - y + 1;
						int rx = oy, ry = size - ox + 1;
						next_grid[rx + x - 1][ry + y - 1] = grid[row][col] - 1;
					}
				}

				for (int row = x; row <= x + size - 1; row++) {
					for (int col = y; col <= y + size - 1; col++) {
						grid[row][col] = next_grid[row][col];
					}
				}

				return;
			}
		}
	}
}

void Print() {
	for (int i = 1; i <= m; i++) {
		if(is_live[i]) cout << '#' << i << " : " << player[i].first << " " << player[i].second << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}
	
	for (int i = 1; i <= m; i++) {
		cin >> player[i].first >> player[i].second;
		is_live[i] = true;
	}
	cin >> exit_pos.first >> exit_pos.second;

	for (int t = 1; t <= k; t++) {

		MovePlayer();

		bool is_end = true;
		for (int i = 1; i <= m; i++) {
			if (is_live[i]) {
				is_end = false;
				break;
			}
		}
		if(!is_end) RotateGrid();
		else break;
	}

	cout << move_dist << "\n";
	cout << exit_pos.first << " " << exit_pos.second << "\n";
	return 0;
}