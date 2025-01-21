#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define MAX_M 30
#define DIR_NUM 4

int n, m, k;
vector<int> grid[MAX_N + 1][MAX_N + 1]; // 총 위치
pair<int, int> p_pos[MAX_N + 1]; // 플레이어 위치
int p_dir[MAX_M + 1]; // 플레이어 방향
int p_power[MAX_M + 1]; // 플레이어 초기 능력치
int g_power[MAX_M + 1]; // 플레이어 총 공격력
int p_point[MAX_M + 1]; // 플레이어 포인트

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool inRange(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

void movePlayer(int idx) {
	int cx = p_pos[idx].first, cy = p_pos[idx].second, dir = p_dir[idx];

	int nx = cx + dx[dir], ny = cy + dy[dir];
	if (!inRange(nx, ny)) {
		dir = (dir + 2) % DIR_NUM;
		nx = cx + dx[dir], ny = cy + dy[dir];
		p_pos[idx] = { nx, ny };
		p_dir[idx] = dir;
		return;
	}

	p_pos[idx] = { nx, ny };
	return;
}

bool isCollide(int idx) {
	for (int i = 1; i <= m; i++) {
		if (i == idx) continue;
		if (p_pos[idx] == p_pos[i]) return true;
	}
	return false;
}

bool isAny(int x, int y) {
	for (int i = 1; i <= m; i++) {
		if (p_pos[i] == make_pair(x, y)) return true;
	}
	return false;
}

void Collide(int idx1, int idx2) {
	int winner, loser;
	if (p_power[idx1] + g_power[idx1] > p_power[idx2] + g_power[idx2]) {
		winner = idx1;
		loser = idx2;
	}
	else if (p_power[idx1] + g_power[idx1] < p_power[idx2] + g_power[idx2]) {
		winner = idx2;
		loser = idx1;
	}
	else {
		if (p_power[idx1] > p_power[idx2]) {
			winner = idx1;
			loser = idx2;
		}
		else {
			winner = idx2;
			loser = idx1;
		}
	}

	p_point[winner] += ((p_power[winner] + g_power[winner]) - (p_power[loser] + g_power[loser]));

	// 진 플레이어의 행동
	int cx = p_pos[loser].first, cy = p_pos[loser].second, dir = p_dir[loser];
	if (g_power[loser] != 0) {
		grid[cx][cy].push_back(g_power[loser]);
		g_power[loser] = 0;
	}

	for (int cnt = 0; cnt < DIR_NUM; cnt++) {
		int new_dir = (dir + cnt) % DIR_NUM;
		int nx = cx + dx[new_dir], ny = cy + dy[new_dir];
		if (inRange(nx, ny) && !isAny(nx, ny)) {

			p_pos[loser] = { nx, ny };
			p_dir[loser] = new_dir;

			if (!grid[nx][ny].empty()) {
				sort(grid[nx][ny].begin(), grid[nx][ny].end());
				g_power[loser] = grid[nx][ny].back();
				grid[nx][ny].pop_back();
			}
			break;
		}
	}

	// 이긴 플레이어의 행동
	cx = p_pos[winner].first, cy = p_pos[winner].second;

	if (!grid[cx][cy].empty()) {
		// 이긴 플레이어 총 안 넣냐?
		grid[cx][cy].push_back(g_power[winner]);
		sort(grid[cx][cy].begin(), grid[cx][cy].end());
		g_power[winner] = grid[cx][cy].back();
		grid[cx][cy].pop_back();
	}
}

void moveAllPlayer() {
	for (int i = 1; i <= m; i++) {
		movePlayer(i);

		if (isCollide(i)) {
			int opponent_idx;
			for (int j = 1; j <= m; j++) {
				if (j == i) continue;
				if (p_pos[i] == p_pos[j]) {
					opponent_idx = j;
					break;
				}
			}

			//cout << "Collide! " << i << " " << opponent_idx << "\n";
			Collide(i, opponent_idx);

		}
		else {
			int cx = p_pos[i].first, cy = p_pos[i].second;

			if (!grid[cx][cy].empty()) {
				if (g_power[i] != 0) grid[cx][cy].push_back(g_power[i]);
				sort(grid[cx][cy].begin(), grid[cx][cy].end());
				g_power[i] = grid[cx][cy].back();
				grid[cx][cy].pop_back();
			}
		}
	}
}

void print() {
	cout << "플레이어들의 위치\n";
	for (int i = 1; i <= m; i++) {
		cout << "#" << i << " : " << p_pos[i].first << " " << p_pos[i].second << "\n";
	}
	cout << "플레이어들의 방향\n";
	for (int i = 1; i <= m; i++) {
		cout << "#" << i << " : " << p_dir[i] << "\n";
	}
	cout << "플레이어들의 파워\n";
	for (int i = 1; i <= m; i++) {
		cout << "#" << i << " : " << p_power[i] << "\n";
	}
	cout << "플레이어들의 총\n";
	for (int i = 1; i <= m; i++) {
		cout << "#" << i << " : " << g_power[i] << "\n";
	}
	cout << "플레이어들의 점수\n";
	for (int i = 1; i <= m; i++) {
		cout << "#" << i << " : " << p_point[i] << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int g_power; cin >> g_power;
			if (g_power == 0) continue;
			grid[i][j].push_back(g_power);
		}
	}

	for (int i = 1; i <= m; i++) {
		int x, y, d, s; cin >> x >> y >> d >> s;
		p_pos[i] = { x, y };
		p_dir[i] = d;
		p_power[i] = s;
		g_power[i] = 0;
		p_point[i] = 0;
	}

	//print();
	for (int t = 1; t <= k; t++) {
		//cout << "****** 라운드 " << t << " ******" << "\n";
		moveAllPlayer();
		//print();
	}

	for (int i = 1; i <= m; i++) cout << p_point[i] << " ";
	cout << "\n";
	return 0;
}