#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n, m, k, c;
int grid[MAX_N][MAX_N]; // 나무, 벽
int next_grid[MAX_N][MAX_N];
int plant_killer[MAX_N][MAX_N]; // 제초제

int ans;

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

int dx_d[DIR_NUM] = {-1,1,1,-1};
int dy_d[DIR_NUM] = {1,1,-1,-1};

bool inRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

void grow() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			next_grid[i][j] = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0) continue;
			if (grid[i][j] == -1) {
				next_grid[i][j] = -1;
				continue;
			}

			int cnt = 0;
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = i + dx[dir], ny = j + dy[dir];
				if (inRange(nx, ny) && grid[nx][ny] > 0) cnt++;
			}

			next_grid[i][j] = grid[i][j] + cnt;
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = next_grid[i][j];
}

void reproduce(int time) {
	

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0) continue;
			if (grid[i][j] == -1) {
				next_grid[i][j] = -1;
				continue;
			}

			int cnt = 0;
			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = i + dx[dir], ny = j + dy[dir];
				if (inRange(nx, ny) && grid[nx][ny] == 0 && plant_killer[nx][ny] <= time) cnt++;
			}

			if (cnt != 0) {
				int reproduce_amount = grid[i][j] / cnt;

				next_grid[i][j] = grid[i][j];
				for (int dir = 0; dir < DIR_NUM; dir++) {
					int nx = i + dx[dir], ny = j + dy[dir];
					if (inRange(nx, ny) && grid[nx][ny] == 0 && plant_killer[nx][ny] <= time)
						next_grid[nx][ny] += reproduce_amount;
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = next_grid[i][j];
}

int getRemovedCnt(int x, int y) {
	int cnt = grid[x][y]; // 초기화!
	for (int dir = 0; dir < DIR_NUM; dir++) {
		for (int dist = 1; dist <= k; dist++) {
			int nx = x + dx_d[dir] * dist, ny = y + dy_d[dir] * dist;
			if (inRange(nx, ny) && grid[nx][ny] > 0) {
				cnt += grid[nx][ny];
			}
			else break;
		}
	}

	//cout << cnt << "\n";
	return cnt;
}

void doKill(int x, int y, int time) {
	grid[x][y] = 0;
	plant_killer[x][y] = time + c + 1;

	for (int dir = 0; dir < DIR_NUM; dir++) {
		for (int dist = 1; dist <= k; dist++) {
			int nx = x + dx_d[dir] * dist, ny = y + dy_d[dir] * dist;
			if (inRange(nx, ny) && grid[nx][ny] > 0) {
				grid[nx][ny] = 0;
				plant_killer[nx][ny] = time + c + 1;
			}
			else {
				if (inRange(nx, ny)) {
					plant_killer[nx][ny] = time + c + 1;
					break;
				}
			}
		}
	}
}

void killPlant(int time) {
	int max_cnt = -1, max_x, max_y;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0 || grid[i][j] == -1) continue; // 꼭 모든 칸을 순회할 필요 없음
			int cnt = getRemovedCnt(i, j);
			if (max_cnt < cnt) {
				max_cnt = cnt;
				max_x = i;
				max_y = j;
			}
		}
	}

	if (max_cnt != -1) {
		doKill(max_x, max_y, time);
		ans += max_cnt;
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
	cout << "PLANT_KILLER" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << plant_killer[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m >> k >> c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			plant_killer[i][j] = 0;
		}
	}

	//print();
	for (int t = 1; t <= m; t++) {
		//cout << t << "\n";
		//cout << t << " GROW\n";
		grow();
		//print();

		//cout << t << " REPRODUCE\n";
		reproduce(t);
		//print();

		//cout << t << " KILLPLANT\n";
		killPlant(t);
		//print();
	}

	cout << ans << "\n";
	return 0;
}