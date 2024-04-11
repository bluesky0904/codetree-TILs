/*
[객체관리]
전기차 : 배터리 (모두 소진 되는 경우 더이상 움직일 수 없음) -> car_x, car_y, remain 변수로 관리
승객 : m 명 -> passenger 벡터로 관리
목적지 : m 개
벽 : 차가 지나갈 수 없는 위치 -> grid 배열로 관리

하나의 격자에 여러 객체가 들어가지 않음
객체가 이동하지 않음

[알고리즘]
전기차는 항상 최단 거리로 이동함 (BFS에서 -1 output됐을 경우 어떻게 처리할지 고민)
한 칸을 이동할 때 1만큼의 배터리 소모
승객을 목적지로 태워주면 -> 해당 승객을 태워 이동하며 소모한 배터리 양의 두 배만큼 충전
이동하는 도중에 배터리가 모두 소모되면 그 즉시 종료
만일 승객을 목적지로 이동시킨 동시에 배터리가 모두 소모된 경우 배터리 충전이 이루어지고 운행 가능
마지막 승객을 태워주고 운행을 종료하는 순간에도 충전은 이루어짐

승객이 여러명일 경우 우선순위 : 최단거리인 승객 > 행이 작은 승객 > 열이 작은 승객

모든 승객을 성공적으로 데려다 줄 수 있는지, 데려다줄 수 있는 경우 최종적으로 남는 배터리 양 출력
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

// n : 격자의 크기, m : 승객의 수, c : 초기 배터리 충전량
int n, m, c;
int grid[MAX_N][MAX_N];
int car_x, car_y, remain;
bool is_possible = true;

struct Passenger {
	int sx, sy, ex, ey;
};
vector<Passenger> passengers;

bool visited[MAX_N][MAX_N];
void InitVisited() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			visited[x][y] = false;
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
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

bool cmp(Passenger a, Passenger b) {
	int min_route_a = BFS(car_x, car_y, a.sx, a.sy);
	int min_route_b = BFS(car_x, car_y, b.sx, b.sy);
	if (min_route_a != min_route_b) {
		if (min_route_a < min_route_b) return true;
		else return false;
	}
	if (a.sx != b.sx) return a.sx < b.sx;
	return a.sy < b.sy;
}

/*
전기차는 항상 최단 거리로 이동함
한 칸을 이동할 때 1만큼의 배터리 소모
승객을 목적지로 태워주면 -> 해당 승객을 태워 이동하며 소모한 배터리 양의 두 배만큼 충전
이동하는 도중에 배터리가 모두 소모되면 그 즉시 종료
만일 승객을 목적지로 이동시킨 동시에 배터리가 모두 소모된 경우 배터리 충전이 이루어지고 운행 가능
마지막 승객을 태워주고 운행을 종료하는 순간에도 충전은 이루어짐
*/
bool Simulate() {
	if (passengers.empty()) return false;

	sort(passengers.begin(), passengers.end(), cmp);
	Passenger cur_passenger = passengers.front();
	passengers.erase(passengers.begin());
	int min_route_start = BFS(car_x, car_y, cur_passenger.sx, cur_passenger.sy);
	if (min_route_start == -1) {
		is_possible = false;
		return false;
	}
	if (remain > min_route_start) {
		remain -= min_route_start;
		car_x = cur_passenger.sx;
		car_y = cur_passenger.sy;
	}
	else {
		is_possible = false;
		return false;
	}
	int min_route_end = BFS(car_x, car_y, cur_passenger.ex, cur_passenger.ey);
	if (min_route_end == -1) {
		is_possible = false;
		return false;
	}
	if (remain >= min_route_end) {
		remain -= min_route_end;
		car_x = cur_passenger.ex;
		car_y = cur_passenger.ey;
	}
	else {
		is_possible = false;
		return false;
	}
	remain += (min_route_end * 2);

	return true;
}

void Print() {
	cout << "Car Info : " << car_x  << " " << car_y << " " << remain << "\n";
	cout << "Passenger Info : " << "\n";
	for (int i = 0; i < (int)passengers.size(); i++) {
		cout << passengers[i].sx << " " << passengers[i].sy << " " << passengers[i].ex << " " << passengers[i].ey << "\n";
	}
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

	int x, y;
	cin >> x >> y;
	car_x = x - 1, car_y = y - 1;
	remain = c;
	
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
		//Print();
	}

	if (is_possible && passengers.empty()) cout << remain << "\n";
	else cout << -1 << "\n";
	return 0;
}