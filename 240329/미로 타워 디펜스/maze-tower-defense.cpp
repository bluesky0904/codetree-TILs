#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 25
#define DIR_NUM 4

// 격자의 크기 n, 총 라운드 수 m
int n, m;
// 플레이어가 얻은 점수
int ans = 0;

// 나선형 방향 위치 관리
vector<pair<int, int>> spiral_point;

// 몬스터의 위치
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];

void SearchSpiral() {
	int dx[DIR_NUM] = {0,1,0,-1};
	int dy[DIR_NUM] = {-1,0,1,0};

	int cx = n / 2, cy = n / 2;
	int move_dir = 0, move_num = 1;
	while (!(cx == 0 && cy == 0)) {
		for (int i = 0; i < move_num; i++) {
			cx += dx[move_dir];
			cy += dy[move_dir];
			spiral_point.push_back({ cx, cy });
			if(cx == 0 && cy == 0) break;
		}
		move_dir = (move_dir + 1) % 4;
		if(move_dir == 0 || move_dir == 2) move_num++;
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void Pull() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y] = 0;
		}
	}

	int cur_idx = 0;
	int spiral_idx = 0;
	int end_idx = spiral_point.size();
	while (cur_idx < end_idx) {
		int x, y;
		tie(x, y) = spiral_point[cur_idx];
		if (grid[x][y]) {
			int nx, ny;
			tie(nx, ny) = spiral_point[spiral_idx];
			next_grid[nx][ny] = grid[x][y];
			spiral_idx++;
		}
		cur_idx++;
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void Attack(int d, int p) {
	int dx[DIR_NUM] = {0,1,0,-1};
	int dy[DIR_NUM] = {1,0,-1,0};

	int cx = n / 2, cy = n / 2;
	for (int dis = 1; dis <= p; dis++) {
		int nx = cx + dx[d]*dis, ny = cy + dy[d]*dis;
		if (InRange(nx, ny)) {
			ans += grid[nx][ny];
			grid[nx][ny] = 0;
		}
	}

	Pull();
}

int GetEndIdxOfSameNum(int idx) {
	int end_idx = idx + 1;
	int cur_num = grid[spiral_point[idx].first][spiral_point[idx].second];
	int end_of_spiral = spiral_point.size();

	while (end_idx < end_of_spiral) {
		if (grid[spiral_point[end_idx].first][spiral_point[end_idx].second] == cur_num) end_idx++;
		else break;
	}

	return end_idx - 1;
}

bool Bomb() {
	bool did_explode = false;
	int cur_idx = 0;
	int end_of_spiral = spiral_point.size();
	while (cur_idx < end_of_spiral) {
		int end_idx = GetEndIdxOfSameNum(cur_idx);
		int cur_num = grid[spiral_point[cur_idx].first][spiral_point[cur_idx].second];
		if (cur_num == 0) break;
		if (end_idx - cur_idx + 1 >= 4) {
			for (int idx = cur_idx; idx <= end_idx; idx++) {
				int x, y;
				tie(x, y) = spiral_point[idx];
				ans += grid[x][y];
				grid[x][y] = 0;
			}
			did_explode = true;
		}
		cur_idx = end_idx + 1;
	}
	return did_explode;
}


void Organize() {
	while (true) {
		bool bombed = Bomb();
		if (!bombed) break;
		Pull();
	}
}

void LookAndSay() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y] = 0;
		}
	}

	int temp_idx = 0;
	int cur_idx = 0;
	int end_of_spiral = spiral_point.size();
	while (cur_idx < end_of_spiral) {
		int end_idx = GetEndIdxOfSameNum(cur_idx);
		int cnt = end_idx - cur_idx + 1;
		int num = grid[spiral_point[cur_idx].first][spiral_point[cur_idx].second];

		if (num == 0) break;

		if (temp_idx >= end_of_spiral) break;
		int tx, ty;
		tie(tx, ty) = spiral_point[temp_idx];
		next_grid[tx][ty] = cnt;
		temp_idx++;

		if(temp_idx >= end_of_spiral) break;
		tie(tx, ty) = spiral_point[temp_idx];
		next_grid[tx][ty] = num;
		temp_idx++;

		cur_idx = end_idx + 1;
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void Simulate(int d, int p) {
	Attack(d, p);
	Organize();
	LookAndSay();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	SearchSpiral();

	while (m--) {
		int d, p;
		cin >> d >> p;
		Simulate(d, p);
	}

	cout << ans << "\n";
	return 0;
}