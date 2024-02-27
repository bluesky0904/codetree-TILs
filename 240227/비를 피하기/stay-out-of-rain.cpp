// 0은 해당 칸이 이동할 수 있는 곳임
// 1은 벽이 있어 이동할 수 없는 곳임
// 2는 해당 칸에 사람이 서있음을 의미
// 3은 해당 공간이 비를 피할 수 있는 공간임
// 벽이 아닌 곳은 전부 이동 가능, 이동하는데 1초
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_N 100
#define DIR_NUM 4

int n, h, m;
vector<pair<int, int>> people_pos;

int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int taken_time[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

void Initialize() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void BFS(int x, int y) {
	Initialize();
	queue<tuple<int, int, int>> q;
	q.push(make_tuple(x, y, 0));
	visited[x][y] = true;
	while (!q.empty()) {
		int cx, cy, cnt;
		tie(cx, cy, cnt) = q.front();
		q.pop();

		if (grid[cx][cy] == 3) {
			taken_time[x][y] = cnt;
			return;
		}

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] != 1) {
				q.push(make_tuple(nx, ny, cnt + 1));
				visited[nx][ny] = true;
			}
		}
	}
	taken_time[x][y] = -1;
	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> h >> m;
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
			cin >> grid[i][j];
			if (grid[i][j] == 2) people_pos.push_back(make_pair(i, j));
		}
	}

	for (int i = 0; i < people_pos.size(); i++) {
		int x, y;
		tie(x, y) = people_pos[i];
		BFS(x, y);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << taken_time[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}