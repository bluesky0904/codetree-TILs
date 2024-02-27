#include <iostream>
#include <queue>
using namespace std;

#define MAX_NUM 200
#define DIR_NUM 4

int n, m;
int elapsed_time, last_melt_cnt;

queue<pair<int, int>> q;
int grid[MAX_NUM][MAX_NUM];
bool visited[MAX_NUM][MAX_NUM];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

void Initialize() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = false;
		}
	}
}

void BFS() {
	Initialize();
	q.push(make_pair(0, 0));
	visited[0][0] = true;

	while (!q.empty()) {
		pair<int, int> curr_pos = q.front();
		int x = curr_pos.first, y = curr_pos.second;
		q.pop();
		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 0) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
			}
		}
	}
}

bool OutsideGlacierExistInNeighbor(int x, int y) {
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = x + dx[dir], ny = y + dy[dir];
		if (InRange(nx, ny) && grid[nx][ny] == 0 && visited[nx][ny] == true) return true;
	}
	return false;
}

void Melt() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 1 && OutsideGlacierExistInNeighbor(i, j)) {
				grid[i][j] = 0;
				last_melt_cnt++;
			}
		}
	}
}

void Simulate() {
	elapsed_time++;
	last_melt_cnt = 0;
	BFS();
	Melt();
}

bool GlacierExist() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 1) return true;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	do {
		Simulate();
	} while (GlacierExist());

	cout << elapsed_time << " " << last_melt_cnt;
	return 0;
}