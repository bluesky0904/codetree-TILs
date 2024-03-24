#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define MAX_M 30
#define DIR_NUM 4

int n, m, k;

struct player {
	int num, x, y, d, s, g;
};

player players[MAX_M];
int point[MAX_M];
vector<int> gun[MAX_N][MAX_N];
int recent_num[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

void InitRecentNum() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			recent_num[i][j] = -1;
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

tuple<int, int, int> GetNextPos(int x, int y, int d) {
	int nx = x + dx[d], ny = y + dy[d];
	if (!InRange(nx, ny)) {
		int nd = (d + 2) % 4;
		nx = x + dx[nd];
		ny = y + dy[nd];
		return make_tuple(nx, ny, nd);
	}
	return make_tuple(nx, ny, d);
}

void LoserMove(player& loser) {
	if (loser.g) {
		gun[loser.x][loser.y].push_back(loser.g);
		loser.g = 0;
	}

	int nx = loser.x + dx[loser.d], ny = loser.y + dy[loser.d];
	if (!InRange(nx, ny) || recent_num[nx][ny] != -1) {
		for (int i = 1; i <= 3; i++) {
			int nd = (loser.d + i) % 4;
			nx = loser.x + dx[nd], ny = loser.y + dy[nd];
			if (recent_num[nx][ny] == -1) {
				loser.x = nx;
				loser.y = ny;
				loser.d = nd;
				recent_num[nx][ny] = loser.num;
				if ((int)gun[nx][ny].size()) {
					sort(gun[nx][ny].begin(), gun[nx][ny].end());
					loser.g = gun[nx][ny].back();
					gun[nx][ny].pop_back();
				}
			}
		}
	}
	else {
		loser.x = nx;
		loser.y = ny;
		recent_num[nx][ny] = loser.num;
		if ((int)gun[nx][ny].size()) {
			sort(gun[nx][ny].begin(), gun[nx][ny].end());
			loser.g = gun[nx][ny].back();
			gun[nx][ny].pop_back();
		}
	}
}

void WinnerMove(player& winner) {
	int x = winner.x;
	int y = winner.y;
	int num = winner.num;
	int g = winner.g;
	recent_num[x][y] = num;
	if ((int)gun[x][y].size()) {
		gun[x][y].push_back(g);
		sort(gun[x][y].begin(), gun[x][y].end());
		winner.g = gun[x][y].back();
		gun[x][y].pop_back();
	}
}

void Collide(player &p1, player &p2) {
	player* winner, * loser;
	if (p1.s + p1.g != p2.s + p2.g) {
		if (p1.s + p1.g > p2.s + p2.g) {
			winner = &p1;
			loser = &p2;
		}
		else {
			winner = &p2;
			loser = &p1;
		}
	}
	else {
		if (p1.s > p2.s) {
			winner = &p1;
			loser = &p2;
		}
		else {
			winner = &p2;
			loser = &p1;
		}
	}
	point[winner->num] += (winner->s + winner->g) - (loser->s + loser->g);
	LoserMove(*loser);
	WinnerMove(*winner);
}

void MoveAll() {
	for (int i = 0; i < m; i++) {
		int x = players[i].x;
		int	y = players[i].y;
		int d = players[i].d;
		int nx, ny, nd;
		tie(nx, ny, nd) = GetNextPos(x, y, d);
		players[i].x = nx;
		players[i].y = ny;	
		players[i].d = nd;
		recent_num[x][y] = -1;
		if (recent_num[nx][ny] == -1) {
			recent_num[nx][ny] = i;
			if ((int)gun[nx][ny].size()) {
				if (players[i].g) {
					gun[nx][ny].push_back(players[i].g);
					sort(gun[nx][ny].begin(), gun[nx][ny].end());
					players[i].g = gun[nx][ny].back();
					gun[nx][ny].pop_back();
				}
				else {
					sort(gun[nx][ny].begin(), gun[nx][ny].end());
					players[i].g = gun[nx][ny].back();
					gun[nx][ny].pop_back();
				}
			}
		}
		else {
			Collide(players[i], players[recent_num[nx][ny]]);
		}
	}
}

int main() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int info;
			cin >> info;
			if (info) gun[i][j].push_back(info);
		}
	}

	InitRecentNum();
	for (int i = 0; i < m; i++) {
		int x, y, d, s;
		cin >> x >> y >> d >> s;
		players[i].num = i;
		players[i].x = x - 1;
		players[i].y = y - 1;
		recent_num[x - 1][y - 1] = i;
		players[i].d = d;
		players[i].s = s;
		players[i].g = 0;	
	}

	while (k--) {
		MoveAll();
	}

	for (int i = 0; i < m; i++) {
		cout << point[i] << " ";
	}
	cout << "\n";
	return 0;
}