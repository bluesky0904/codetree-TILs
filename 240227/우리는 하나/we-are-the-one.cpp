// 나라 -> 도시 -> 높이 정보
// k개의 도시를 겹치지 않게 적절하게 골라, 갈 수 있는 도시의 수 최대화
// 이동은 상하좌우 & 도시간 높이의 차가 u이상 d이하인 경우
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_N 8
#define DIR_NUM 4

int n, k, u, d;
int max_cnt;

queue<pair<int, int>> q;
vector<pair<int, int>> city;
vector<pair<int, int>> selected;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

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

int BFS() {
	int cnt = 0;
	Initialize();

	for (int i = 0; i < selected.size(); i++) {
		int x, y;
		tie(x, y) = selected[i];
		q.push(make_pair(x, y));
		visited[x][y] = true;
	}
	while (!q.empty()) {
		int cx, cy;
		tie(cx, cy) = q.front();
		q.pop();
		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && u <= abs(grid[cx][cy] - grid[nx][ny]) && abs(grid[cx][cy] - grid[nx][ny]) <= d) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == true) cnt++;
		}
	}

	return cnt;
}

void FindMaxCnt(int curr_idx, int cnt) {
	if (cnt == k) {
		max_cnt = max(max_cnt, BFS());
		return;
	}

	if (curr_idx == (int)city.size()) return;

	FindMaxCnt(curr_idx + 1, cnt);
	selected.push_back(city[curr_idx]);
	FindMaxCnt(curr_idx + 1, cnt + 1);
	selected.pop_back();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k >> u >> d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			city.push_back(make_pair(i, j));
		}
	}

	FindMaxCnt(0, 0);
	cout << max_cnt << "\n";
}