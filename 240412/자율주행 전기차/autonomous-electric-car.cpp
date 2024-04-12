/*
[객체 관리]
자동차 ->  car_x, car_y, battery 변수
승객 : m명 -> passenger 벡터
벽 -> grid 배열
[알고리즘]
1. 항상 최단거리로 이동
2. 한칸에 1만큼 배터리 소모
3. 승객을 목적지로 무사히 태워주면 그 승객을 태워서 이동하며 소모한 배터리 양의 두 배만큼을 충전
4. 승객이 여러명인 경우 우선 순위 : 현재 위치에서의 최단 거리 > 행이 가장 작은 경우 > 열이 가장 작은 경우
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

// n : 격자의 크기, m : 승객의 수, c : 초기 배터리 충전량
int n, m, c;
int grid[MAX_N][MAX_N];
int car_x, car_y, battery;
// 모든 손님을 이동시킬 수 있는지를 나타내는 변수
bool is_possible = true;
// BFS
bool visited[MAX_N][MAX_N];

struct Passenger {
	int sx, sy, ex, ey, min_dist;
};

vector<Passenger> passengers;

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void GetMinDistance() {
	int distance[MAX_N][MAX_N];
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			distance[x][y] = -1;
		}
	}

	queue<tuple<int, int, int>> q;
	q.push(make_tuple(car_x, car_y, 0));
	distance[car_x][car_y] = 0;

	while (!q.empty()) {
		int cx, cy, dist;
		tie(cx, cy, dist) = q.front();
		q.pop();

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && grid[nx][ny] == 0 && distance[nx][ny] == -1) {
				q.push(make_tuple(nx, ny, dist + 1));
				distance[nx][ny] = dist + 1;
			}
		}
	}

	for (int i = 0; i < (int)passengers.size(); i++) {
		passengers[i].min_dist = distance[passengers[i].sx][passengers[i].sy];
	}
}

bool cmp(Passenger a, Passenger b) {
	if (a.min_dist != b.min_dist) return a.min_dist < b.min_dist;
	if (a.sx != b.sx) return a.sx < b.sx;
	return a.sy < b.sy;
}

/*
[알고리즘]
1. 항상 최단거리로 이동
2. 한칸에 1만큼 배터리 소모
3. 승객을 목적지로 무사히 태워주면 그 승객을 태워서 이동하며 소모한 배터리 양의 두 배만큼을 충전
4. 승객이 여러명인 경우 우선 순위 : 현재 위치에서의 최단 거리 > 행이 가장 작은 경우 > 열이 가장 작은 경우
*/

void InitVisited() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			visited[x][y] = false;
		}
	}
}

int BFS(int sx, int sy, int ex, int ey) {
	InitVisited();
	queue<tuple<int, int, int>> q;
	q.push(make_tuple(sx, sy, 0));
	visited[sx][sy] = true;

	while (!q.empty()) {
		int cx, cy, cnt;
		tie(cx, cy, cnt) = q.front();
		q.pop();

		if (cx == ex && cy == ey) return cnt;

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 0) {
				q.push(make_tuple(nx, ny, cnt + 1));
				visited[nx][ny] = true;
			}
		}
	}

	return -1;
}

bool Simulate() {
	if (passengers.empty()) return false;
	GetMinDistance();
	sort(passengers.begin(), passengers.end(), cmp);
	Passenger target = passengers.front();
	passengers.erase(passengers.begin());
	if (target.min_dist == -1) {
		is_possible = false;
		return false;
	}

	if (battery > target.min_dist) {
		battery -= target.min_dist;
		car_x = target.sx;
		car_y = target.sy;
	}
	else {
		is_possible = false;
		return false;
	}

	int to_end_dist = BFS(target.sx, target.sy, target.ex, target.ey);
	if (to_end_dist == -1) {
		is_possible = false;
		return false;
	}
	if (battery >= to_end_dist) {
		battery -= to_end_dist;
		car_x = target.ex;
		car_y = target.ey;
	}
	else {
		is_possible = false;
		return false;
	}
	battery += (to_end_dist * 2);
	return true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	cin >> n >> m >> c;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cin >> grid[x][y];
		}
	}
	cin >> car_x >> car_y;
	car_x--; car_y--;
	battery = c;
	for (int i = 0; i < m; i++) {
		int sx, sy, ex, ey;
		cin >> sx >> sy >> ex >> ey;
		Passenger passenger;
		passenger.sx = sx - 1;
		passenger.sy = sy - 1;
		passenger.ex = ex - 1;
		passenger.ey = ey - 1;
		passengers.push_back(passenger);
	}

	while (true) {
		if (!Simulate()) break;
	}

	if (is_possible) cout << battery << "\n";
	else cout << -1 << "\n";
	return 0;
}