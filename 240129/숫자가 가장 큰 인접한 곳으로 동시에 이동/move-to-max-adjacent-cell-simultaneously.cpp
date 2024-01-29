#include <iostream>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n, m, t;
int grid[MAX_N][MAX_N];
int marble_count[MAX_N][MAX_N];
int next_marble_count[MAX_N][MAX_N];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> GetNextPos(int x, int y) {
	int dx[DIR_NUM] = {-1,1,0,0};
	int dy[DIR_NUM] = {0,0,-1,1};
	int max_num = 0;
	int mx, my;
	for (int i = 0; i < DIR_NUM; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (InRange(nx, ny) && grid[nx][ny] > max_num) {
			max_num = grid[nx][ny];
			mx = nx;
			my = ny;
		}
	}
	return make_pair(mx, my);
}

void Move(int x, int y) {
	pair<int, int> next_pos = GetNextPos(x, y);
	int nx = next_pos.first, ny = next_pos.second;
	next_marble_count[nx][ny]++;
}

void MoveAll() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_marble_count[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (marble_count[i][j] == 1) Move(i, j);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			marble_count[i][j] = next_marble_count[i][j];
		}
	}
}

void RemoveDuplicateMarbles() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (marble_count[i][j] >= 2) marble_count[i][j] = 0;
		}
	}
}

void Simulate() {
	MoveAll();
	RemoveDuplicateMarbles();
}

int RemainMarbleCount() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (marble_count[i][j] == 1) cnt++;
		}
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m >> t;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int r, c; cin >> r >> c; r--; c--;
		marble_count[r][c] = 1;
	}
	
	while (t--) Simulate();

	cout << RemainMarbleCount() << "\n";
}