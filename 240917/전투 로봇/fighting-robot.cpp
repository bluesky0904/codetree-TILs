/*
n * n 격자판 : 한 칸에는 몬스터가 최대 하나만 존재 가능
m개의 몬스터 : 레벨
하나의 전투로봇 : 레벨. 초기 레벨 2, 1초에 상하좌우로 인접한 한 칸씩 이동. 몬스터를 없애는 시간은 없음. 본인의 레벨과 같은 수의 몬스터를 없앨 때마다 레벨이 상승함.
	몬스터의 레벨이 작은 경우 : 지나갈 수 있고 없앨 수 있음
	몬스터의 레벨이 같은 경우 : 지나갈 수 있고 없앨 수 없음
	몬스터의 레벨이 큰 경우 : 지나갈 수 없음

전투로봇이 어디로 이동할지 정하는 규칙
- 없앨 수 있는 몬스터가 있다면 해당 몬스터를 없애러 감.
- 없앨 수 있는 몬스터가 하나 이상이라면, 거리가 가장 가까운 몬스터를 없애러 감.
	거리는 해당 칸으로 이동할 때 지나야하는 칸의 개수의 최솟값을 뜻함.
	우선 순위 : 거리 최소 > 행 값 최소 > 열 값 최소
- 없앨 수 있는 몬스터가 없다면 일을 끝냄.

전투 로봇이 일을 끝내기 전까지 걸린 시간 출력
*/

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n;
int rx, ry, cnt = 0;
int robot_level = 2;
int ans = 0;

int grid[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,1,0,0};
int dy[DIR_NUM] = {0,0,-1,1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

tuple<int, int, int> BFS() {
	bool visited[MAX_N][MAX_N] = {false};
	int px = -1, py = -1, min_dist = INT_MAX;
	vector<tuple<int, int, int>> list;

	queue<tuple<int, int, int>> q;
	q.push({rx, ry, 0});
	visited[rx][ry] = true;

	while (!q.empty()) {
		int cx, cy, cnt;
		tie(cx, cy, cnt) = q.front(); q.pop();
		
		if (1 <= grid[cx][cy] && grid[cx][cy] <= 6 && grid[cx][cy] < robot_level) {
			list.push_back({ cnt, cx, cy });
		}

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] <= robot_level) {
				q.push({ nx, ny, cnt + 1 });
				visited[nx][ny] = true;
			}
		}
	}

	if(list.empty()) return { 0,-1,-1};
	else {
		sort(list.begin(), list.end());
		tie(min_dist, px, py) = list[0];
		return {min_dist, px, py};
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 9) {
				rx = i;
				ry = j;
			}
		}
	}

	while (1) {
		int px, py, min_dist;
		tie(min_dist, px, py) = BFS();
		if (px == -1 && py == -1) break;
		ans += min_dist;
		grid[rx][ry] = 0;
		rx = px;
		ry = py;
		grid[rx][ry] = 9;
		cnt++;
		if (cnt == robot_level) {
			robot_level++;
			cnt = 0;
		}
	}

	cout << ans << "\n";
	return 0;
}