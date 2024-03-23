#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define MAX_M 30
#define DIR_NUM 4

int n, m, k;

vector<int> grid[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

struct player {
	int num, x, y, d, s, g, p;
};

player players[MAX_M];
int recent_num[MAX_N][MAX_N];

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
	int nx = x + dx[d];
	int ny = y + dy[d];
	if (!InRange(nx, ny)) {
		nx = x + dx[(d + 2) % 4];
		ny = y + dy[(d + 2) % 4];
		return make_tuple(nx, ny, (d + 2) % 4);
	}
	return make_tuple(nx, ny, d);
}

void LoserRule(player& loser) {
	grid[loser.x][loser.y].push_back(loser.g);
	loser.g = 0;
	int nx = loser.x + dx[loser.d], ny = loser.y + dy[loser.d];
	if (!InRange(nx, ny) || recent_num[nx][ny] != -1) {
		for (int i = 1; i <= 3; i++) {
			nx = loser.x + dx[(loser.d + i) % 4];
			ny = loser.y + dy[(loser.d + i) % 4];
			if (recent_num[nx][ny] == -1) {
				loser.x = nx;
				loser.y = ny;
				loser.d = (loser.d + i) % 4;
				if (grid[nx][ny].size() != 0) {
					sort(grid[nx][ny].begin(), grid[nx][ny].end());
					loser.g = grid[nx][ny].back();
					grid[nx][ny].pop_back();
				}
				recent_num[nx][ny] = loser.num;
				break;
			}
		}
	}
	else {
		loser.x = nx;
		loser.y = ny;
		recent_num[nx][ny] = loser.num;
		if (grid[nx][ny].size() != 0) {
			sort(grid[nx][ny].begin(), grid[nx][ny].end());
			loser.g = grid[nx][ny].back();
			grid[nx][ny].pop_back();
		}
	}
}

void WinnerRule(player& winner) {
	int x = winner.x , y = winner.y;
	sort(grid[x][y].begin(), grid[x][y].end());
	if ((int)grid[x][y].size() != 0) {
		if (winner.g < grid[x][y].back()) {
			int tmp = winner.g;
			winner.g = grid[x][y].back();
			grid[x][y].back() = tmp;
		}
	}
}

void Collide(player& p1, player& p2) {
	player* winner, *loser;
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
	winner->p += ((winner->s + winner->g) - (loser->s + loser->g));
	recent_num[winner->x][winner->y] = winner->num;
	
	LoserRule(*loser);
	WinnerRule(*winner);
}

void Print() {
	cout << "player info\n";
	for (int i = 0; i < m; i++) {
		int num = players[i].num;
		int x = players[i].x;
		int y = players[i].y;
		int d = players[i].d;
		int g = players[i].g;
		int p = players[i].p;
		cout << num << " : " << x << " " << y << " " << d << " " << g << " " << p << "\n";
	}
	cout << "--------------------\n";
}

void MoveAll() {
	for (int i = 0; i < m; i++) {
		int x, y, d;
		x = players[i].x;
		y = players[i].y;	
		d = players[i].d;	
		recent_num[x][y] = -1;
		int nx, ny, ndir;
		tie(nx, ny, ndir) = GetNextPos(x, y, d);
		players[i].x = nx;
		players[i].y = ny;	
		players[i].d = ndir;
		if (recent_num[nx][ny] == -1) {
			recent_num[nx][ny] = i;
			sort(grid[nx][ny].begin(), grid[nx][ny].end());
			if ((int)grid[nx][ny].size() != 0) {
				if (players[i].g == 0) {
					players[i].g = grid[nx][ny].back();
					grid[nx][ny].pop_back();
				}
				else {
					if (players[i].g >= grid[nx][ny].back()) continue;
					else {
						int tmp = players[i].g;
						players[i].g = grid[nx][ny].back();
						grid[nx][ny].back() = tmp;
					}
				}
			}
		}
		else {
			Collide(players[i], players[recent_num[nx][ny]]);
		}
		//Print();
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int gun;
			cin >> gun;
			if(gun) grid[i][j].push_back(gun);
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
		players[i].p = 0;
	}

	
	while (k--) {
		MoveAll();
	}

	for (int i = 0; i < m; i++) {
		cout << players[i].p << " ";
	}
	cout << "\n";
	return 0;
}