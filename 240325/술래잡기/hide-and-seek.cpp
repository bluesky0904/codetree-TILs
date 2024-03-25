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
bool visited[MAX_N * MAX_N];

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

void InitVisited() {
	for (int i = 0; i < n * n; i++) {
		visited[i] = false;
	}
}

/*
void CatchRunner() {
	int cx, cy, cd;
	tie(cx, cy, cd) = catcher;
	int cnt = 0;
	next_runner.clear();
	for (int i = 0; i < (int)runner.size(); i++) {
		bool is_possible = true;
		int x, y;
		tie(x, y, ignore) = runner[i];
		for (int dis = 0; dis < 3; dis++) {
			if (dis != 0) cx += dx[cd], cy += dy[cd];
			if (!InRange(cx, cy)) continue;
			if (tree[cx][cy] == 1) continue;
			if (x == cx && y == cy) {
				is_possible = false;
				break;
			}
		}
		if(is_possible) next_runner.push_back(runner[i]);
		else cnt++;
	}
	runner = next_runner;
	ans += turn * cnt;
}
*/

void CatchRunner() {
	int cx, cy, cd;
	tie(cx, cy, cd) = catcher; // 술래의 현재 위치와 방향
	int cnt = 0; // 잡힌 도망자의 수
	vector<tuple<int, int, int>> temp_next_runner; // 임시로 다음 턴에 남아있을 도망자들을 저장할 벡터

	for (int i = 0; i < runner.size(); ++i) {
		bool caught = false; // 현재 도망자가 잡혔는지 여부
		int rx, ry;
		tie(rx, ry, ignore) = runner[i]; // 도망자의 위치

		for (int dis = 0; dis < 3 && !caught; ++dis) {
			int nx = cx + dx[cd] * dis; // 검사할 위치
			int ny = cy + dy[cd] * dis;

			if (!InRange(nx, ny) || tree[nx][ny] == 1) {
				// 범위를 벗어나거나 나무가 있는 경우, 이 위치에서 도망자를 잡을 수 없음
				continue;
			}

			if (rx == nx && ry == ny) {
				caught = true; // 도망자를 잡음
				cnt++; // 잡힌 도망자 수 증가
			}
		}

		if (!caught) {
			// 현재 도망자가 잡히지 않았다면, 다음 턴의 도망자 목록에 추가
			temp_next_runner.push_back(runner[i]);
		}
	}

	runner = temp_next_runner; // 다음 턴의 도망자 목록으로 업데이트
	ans += turn * cnt; // 점수 업데이트
}


bool MoveCatcherClock() {
	int cx, cy, cd;
	tie(cx, cy, cd) = catcher;
	for (int dist = 1; dist <= n - 1; dist++) {
		for (int cnt = 0; cnt < 2; cnt++) {
			for (int i = 0; i < dist; i++) {
				turn++;
				//Print();
				MoveAllRunner();
				cx += dx[cd], cy += dy[cd];
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
	for (int i = 0; i < n - 1; i++) {
		turn++;
		//Print();
		MoveAllRunner();
		cx += dx[cd], cy += dy[cd];
		if (cx == 0 && cy == 0) cd = 2;
		catcher = make_tuple(cx, cy, cd);
		CatchRunner();
		if (turn == k) {
			finish = true;
			return false;
		}
	}
	return true;
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