/*
사람 : m명
1번 사람은 1분에, 2번 사람은 2분에, ... , m번 사람은 m분에 각자의 베이스캠프에서 출발하여 편의점으로 이동
사람들은 출발 시간이 되기 전까지 격자 밖에 나와있으며, 사람들이 목표로 하는 편의점은 모두 다름

격자 : n x n

지나갈 수 없는 칸 표시

3가지 행동은 총 1분 동안 진행되며, 정확히 1, 2, 3 순서로 진행되어야 함에 유의
1. 격자에 있는 사람들 모두가 본인이 가고 싶은 편의점 방향을 향해 1 칸 움직임
최단거리로 움직이며 최단 거리로 움직이는 방법이 여러가지라면 상좌우하 우선순위
최단거리 : 상하좌우 인접한 칸 중 이동가능한 칸으로만 이동하여 도달하기까지 거쳐야 하는 칸의 수가 최소가 되는 거리

2. 만약 편의점에 도착한다면 해당 편의점에서 멈추게 되고, 이때부터 다른 사람들은 해당 편의점이 있는 칸을 지나갈 수 없게 됨.
격자에 있는 사람들이 모두 이동한 뒤에 해당 칸을 지나갈 수 없어짐에 유의

3. 현재 시간이 t분이고 t <= m을 만족한다면 t번 사람은 자신이 가고 싶은 편의점과 가장 가까이 있는 베이스 캠프에 들어감
거리 최소 > 행 최소 > 열 최소 우선순위
t번 사람이 베이스 캠프로 이동하는 데에는 시간이 전혀 소요되지 않음

이때부터 다른 사람들은 해당 베이스 캠프가 있는 칸을 지나갈 수 없게 됨
t번 사람이 편의점을 향해 움직이기 시작했더라도 해당 베이스 캠프는 앞으로 절대 지나갈 수 없음에 유의
해당 턴 격자에 있는 사람들이 모두 이동한 뒤에 해당 칸을 지나갈 수 없어짐

이미 사람들이 도착한 편의점이나 출발한 적이 있는 베이스캠프의 경우 움직일 때 절대 지나갈 수 없는 공간임을 유의

총 몇 분 후에 모두 편의점에 도착하는지를 구하는 프로그램

이동하는 도중 동일한 칸에 둘 이상의 사람이 위치하게 되는 경우 가능
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX_N 15
#define MAX_M 30
#define OUT_OF_GRID make_pair(-1, -1)
#define DIR_NUM 4

struct Base {
	int dist;
	int row;
	int col;
};

bool Comparator(Base& a, Base& b) {
	if (a.dist != b.dist) return a.dist < b.dist;
	if (a.row != b.row) return a.row < b.row;
	return a.col < b.col;
}

int n, m;
int grid[MAX_N + 1][MAX_N + 1];
bool blocked[MAX_N + 1][MAX_N + 1];

vector<pair<int, int>> base_camp;

pair<int, int> pos[MAX_M + 1];
pair<int, int> cvs[MAX_M + 1];

bool visited[MAX_N + 1][MAX_N + 1];

int back_x[MAX_N + 1][MAX_N + 1];
int back_y[MAX_N + 1][MAX_N + 1];

int dx[DIR_NUM] = { -1,0,0,1 };
int dy[DIR_NUM] = { 0,-1,1,0 };

bool allArrive() {
	for (int i = 1; i <= m; i++) {
		if (pos[i] != cvs[i]) return false;
	}
	return true;
}

bool inRange(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

void moveAll() {
	for (int i = 1; i <= m; i++) {
		if (pos[i] == OUT_OF_GRID) continue;
		if (pos[i] == cvs[i]) continue; // 이미 도착한 사람은 움직일 필요가 없음

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				visited[i][j] = false;
				back_x[i][j] = -1;
				back_y[i][j] = -1;
			}
		}

		queue<pair<int, int>> q;

		q.push(pos[i]);
		visited[pos[i].first][pos[i].second] = true;
		while (!q.empty()) {
			int cx = q.front().first, cy = q.front().second; q.pop();

			if (cx == cvs[i].first && cy == cvs[i].second) {

				while (1) {
					int bx = back_x[cx][cy], by = back_y[cx][cy];

					if (bx == pos[i].first && by == pos[i].second) {
						pos[i] = { cx, cy };
						break;
					}

					cx = bx, cy = by;
				}

				break; // return이 아니라 break를 사용해야 함
			}

			for (int dir = 0; dir < DIR_NUM; dir++) {
				int nx = cx + dx[dir], ny = cy + dy[dir];

				if (!inRange(nx, ny) || visited[nx][ny] || blocked[nx][ny]) continue;

				q.push({ nx, ny });
				visited[nx][ny] = true;
				back_x[nx][ny] = cx;
				back_y[nx][ny] = cy;
			}
		}
	}
}

void goBase(int time) {
	if (time > m) return;

	vector<Base> v;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			visited[i][j] = false;
		}
	}

	queue<tuple<int, int, int>> q;
	q.push({ cvs[time].first, cvs[time].second, 0});
	visited[cvs[time].first][cvs[time].second] = true;

	while (!q.empty()) {
		int cx, cy, cnt;
		tie(cx, cy, cnt) = q.front(); q.pop();

		if (grid[cx][cy] == 1 && !blocked[cx][cy]) {
			Base new_base;
			new_base.dist = cnt;
			new_base.row = cx;
			new_base.col = cy;

			v.push_back(new_base);
		}

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];

			if (!inRange(nx, ny) || visited[nx][ny] || blocked[nx][ny]) continue;
			q.push({ nx, ny , cnt + 1 });
			visited[nx][ny] = true;
		}
	}

	if (v.empty()) return;

	sort(v.begin(), v.end(), Comparator);

	pos[time] = { v[0].row, v[0].col };
	blocked[v[0].row][v[0].col] = true;
}

void print() {
	cout << "BLOCKED\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (blocked[i][j]) cout << 1 << " ";
			else cout << 0 << " ";
		}
		cout << "\n";
	}
	cout << "POS\n";
	for (int i = 1; i <= m; i++) {
		cout << "pos" << i << " : " << pos[i].first << " " << pos[i].second << " cvs" << i << " : " << cvs[i].first << " " << cvs[i].second << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 1) base_camp.push_back({ i, j });
		}
	}

	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		cvs[i] = { x, y };
	}

	for (int i = 1; i <= m; i++) {
		pos[i] = OUT_OF_GRID;
	}

	int time = 0;
	while (1) {
		if (allArrive()) break;
		time++;
		//cout << time << "\n";

		moveAll();
		for (int i = 1; i <= m; i++) {
			if (pos[i] == cvs[i]) blocked[pos[i].first][pos[i].second] = true;
		}
		//cout << "MOVEALL\n";
		//print();

		goBase(time);
		//cout << "GOBASE\n";
		//print();
	}

	cout << time << "\n";
	return 0;
}
