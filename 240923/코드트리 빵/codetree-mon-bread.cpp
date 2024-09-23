/*
사람 : m명, m번 사람은 정확히 m분에 각자의 베이스캠프에서 출발하여 편의점으로 이동
출발 시간이 되기 전까지 격자 밖으로 나와있으며, 사람들이 목표로 하는 편의점은 모두 다름.

격자 : n * n

3가지 행동은 총 1분 동안 진행, 정확히 1,2,3 순서로 진행되어야 함.
1. 격자에 있는 사람들 모두가 본인이 가고 싶은 편의점 방향을 향해서 1칸 움직임
최단거리 > 상좌우하
2. 만약 편의점에 도착한다면 해당 편의점에서 멈추게 되고, 이때부터 다른 사람들은 해당 편의점이
있는 칸을 지날 수 없게 됨.
격자에 있는 사람들이 모두 이동한 뒤에 해당 칸을 지나갈 수 없어짐에 유의.
3. 현재 시간이 t분이고 t <= m를 만족한다면, t번 사람은 자신이 가고 싶은 편의점과 가장 가까이
있는 베이스 캠프에 들어감.
최단거리 > 행 최소 > 열 최소
t번 사람이 베이스 캠프로 이동하는 데에는 시간이 전혀 소요되지 않음
이때부터 다른 사람들은 해당 베이스 캠프가 있는 칸을 지나갈 수 없게 됨.
t번 사람이 편의점을 향해 움직이기 시작했더라도 해당 베이스 캠프는 앞으로 절대 지나갈 수 없음에
유의.
해당 턴 격자에 있는 사람들이 모두 이동한 뒤에 해당 칸을 지나갈 수 없어짐에 유의.

=> 총 몇 분 후에 모두 편의점에 도착하는지 구하기
*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <tuple>
#include <climits>
using namespace std;

#define MAX_N 15
#define MAX_M 30
#define DIR_NUM 4

int n, m;
pair<int, int> store[MAX_M + 1];
pair<int, int> pos[MAX_M + 1];

int grid[MAX_N+1][MAX_N+1]; // 0의 경우에는 빈 공간, 1의 경우에는 베이스캠프
bool is_passed[MAX_N + 1][MAX_N + 1] = { false };

bool visited[MAX_N + 1][MAX_N + 1];
int dist[MAX_N + 1][MAX_N + 1];

int dx[DIR_NUM] = { -1,0,0,1 };
int dy[DIR_NUM] = { 0,-1,1,0 };

bool InRange(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

void BFS(pair<int, int> start_pos) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			visited[i][j] = false;
			dist[i][j] = 0;
		}
	}

	queue<pair<int, int>> q;
	q.push(start_pos);
	visited[start_pos.first][start_pos.second] = true;
	dist[start_pos.first][start_pos.second] = 0;
	
	while (!q.empty()) {
		int cx, cy; tie(cx, cy) = q.front(); q.pop();
		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && !is_passed[nx][ny]) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
				dist[nx][ny] = dist[cx][cy] + 1;
			}
		}
	}
}

pair<int, int> GetNextPos(int x, int y, int idx) {
	BFS(store[idx]);

	int mx = -1, my = -1;
	int min_dist = INT_MAX;
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = x + dx[dir], ny = y + dy[dir];
		if (InRange(nx, ny) && visited[nx][ny] && min_dist > dist[nx][ny]) {
			mx = nx;
			my = ny;
			min_dist = dist[nx][ny];
		}
	}
	return make_pair(mx, my);
}

void GoStore() {
	for (int i = 1; i <= m; i++) {
		if (pos[i] == make_pair(-1, -1) || pos[i] == store[i]) continue;
		int x, y;
		tie(x, y) = pos[i];
		pos[i] = GetNextPos(x, y, i);
	}

	for (int i = 1; i <= m; i++) {
		if (pos[i] == store[i]) is_passed[pos[i].first][pos[i].second] = true;
	}
}

void GoBase(int idx) {
	BFS(store[idx]);

	int mx = -1, my = -1;
	int min_dist = INT_MAX;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (grid[i][j] == 1 && visited[i][j] && min_dist > dist[i][j]) {
				mx = i;
				my = j;
				min_dist = dist[i][j];
			}
		}
	}
	pos[idx] = make_pair(mx, my);
	is_passed[mx][my] = true;
}

bool Finish() {
	for (int i = 1; i <= m; i++) if (pos[i] != store[i]) return false;
	return true;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		store[i] = make_pair(x, y);
		pos[i] = make_pair(-1, -1);
	}

	int t = 0;
	while (1) {
		t++;
		GoStore();
		if (t <= m) GoBase(t);
		if (Finish()) break;
	}

	cout << t << "\n";
	return 0;
}