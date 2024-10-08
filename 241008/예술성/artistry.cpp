#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 29
#define DIR_NUM 4

struct Group {
	int start_x;
	int start_y;
	int num;
	int cnt;
};

vector<Group> groups;

int n;
int drawing[MAX_N][MAX_N];
int next_drawing[MAX_N][MAX_N];
int group_grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int ans = 0;

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int CheckEncounter(int g1, int g2) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}

	queue<pair<int, int>> q;
	q.push({ groups[g1].start_x , groups[g1].start_y });
	visited[groups[g1].start_x][groups[g1].start_y] = true;

	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second; q.pop();

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && (group_grid[nx][ny] == g2)) cnt++;
		}

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && group_grid[nx][ny] == g1) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}

	return cnt;
}

int GetScore() {
	int score = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			group_grid[i][j] = -1;
			visited[i][j] = false;
		}
	}

	int group_idx = 0;
	groups.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j]) continue;
			Group group;
			group.start_x = i;
			group.start_y = j;

			int num = drawing[i][j];
			group.num = num;

			int cnt = 0;
			queue<pair<int, int>> q;
			q.push({ i, j });
			visited[i][j] = true;
			group_grid[i][j] = group_idx;
			cnt++;

			while (!q.empty()) {
				int cx = q.front().first, cy = q.front().second; q.pop();

				for (int dir = 0; dir < DIR_NUM; dir++) {
					int nx = cx + dx[dir], ny = cy + dy[dir];
					if (InRange(nx, ny) && !visited[nx][ny] && drawing[nx][ny] == num) {
						q.push({ nx, ny });
						visited[nx][ny] = true;
						group_grid[nx][ny] = group_idx;
						cnt++;
					}
				}
			}

			group.cnt = cnt;
			groups.push_back(group);
			group_idx++;
		}
	}

	for (int i = 0; i < (int)groups.size(); i++) {
		for (int j = i + 1; j < (int)groups.size(); j++) {
			int encounter_cnt = CheckEncounter(i, j);
			if (encounter_cnt == 0) continue;
			score += ((groups[i].cnt + groups[j].cnt) * groups[i].num * groups[j].num * encounter_cnt);
		}
	}
	return score;
}

void Rotate() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_drawing[i][j] = 0;
		}
	}

	int cx = n / 2, cy = n / 2;
	next_drawing[cx][cy] = drawing[cx][cy];

	for (int dir = 0; dir < DIR_NUM; dir++) {
		for (int dist = 1; dist <= n / 2; dist++) {
			int nx = cx + dx[dir] * dist, ny = cy + dy[dir] * dist;
			next_drawing[n - ny - 1][nx] = drawing[nx][ny];
		}
	}

	for (int center_x = 0; center_x < n; center_x += (n / 2 + 1)) {
		for (int center_y = 0; center_y < n; center_y += (n / 2 + 1)) {
			for (int i = center_x; i < center_x + n / 2; i++) {
				for (int j = center_y; j < center_y + n / 2; j++) {
					int sx = i, sy = j;
					int ox = i - center_x, oy = j - center_y;
					int rx = oy, ry = n / 2 - ox - 1;
					next_drawing[rx + center_x][ry + center_y] = drawing[sx][sy];
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			drawing[i][j] = next_drawing[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> drawing[i][j];
		}
	}

	ans += GetScore();
	for (int i = 0; i < 3; i++) {
		Rotate();
		ans += GetScore();
	}

	cout << ans << "\n";
	return 0;
}