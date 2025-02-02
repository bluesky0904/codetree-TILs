/*
도시 : n x n, 0-based
	   병원 2 
	   벽 1
	   바이러스 0 

m 개의 병원을 적절히 골라 최대한 빨리 바이러스를 없애려고 함
m 개의 병원을 고르게 되면,
골라진 병원들을 시작으로 매 초마다 상하좌우로 인접한 지역 중 벽을 제외한 지역에 백신이 공급되어 바이러스가 사라짐

m개의 병원을 적절히 골라 바이러스를 전부 없애는데 걸리는 시간 중 최소 시간
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <climits>
#include <tuple>
using namespace std;

#define MAX_N 50
#define DIR_NUM 4

int n, m;
int grid[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
int min_time;
vector<pair<int, int>> hospital_pos;
vector<pair<int, int>> selected;

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool isFilled() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0 && visited[i][j] == -1) return false; // 체크할때는 0인 칸만 확인하면되는것
		}
	}
	return true;
}

bool inRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

int bfs() {
	queue<tuple<int, int, int>> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = -1;
		}
	}
	
	for (int i = 0; i < m; i++) {
		int x, y;
		tie(x, y) = selected[i];
		q.push(make_tuple(x, y, 0));
		visited[x][y] = 0;
	}
	while (!q.empty()) {
		int cx, cy, cnt;
		tie(cx, cy, cnt) = q.front(); q.pop();

		if (isFilled()) {
			int max_time = -1;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					max_time = max(max_time, visited[i][j]);
				}
			}
			return max_time;
		}

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (inRange(nx, ny) && grid[nx][ny] != 1 && visited[nx][ny] == -1) {
				visited[nx][ny] = cnt + 1;
				q.push(make_tuple(nx, ny, cnt + 1));
			}
		}
	}
	return -1;
}

void findMinTime(int start, int cnt) {
	if (cnt == m) {
		int elapsed_time = bfs();
		if(elapsed_time != -1) min_time = min(min_time, elapsed_time);

		return;
	}

	for (int i = start; i < (int)hospital_pos.size(); i++) {
		selected.push_back(hospital_pos[i]);
		findMinTime(i + 1, cnt + 1); // 여기서 i를 넣었어야 함
		selected.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 2) hospital_pos.push_back({ i, j });
		}
	}

	min_time = INT_MAX;

	findMinTime(0, 0);
	
	if (min_time != INT_MAX) cout << min_time << "\n";
	else cout << -1 << "\n";

	return 0;
}