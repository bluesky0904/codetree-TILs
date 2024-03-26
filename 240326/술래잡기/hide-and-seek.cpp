#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 99
#define DIR_NUM 4

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

int n, m, h, k;
int ans;
bool forward_facing = true;

pair<int, int> catcher;
vector<int> runner[MAX_N][MAX_N];
vector<int> next_runner[MAX_N][MAX_N];
bool tree[MAX_N][MAX_N];
int catcher_next_dir[MAX_N][MAX_N];
int catcher_rev_dir[MAX_N][MAX_N];

void InitializeCatcherPath() {
	int cur_x = n / 2, cur_y = n / 2;
	int move_dir = 0, move_num = 1;

	while (!(cur_x == 0 && cur_y == 0)) {
		for (int i = 0; i < move_num; i++) {
			catcher_next_dir[cur_x][cur_y] = move_dir;
			cur_x += dx[move_dir], cur_y += dy[move_dir];
			catcher_rev_dir[cur_x][cur_y] = (move_dir + 2) % 4;
			if (cur_x == 0 && cur_y == 0) break;
		}

		move_dir = (move_dir + 1) % 4;
		if (move_dir == 0 || move_dir == 2) move_num++;
	}
}

bool MovePossible(int x, int y) {
	return abs(catcher.first - x) + abs(catcher.second - y) <= 3;
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void MoveRunner(int x, int y, int move_dir) {
	int nx = x + dx[move_dir], ny = y + dy[move_dir];
	if (!InRange(nx, ny)) {
		move_dir = (move_dir + 2) % 4;
		nx = x + dx[move_dir], ny = y + dy[move_dir];
	}

	if(make_pair(nx, ny) != catcher) next_runner[nx][ny].push_back(move_dir);
	else next_runner[x][y].push_back(move_dir);
}

void MoveAllRunner() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_runner[x][y].clear();
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (MovePossible(x, y)) {
				for (int i = 0; i < (int)runner[x][y].size(); i++)
					MoveRunner(x, y, runner[x][y][i]);
			}
			else {
				for(int i = 0; i < (int)runner[x][y].size(); i++)
					next_runner[x][y].push_back(runner[x][y][i]);
			}
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			runner[x][y] = next_runner[x][y];
		}
	}
}

int GetCatcherDir() {
	int x, y;
	tie(x, y) = catcher;
	int move_dir;
	if (forward_facing) move_dir = catcher_next_dir[x][y];
	else move_dir = catcher_rev_dir[x][y];
	return move_dir;
}

void CheckFacing() {
	if(catcher == make_pair(0, 0) && forward_facing) forward_facing = false;
	else if(catcher == make_pair(n / 2, n / 2) && !forward_facing) forward_facing = true;
}

void MoveCatcher() {
	int x, y;
	tie(x, y) = catcher;
	int move_dir = GetCatcherDir();
	catcher = make_pair(x + dx[move_dir], y + dy[move_dir]);
	CheckFacing();
}

void GetScore(int t) {
	int x, y;
	tie(x, y) = catcher;
	int move_dir = GetCatcherDir();

	for (int dis = 0; dis < 3; dis++) {
		int nx = x + dis * dx[move_dir], ny = y + dis * dy[move_dir];
		if (InRange(nx, ny) && !tree[nx][ny]) {
			ans += t * (int)runner[nx][ny].size();
			runner[nx][ny].clear();
		}
	}
}

void Simulate(int t) {
	MoveAllRunner();

	MoveCatcher();
	
	GetScore(t);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> h >> k;

	while(m--){
		int x, y, d;
		cin >> x >> y >> d;
		runner[x - 1][y - 1].push_back(d);
	}

	while(h--){
		int x, y;
		cin >> x >> y;
		tree[x - 1][y - 1] = true;
	}

	catcher = make_pair(n / 2, n / 2);
	InitializeCatcherPath();

	for (int t = 1; t <= k; t++) Simulate(t);
	cout << ans << "\n";
	return 0;
}