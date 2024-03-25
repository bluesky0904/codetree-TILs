#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 99
#define DIR_NUM 4

int n, m, h, k;
int turn = 0;
int ans = 0;
bool finish = false;

tuple<int, int, int> catcher;
vector<tuple<int, int, int>> runner;
vector<tuple<int, int, int>> next_runner;
int tree[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool MovePossible(tuple<int, int, int> runner) {
	int rx, ry;
	tie(rx, ry, ignore) = runner;
	int cx, cy;
	tie(cx, cy, ignore) = catcher;
	return abs(rx - cx) + abs(ry - cy) <= 3;
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Print() {
	cout << "Turn: " << turn << "\n";
	int x, y, d;
	tie(x, y, d) = catcher;
	cout << "Catcher: " << x << " " << y << " " << d << "\n";
	for (int i = 0; i < (int)runner.size(); i++) {
		int x, y, d;
		tie(x, y, d) = runner[i];
		cout << x << " " << y << " " << d << "\n";
	}
	cout << "--------------------------\n";
}

void MoveAllRunner() {
	for (int i = 0; i < (int)runner.size(); i++) {
		if (MovePossible(runner[i])) {
			int cat_x, cat_y;
			tie(cat_x, cat_y, ignore) = catcher;
			int cx, cy, cd;
			tie(cx, cy, cd) = runner[i];
			int nx = cx + dx[cd], ny = cy + dy[cd];
			if (InRange(nx, ny)) {
				if (nx == cat_x && ny == cat_y) {
					runner[i] =  make_tuple(cx, cy, cd);
				}
				else {
					runner[i] = make_tuple(nx, ny, cd);
				}
			}
			else {
				int nd = (cd + 2) % 4;
				int nx = cx + dx[nd], ny = cy + dy[nd];
				if (nx == cat_x && ny == cat_y) {
					runner[i] = make_tuple(cx, cy, nd);
				}
				else {
					runner[i] = make_tuple(nx, ny, nd);
				}
			}
		}
	}
}

void CatchRunner() {
	int cx, cy, cd;
	tie(cx, cy, cd) = catcher;
	int cnt = 0;
	for (int i = 0; i < 3; i++) {
		cx += dx[cd], cy += dy[cd];
		if (!InRange(cx, cy)) continue;
		if (tree[cx][cy] == 1) continue;
		for (int i = 0; i < (int)runner.size(); i++) {
			int x, y;
			tie(x, y, ignore) = runner[i];
			if (x == cx && y == cy) cnt++;
		}
	}
	ans += turn * cnt;
}

bool MoveCatcherClock() {
	int cx, cy, cd;
	tie(cx, cy, cd) = catcher;
	for (int dist = 1; dist <= n; dist++) {
		for (int cnt = 0; cnt < 2; cnt++) {
			for (int i = 0; i < dist; i++) {
				turn++;
				//Print();
				MoveAllRunner();
				cx += dx[cd], cy += dy[cd];
				if (cx == 0 && cy == 0) {
					cd = 2;
					catcher = make_tuple(cx, cy, cd);
					CatchRunner();
					return true;
				}
				if (i == dist - 1) cd = (cd + 1) % 4;
				catcher = make_tuple(cx, cy, cd);
				CatchRunner();
				if (turn == k) {
					finish = true;
					return false;
				}
			}
		}
	}
}

void MoveCatcherCounterClock() {
	int cx, cy, cd;
	tie(cx, cy, cd) = catcher;
	for (int i = 0; i < n - 1; i++) {
		turn++;
		//Print();
		MoveAllRunner();
		cx += dx[cd], cy += dy[cd];
		if (i == n - 2) cd = (cd + 3) % 4;
		catcher = make_tuple(cx, cy, cd);
		CatchRunner();
		if (turn == k) {
			finish = true;
			return;
		}
	}
	for (int dist = n-1; dist > 0; dist--) {
		for (int cnt = 0; cnt < 2; cnt++) {
			for (int i = 0; i < dist; i++) {
				turn++;
				//Print();
				MoveAllRunner();
				cx += dx[cd], cy += dy[cd];
				if (cx == n / 2 && cy == n / 2) {
					cd = 0;
					catcher = make_tuple(cx, cy, cd);
					CatchRunner();
					return;
				}
				if (i == dist - 1) cd = (cd + 3) % 4;
				catcher = make_tuple(cx, cy, cd);
				CatchRunner();
				if (turn == k) {
					finish = true;
					return;
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> h >> k;

	catcher = make_tuple(n / 2, n / 2, 0);

	for (int i = 0; i < m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		runner.push_back(make_tuple(x - 1, y - 1, d));
	}

	for (int i = 0; i < h; i++) {
		int x, y;
		cin >> x >> y;
		tree[x - 1][y - 1] = 1;
	}

	while (!finish) {
		if(MoveCatcherClock())MoveCatcherCounterClock();
	}

	cout << ans << "\n";
	return 0;
}