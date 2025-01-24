/*
격자 : n * n

술래 : 처음 정중앙에 서있음

도망자 : m명. 처음 지정된 곳에 서있음
좌우로만 움직이는 유형과 상하로만 움직이는 유형 2가지가 있음
좌우로 움직이는 사람은 항상 오른쪽을 보고 시작, 상하로 움직이는 사람은 항상 아래쪽을 보고 시작
생존 여부

나무 : h개
나무가 도망자와 초기에 겹쳐져 주어질 수 있음

아래 과정을 k번 반복
1. m명의 도망자가 먼저 동시에 움직임
현재 술래와의 거리가 3이하인 도망자만 움직임. 두 사람 간의 거리는 |x1-x2| + |y1-y2|

현재 바라보고 있는 방향으로 1칸 움직인다 했을 때 격자를 벗어나지 않는 경우
움직이려는 칸에 술래가 있는 경우라면 움직이지 않음
움직이려는 칸에 술래가 있지 않다면 해당 칸으로 이동. 해당 칸에 나무가 있어도 괜찮음

현재 바라보고 있는 방향으로 1칸 움직인다 했을 때 격자를 벗어나는 경우
먼저 방향을 반대로 틀어줌. 이후 바라보고 있는 방향으로 1칸 움직인다 했을 때 해당 위치에 술래가 없다면 1칸 앞으로 이동

2. 술래 움직임
술래는 처음 위 방향으로 시작하여 달팽이 모양으로 움직임
만약 끝에 도달하게 되면 다시 거꾸로 중심으로 이동하고, 다시 중심에 오게 되면 처음처럼 위 방향으로 시작하여 시계방향으로 도는 것을 k턴에 걸쳐 반복하게 됨
술래는 1번의 턴 동안 정확히 한 칸 해당하는 방향으로 이동
이동 후의 위치가 만약 이동방향이 틀어지는 지점이라면, 방향을 바로 틀어줌
만약 이동을 통해 양끝에 해당하는 위치인 (1행, 1열) 혹은 정중앙에 도달하게 된다면 이 경우 역시 방향을 바로 틀어줘야 함에 유의

이동 직후 술래는 턴을 넘기기 전에 시야 내에 있는 도망자를 잡게 됨.
술래의 시야는 현재 바라보고 있는 방향을 기준으로 현재 칸을 포함하여 총 3칸
격자 크기에 상관없이 술래의 시야는 항상 3칸
하지만 만약 나무가 놓여 있는 칸이라면, 해당 칸에 있는 도망자는 나무에 가려져 보이지 않게 됨.
따라서 <Figure 8>의 경우에서는 (2행, 5열)에 있는 도망자만 잡히게 됨

잡힌 도망자는 사라지게 되고, 술래는 현재 턴을 t번째 턴이라고 했을 때 t x (현재 턴에서 잡힌 도망자의 수) 만큼의 점수를 얻게 됨

k번에 걸쳐 술래잡기를 진행하는 동안 술래가 총 얻게된 점수를 출력
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
using namespace std;

#define MAX_N 99
#define DIR_NUM 4

int n, m, h, k;
int catcher_x, catcher_y, catcher_d;
vector<int> grid[MAX_N + 1][MAX_N + 1]; // runner들의 위치 관리
vector<int> next_grid[MAX_N + 1][MAX_N + 1]; // runner들의 위치 관리
bool tree[MAX_N + 1][MAX_N];

bool is_clock;
int clock_dir[MAX_N + 1][MAX_N + 1];
int counter_clock_dir[MAX_N + 1][MAX_N + 1];

int ans;

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

void print() {
	cout << "CATCHER_POS : " << catcher_x << " " << catcher_y << "\n";
	cout << "CATCHER_DIR : " << catcher_d << "\n";
	cout << "GRID" << "\n";
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			cout << "{ ";
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				cout << grid[x][y][i] << " ";
			}
			cout << " } ";
		}
		cout << "\n";
	}
	cout << "TREE" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (tree[i][j]) cout << 1 << " ";
			else cout << 0 << " ";
		}
		cout << "\n";
	}
}

void setCatcherDir() {
	int cx = (n + 1) / 2, cy = (n + 1) / 2;
	int dir = 0, dist = 1;

	while (!(cx == 1 && cy == 1)) {
		for (int cnt = 1; cnt <= 2; cnt++) {
			for (int i = 1; i <= dist; i++) {
				clock_dir[cx][cy] = dir;
				cx += dx[dir], cy += dy[dir];

				if (cx == 1 && cy == 1) return;
			}
			dir = (dir + 1) % DIR_NUM;
		}
		dist++;
	}
}
/*
x 1 1 1 2
0 0 1 2 2
0 0 0 2 2
0 0 3 3 2
0 3 3 3 3
*/

void setCounterCatcherDir() {
	int cx = n, cy = 1;
	int dir = 1, dist = n - 1;

	for (int i = 1; i <= n - 1; i++) {
		counter_clock_dir[i][1] = 2;
	}

	while (!(cx == (n + 1) / 2 && cy == (n + 1) / 2)) {
		for (int cnt = 1; cnt <= 2; cnt++) {
			for (int i = 1; i <= dist; i++) {
				counter_clock_dir[cx][cy] = dir;
				cx += dx[dir], cy += dy[dir];

				if (cx == (n + 1) / 2 && cy == (n + 1) / 2) return;
			}
			dir = (dir + 3) % DIR_NUM;
		}
		dist--;
	}
}
/*
2 2 3 3 3
2 2 2 3 0
2 2 x 0 0
2 1 1 0 0
1 1 1 1 0
*/

bool inRange(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

int getDist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

tuple<int, int, int> getNextPos(int x, int y, int d) {
	int nx = x + dx[d], ny = y + dy[d], nd = d;
	if (inRange(nx, ny)) {
		if (nx == catcher_x && ny == catcher_y) return make_tuple(x, y, nd);
		else return make_tuple(nx, ny, nd);
	}
	else {
		nd = (nd + 2) % DIR_NUM;
		nx = x + dx[nd], ny = y + dy[nd];
		if (nx == catcher_x && ny == catcher_y) return make_tuple(x, y, nd);
		else return make_tuple(nx, ny, nd);
	}
}

void moveRunner() {
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			next_grid[x][y].clear();
		}
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			if (getDist(x, y, catcher_x, catcher_y) > 3) {
				next_grid[x][y] = grid[x][y];
				continue;
			}

			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				int nx, ny, nd;
				tie(nx, ny, nd) = getNextPos(x, y, grid[x][y][i]);
				next_grid[nx][ny].push_back(nd);
			}
		}
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void moveCatcher() {
	if (is_clock) {
		catcher_x += dx[catcher_d], catcher_y += dy[catcher_d];
		catcher_d = clock_dir[catcher_x][catcher_y];
		if (catcher_x == 1 && catcher_y == 1) {
			is_clock = false;
			catcher_d = 2;
			return;
		}
	}
	else {
		catcher_x += dx[catcher_d], catcher_y += dy[catcher_d];
		catcher_d = counter_clock_dir[catcher_x][catcher_y];
		if (catcher_x == (n + 1) / 2 && catcher_y == (n + 1) / 2) {
			is_clock = true;
			catcher_d = 0;
			return;
		}
	}
}

/*
이동 직후 술래는 턴을 넘기기 전에 시야 내에 있는 도망자를 잡게 됨.
술래의 시야는 현재 바라보고 있는 방향을 기준으로 현재 칸을 포함하여 총 3칸
격자 크기에 상관없이 술래의 시야는 항상 3칸
하지만 만약 나무가 놓여 있는 칸이라면, 해당 칸에 있는 도망자는 나무에 가려져 보이지 않게 됨.
따라서 <Figure 8>의 경우에서는 (2행, 5열)에 있는 도망자만 잡히게 됨

잡힌 도망자는 사라지게 되고, 술래는 현재 턴을 t번째 턴이라고 했을 때 t x (현재 턴에서 잡힌 도망자의 수) 만큼의 점수를 얻게 됨
*/
void catchRunner(int turn) {
	int cnt = 0;
	int cx = catcher_x, cy = catcher_y, cd = catcher_d;
	for (int dist = 1; dist <= 3; dist++) {
		int nx = cx + dx[cd] * dist, ny = cy + dy[cd] * dist;
		if (inRange(nx, ny) && !tree[nx][ny]) {
			cnt += (int)grid[nx][ny].size();
			grid[nx][ny].clear();
		}
	}

	ans += cnt * turn;
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m >> h >> k;

	ans = 0;
	catcher_x = (n + 1) / 2, catcher_y = (n + 1) / 2, catcher_d = 0;;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			grid[i][j].clear();
			tree[i][j] = false;
		}
	}

	is_clock = true;
	setCatcherDir();
	setCounterCatcherDir();

	for (int i = 1; i <= m; i++) {
		int x, y, d; cin >> x >> y >> d;

		if (d == 1) {
			grid[x][y].push_back(1);
		}
		else if(d == 2) {
			grid[x][y].push_back(2);
		}
	}

	for (int i = 1; i <= h; i++) {
		int x, y; cin >> x >> y;
		tree[x][y] = true;
	}

	//print();
	for (int i = 1; i <= k; i++) {
		//cout << "MOVERUNNER" << "\n";
		moveRunner();
		//print();

		moveCatcher();
		//print();
		
		catchRunner(i);
		//print();
	}

	cout << ans << "\n";
	return 0;
}
