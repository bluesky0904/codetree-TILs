/*
자율주행 전기차 : 배터리 양이 모두 소진되는 경우 더이상 움직일 수 없음. 최단거리로 이동. 한 칸을 이동할 때 1만큼의 배터리 소요,
승객을 목적지에 태워주면 소모한 배터리 양의 두배만큼 충전. 이동하는 도중에 배터리가 모두 소모되면 종료 but 이동시킨 동시에 소모되면 운행 가능 + 마지막에도 충전
승객 : m명. 우선순위 : 거리 최소 > 행 최소 > 열 최소
격자 : 벽, 승객, 전기차

모든 승객을 데려다 줄 수 있는지 알아내고, 데려다줄 수 있는 경우 최종적으로 남는 배터리의 양을 출력
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_N 20
#define MAX_M 400
#define DIR_NUM 4

int n, m;
int c, car_x, car_y;
pair<int, int> start_pos[MAX_M + 1];
pair<int, int> end_pos[MAX_M + 1];
bool passenger[MAX_M + 1];
int grid[MAX_N+1][MAX_N+1];

int dx[DIR_NUM] = {-1,1,0,0};
int dy[DIR_NUM] = {0,0,-1,1};

bool InRange(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

pair<int, int> BFS() {
	int dist = 0, num;
	queue<tuple <int, int, int>> q;
	bool visited[MAX_N + 1][MAX_N + 1] = { false };
	vector<tuple<int, int, int, int>> list;

	q.push({0, car_x, car_y});
	visited[car_x][car_y] = true;

	while (!q.empty()) {
		int dist, cx, cy;
		tie(dist, cx, cy) = q.front(); q.pop();
		for (int i = 1; i <= m; i++) {
			if (!passenger[i] && start_pos[i] == make_pair(cx, cy)) {
				list.push_back({dist, cx, cy, i});
			}
		}

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 0) {
				q.push({dist + 1, nx, ny });
				visited[nx][ny] = true;
			}
		}
	}

	if (list.empty()) return make_pair(-1, -1);

	sort(list.begin(), list.end());
	tie(dist, ignore, ignore, num) = list[0];

	return make_pair(dist, num);
}

int StartToEnd(int sx, int sy, int ex, int ey) {
	queue<tuple<int, int, int>> q;
	bool visited[MAX_N + 1][MAX_N + 1] = { false };

	q.push({ 0, sx, sy });
	visited[sx][sy] = true;
	while (!q.empty()) {
		int dist, cx, cy;
		tie(dist, cx, cy) = q.front(); q.pop();
		if (cx == ex && cy == ey) return dist;

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 0) {
				q.push({ dist + 1, nx, ny });
				visited[nx][ny] = true;
			}
		}
	}
	return -1;
}

bool Simulate() {
	int dist, num;
	tie(dist, num) = BFS();
	if (dist == -1) return false;
	int start_to_end = StartToEnd(start_pos[num].first, start_pos[num].second, end_pos[num].first, end_pos[num].second);
	if (start_to_end == -1) {
		return false;
	}
	dist += start_to_end;
	if (c >= dist) {
		passenger[num] = true;
		c -= dist;
		c += start_to_end * 2;
		tie(car_x, car_y) = end_pos[num];
		return true;
	}
	else {
		c -= dist;
		return false;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}
	cin >> car_x >> car_y;
	for (int i = 1; i <= m; i++) {
		int x_s, y_s, x_e, y_e;
		cin >> x_s >> y_s >> x_e >> y_e;
		start_pos[i] = { x_s, y_s };
		end_pos[i] = { x_e, y_e };
	}
	while (1) {
		int cnt = 0;
		for (int i = 1; i <= m; i++) {
			if (passenger[i]) cnt++;
		}
		if (cnt == m) break;

		if (!Simulate()) {
			c = -1;
			break;
		}
	}

	cout << c << "\n";
	return 0;
}