#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

#define MAX_NUM 10

const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};
const int dx2[9] = {-1,-1,-1,0,1,1,1,0,0};
const int dy2[9] = {-1,0,1,1,1,0,-1,-1,0};

int n, m, k;
int turn;

int board[MAX_NUM + 1][MAX_NUM + 1];
int rec[MAX_NUM + 1][MAX_NUM + 1];

bool visited[MAX_NUM + 1][MAX_NUM + 1];
int back_x[MAX_NUM + 1][MAX_NUM + 1], back_y[MAX_NUM + 1][MAX_NUM + 1];

bool is_active[MAX_NUM + 1][MAX_NUM + 1];

struct Turret {
	int x, y, r, p;
};

vector<Turret> live_turret;

bool cmp(Turret a, Turret b) {
	if (a.p != b.p) return a.p < b.p;
	if (a.r != b.r) return a.r > b.r;
	if (a.x + a.y != b.x + b.y) return a.x + a.y > b.x + b.y;
	return a.y > b.y;
}

void Init() {
	turn++;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			visited[i][j] = false;
			is_active[i][j] = false;
			// back_x[i][j] = 0, back_y[i][j] = 0; ??
		}
	}
}

void Awake() {
	sort(live_turret.begin(), live_turret.end(), cmp);
	Turret weak_turret = live_turret[0];
	int x = weak_turret.x;
	int y = weak_turret.y;
	board[x][y] += n + m;
	rec[x][y] = turn;
	weak_turret.p = board[x][y];
	weak_turret.r = rec[x][y];
	is_active[x][y] = true;

	live_turret[0] = weak_turret;
}

bool LaserAttack() {
	Turret weak_turret = live_turret[0];
	int sx = weak_turret.x;
	int sy = weak_turret.y;
	int pow = weak_turret.p;

	Turret strong_turret = live_turret[(int)live_turret.size() - 1];
	int ex = strong_turret.x;
	int ey = strong_turret.y;

	queue<pair<int, int>> q;
	q.push(make_pair(sx, sy));
	visited[sx][sy] = true;

	bool is_possible = false;

	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();

		if (cx == ex && cy == ey) {
			is_possible = true;
			break;
		}

		for (int dir = 0; dir < 4; dir++) {
			int nx = (cx + dx[dir] + n) % n;
			if (nx == 0) nx = n;
			int	ny = (cy + dy[dir] + m) % m;
			if (ny == 0) ny = m;

			if (visited[nx][ny] || board[nx][ny] == 0) continue;

			q.push(make_pair(nx, ny));
			visited[nx][ny] = true;
			back_x[nx][ny] = cx;
			back_y[nx][ny] = cy;
		}
	}

	if (is_possible) {
		board[ex][ey] -= pow;
		if (board[ex][ey] < 0) board[ex][ey] = 0;
		is_active[ex][ey] = true;

		// 15:48
		int cx = back_x[ex][ey];
		int cy = back_y[ex][ey];

		while (!(cx == sx && cy == sy)) {
			board[cx][cy] -= pow / 2;
			if (board[cx][cy] < 0) board[cx][cy] = 0;
			is_active[cx][cy] = true;

			int next_cx = back_x[cx][cy];
			int next_cy = back_y[cx][cy];

			cx = next_cx;
			cy = next_cy;
		}
	}

	return is_possible;
}

void BombAttack() {
	Turret weak_turret = live_turret[0];
	int sx = weak_turret.x;
	int sy = weak_turret.y;
	int pow = weak_turret.p;

	Turret strong_turret = live_turret[(int)live_turret.size() - 1];
	int ex = strong_turret.x;
	int ey = strong_turret.y;

	for (int dir = 0; dir < 9; dir++) {
		int nx = (ex + dx2[dir] + n) % n;
		if (nx == 0) nx = n;
		int ny = (ey + dy2[dir] + m) % m;
		if (ny == 0) ny = m;
		
		if (nx == sx && ny == sy) continue;

		if (nx == ex && ny == ey) {
			board[nx][ny] -= pow;
			if (board[nx][ny] < 0) board[nx][ny] = 0;
			is_active[nx][ny] = true;
		}
		else {
			board[nx][ny] -= pow / 2;
			if (board[nx][ny] < 0) board[nx][ny] = 0;
			is_active[nx][ny] = true;
		}
	}
}

void Reserve() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (is_active[i][j] || board[i][j] == 0) continue;
			board[i][j]++;
		}
	}
}

void Print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "-------------------------\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> board[i][j];
		}
	}

	while (k--) {
		live_turret.clear();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (board[i][j]) {
					Turret new_turret;
					new_turret.x = i;
					new_turret.y = j;
					new_turret.r = rec[i][j];
					new_turret.p = board[i][j];
					live_turret.push_back(new_turret);
				}
			}
		}
		Print();

		if (live_turret.size() <= 1) break;

		Init();

		Awake();

		bool is_possible = LaserAttack();
		if (!is_possible) BombAttack();
		Print();

		Reserve();
		Print();
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans = max(ans, board[i][j]);
		}
	}
	cout << ans << "\n";
	return 0;
}