#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define MAX_M 30
#define DIR_NUM 4

int n, m, k;
vector<int> grid[MAX_N + 1][MAX_N + 1];
int collide_idx;

struct Player{
	int num, x, y, d, s, g;
};

Player players[MAX_M + 1];
int point[MAX_M + 1];

int dx[DIR_NUM] = { -1, 0, 1, 0 };
int dy[DIR_NUM] = { 0, 1, 0, -1 };

bool InRange(int x, int y) {
	return 1<= x && x <= n && 1 <= y && y <= n;
}

tuple<int, int, int> GetNextPos(int x, int y, int d) {
	int nx = x + dx[d], ny = y + dy[d], nd = d;
	if (InRange(nx, ny)) {
		return make_tuple(nx, ny, nd);
	}
	else {
		nd = (d + 2) % 4;
		nx = x + dx[nd], ny = y + dy[nd];
		return make_tuple(nx, ny, nd);
	}
}

bool IsPlayer(int idx, int x, int y) {
	for (int i = 1; i <= m; i++) {
		if (i == idx) continue;
		if (players[i].x == x && players[i].y == y) {
			collide_idx = i;
			return true;
		}
	}
	return false;
}

void LoserGo(int loser) {
	int x = players[loser].x, y = players[loser].y, d = players[loser].d;
	grid[x][y].push_back(players[loser].g);
	players[loser].g = 0;
	int nx = x + dx[d], ny = y + dy[d], nd = d;
	if (InRange(nx, ny) && !IsPlayer(loser, nx, ny)) {
		players[loser].x = nx; players[loser].y = ny; players[loser].d = nd;
		if (!grid[nx][ny].empty()) {
			sort(grid[nx][ny].begin(), grid[nx][ny].end());
			players[loser].g = grid[nx][ny].back();
			grid[nx][ny].pop_back();
		}
	}
	else {
		for (int dir = 1; dir <= 3; dir++) {
			nx = x + dx[(d + dir) % 4], ny = y + dy[(d + dir) % 4], nd = (d + dir) % 4;
			if (InRange(nx, ny) && !IsPlayer(loser, nx, ny)) {
				players[loser].x = nx; players[loser].y = ny; players[loser].d = nd;
				if (!grid[nx][ny].empty()) {
					sort(grid[nx][ny].begin(), grid[nx][ny].end());
					players[loser].g = grid[nx][ny].back();
					grid[nx][ny].pop_back();
				}
				break;
			}
		}
	}
}

void WinnerGo(int winner) {
	int x = players[winner].x, y = players[winner].y, d = players[winner].d;
	if (!grid[x][y].empty()) {
		if (players[winner].g) {
			grid[x][y].push_back(players[winner].g);
			sort(grid[x][y].begin(), grid[x][y].end());
			players[winner].g = grid[x][y].back();
			grid[x][y].pop_back();
		}
		else {
			sort(grid[x][y].begin(), grid[x][y].end());
			players[winner].g = grid[x][y].back();
			grid[x][y].pop_back();
		}
	}
}

void Collide(int p1, int p2) {
	int winner, loser;
	if (players[p1].s + players[p1].g > players[p2].s + players[p2].g) {
		winner = p1; loser = p2;
	}
	else if (players[p1].s + players[p1].g == players[p2].s + players[p2].g) {
		if(players[p1].s > players[p2].s){
			winner = p1; loser = p2;
		}
		else {
			winner = p2; loser = p1;
		}
	}
	else {
		winner = p2; loser = p1;
	}
	
	int point_diff = (players[winner].s + players[winner].g) - (players[loser].s + players[loser].g);
	point[winner] += point_diff;
	LoserGo(loser);
	WinnerGo(winner);
}

void Print() {
	cout << "==================================================================\n";

	cout << "Players\n";
	for (int i = 1; i <= m; i++) {
		cout << players[i].x << ' ' << players[i].y << ' ' << players[i].d << ' ' << players[i].g << '\n';
	}
	cout << "Points\n";
	for (int i = 1; i <= m; i++) {
		cout << point[i] << ' ';
	}
	cout << '\n';
}

void MoveAll() {
	for (int i = 1; i <= m; i++) {
		int nx, ny, nd;
		tie(nx, ny, nd) = GetNextPos(players[i].x, players[i].y, players[i].d);
		players[i].x = nx; players[i].y = ny; players[i].d = nd;
		// 플레이어가 없는 경우
		if (!IsPlayer(i, nx, ny)) {
			if (!grid[nx][ny].empty()) {
				if (players[i].g) {
					grid[nx][ny].push_back(players[i].g);
					sort(grid[nx][ny].begin(), grid[nx][ny].end());
					players[i].g = grid[nx][ny].back();
					grid[nx][ny].pop_back();
				}
				else {
					sort(grid[nx][ny].begin(), grid[nx][ny].end());
					players[i].g = grid[nx][ny].back();
					grid[nx][ny].pop_back();
				}
			}
		}
		// 플레이어가 있는 경우
		else {
			Collide(i, collide_idx);
		}
		//Print();
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int x; cin >> x;
			grid[i][j].push_back(x);
		}
	}

	for (int i = 1; i <= m; i++) {
		Player p;
		int x, y, d, s;	cin >> x >> y >> d >> s;
		p.num = i;  p.x = x; p.y = y; p.d = d; p.s = s; p.g = 0;
		players[i] = p;
	}

	while (k--) {
		MoveAll();
	}

	for (int i = 1; i <= m; i++) {
		cout << point[i] << ' ';
	}
	return 0;
}