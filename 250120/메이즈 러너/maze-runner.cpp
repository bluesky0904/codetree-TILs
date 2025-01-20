/*
미로 : N x N grid / 1-based
	0 : 빈칸, 참가자 이동 가능
	1~9 : 벽, 참가자 이동 불가, 회전시 1씩 깎임, 0이 되면 빈칸으로 변경
	출구 : 참가자가 해당 칸에 도달하면, 즉시 탈출
참가자 : M명, 위치, 탈출 여부
출구

K초 동안 반복. 만약 K초 전에 모든 참가자가 탈출에 성공한다면 게임 종료.

1. 참가자 움직이기
1초마다 모든 참가자는 동시에 한 칸씩 움직임
(x1, y1), (x2, y2)의 최단거리는 |x1-x2|+|y1-y2|
상하좌우로 움직일 수 있고 벽이 없는 곳으로 이동 가능
움직인 칸은 현재 칸보다 출구까지의 최단거리가 더 가까워야 함
움직일 수 있는 칸이 2개 이상이라면, 상하로 움직이는 것을 우선시
참가자가 움직일 수 없는 상황이라면 움직이지 않음
한 칸에 2명 이상의 참가자가 있을 수 있음

2. 미로 회전
한 명 이상의 참가자와 출구를 포함한 정사각형을 선택
크기 최소 > 행 최소 > 열 최소
선택된 정사각형은 시계방향으로 90도 회전하며, 회전된 벽은 내구도가 1씩 깎임

게임이 끝났을 때, 모든 참가자들의 이동 거리 합과 출구 좌표를 출력
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <cmath>
#include <tuple>
using namespace std;

#define MAX_N 10
#define MAX_M 10
#define DIR_NUM 4

int n, m, k;
int ans;
int grid[MAX_N + 1][MAX_N + 1];
int next_grid[MAX_N + 1][MAX_N + 1];

pair<int, int> exit_pos;
pair<int, int> runner[MAX_M + 1];
bool is_live[MAX_M + 1];

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool isAllExit() {
	for (int i = 1; i <= m; i++) {
		if (is_live[i]) return false;
	}
	return true;
}

int GetDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

bool inRange(int x, int y) {
	return (x >= 1 && x <= n && y >= 1 && y <= n);
}

void moveAllRunner() {
	int ex = exit_pos.first, ey = exit_pos.second;

	for (int i = 1; i <= m; i++) {
		if (!is_live[i]) continue;
		
		int cx = runner[i].first, cy = runner[i].second;

		int nx = cx + dx[0], ny = cy + dy[0];
		int next_dist = GetDist(nx, ny, ex, ey);
		if (inRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(cx, cy, ex, ey) > next_dist)) {
			runner[i] = { nx, ny };
			ans++;
			if (next_dist == 0) is_live[i] = false;
			continue;
		}

		nx = cx + dx[2], ny = cy + dy[2];
		next_dist = GetDist(nx, ny, ex, ey);
		if (inRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(cx, cy, ex, ey) > next_dist)) {
			runner[i] = { nx, ny };
			ans++;
			if (next_dist == 0) is_live[i] = false;
			continue;
		}

		nx = cx + dx[1], ny = cy + dy[1];
		next_dist = GetDist(nx, ny, ex, ey);
		if (inRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(cx, cy, ex, ey) > next_dist)) {
			runner[i] = { nx, ny };
			ans++;
			if (next_dist == 0) is_live[i] = false;
			continue;
		}

		nx = cx + dx[3], ny = cy + dy[3];
		next_dist = GetDist(nx, ny, ex, ey);
		if (inRange(nx, ny) && grid[nx][ny] == 0 && (GetDist(cx, cy, ex, ey) > next_dist)) {
			runner[i] = { nx, ny };
			ans++;
			if (next_dist == 0) is_live[i] = false;
			continue;
		}
	}
}

tuple<int, int, int> selectRec() {
	int ex = exit_pos.first, ey = exit_pos.second;

	for (int size = 2; size <= n; size++) {
		for (int row = 1; row <= n - size + 1; row++) {
			for (int col = 1; col <= n - size + 1; col++) {
				if (!(row <= ex && ex <= row + size - 1 && col <= ey && ey <= col + size - 1)) continue;

				bool is_runner_in = false;
				for (int i = 1; i <= m; i++) {
					int cx = runner[i].first, cy = runner[i].second;

					if (!is_live[i]) continue;
					if (row <= cx && cx <= row + size - 1 && col <= cy && cy <= col + size - 1) {
						is_runner_in = true;
						break;
					}
				}

				if (is_runner_in) return make_tuple(size, row, col);
				else continue;
			}
		}
	}
	return make_tuple(-1, -1, -1);
}

void rotateGrid() {
	int rec_size, sx, sy;
	tie(rec_size, sx, sy) = selectRec();

	if (rec_size == -1) return;

	// 그리드 회전
	for (int x = sx; x <= sx + rec_size - 1; x++) {
		for (int y = sy; y <= sy + rec_size - 1; y++) {
			next_grid[x][y] = 0;
		}
	}

	for (int x = sx; x <= sx + rec_size - 1; x++) {
		for (int y = sy; y <= sy + rec_size - 1; y++) {
			if (grid[x][y] == 0) continue;

			int ox = x - sx + 1, oy = y - sy + 1;
			int rx = oy, ry = rec_size - ox + 1;
			next_grid[rx + sx - 1][ry + sy - 1] = grid[x][y] - 1;
		}
	}

	for (int x = sx; x <= sx + rec_size - 1; x++) {
		for (int y = sy; y <= sy + rec_size - 1; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}

	// 출구 회전
	int ox = exit_pos.first - sx + 1, oy = exit_pos.second - sy + 1;
	int rx = oy, ry = rec_size - ox + 1;
	exit_pos = { rx + sx - 1, ry + sy - 1};

	// 러너 회전
	for (int i = 1; i <= m; i++) {
		int cx = runner[i].first, cy = runner[i].second;

		if (!is_live[i]) continue;
		if (sx <= cx && cx <= sx + rec_size - 1 && sy <= cy && cy <= sy + rec_size - 1) {
			int ox = cx - sx + 1, oy = cy - sy + 1;
			int rx = oy, ry = rec_size - ox + 1;
			runner[i] = { rx + sx - 1, ry + sy - 1};
		}
	}
}

void print() {
	cout << "GRID" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "RUNNERS" << "\n";
	for (int i = 1; i <= m; i++) {
		cout << i << " : " << runner[i].first << " " << runner[i].second << "\n";
	}
	cout << "EXIT" << "\n";
	cout << exit_pos.first << " " << exit_pos.second << "\n";
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}
	
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		runner[i] = { x, y };
		is_live[i] = true;
	}

	cin >> exit_pos.first >> exit_pos.second;

	ans = 0;
	for (int t = 1; t <= k; t++) {
		if (isAllExit()) break;
		moveAllRunner();
		//print();
		rotateGrid();
		//print();
	}

	// 모든 참가자들의 이동 거리 합과 출구 좌표 출력
	cout << ans << "\n";
	cout << exit_pos.first << " " << exit_pos.second << "\n";
	return 0;
}