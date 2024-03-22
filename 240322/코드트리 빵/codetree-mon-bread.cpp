#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

#define MAX_N 15
#define MAX_M 30
#define DIR_NUM 4
#define EMPTY make_pair(-1,-1)

int n, m;
int t = 0;
int dx[DIR_NUM] = {-1,0,0,1};
int dy[DIR_NUM] = {0,-1,1,0};

pair<int, int> pos[MAX_M + 1]; // 사람들 위치
pair<int, int> store[MAX_M + 1]; // 편의점 위치

bool visited[MAX_N][MAX_N ]; // 편의점으로부터 최단거리 베이스캠프
int step[MAX_N][MAX_N];

int grid[MAX_N][MAX_N]; // 베이스캠프 위치
bool NonPass[MAX_N][MAX_N]; // 통행가능여부 체크

void VisitedInit() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

bool CheckFinish() {
	for (int i = 1; i <= m; i++) {
		if (pos[i] != store[i]) return false;
	}
	return true;
}

void BFS(pair<int, int> start_pos) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
			step[i][j] = 0;
		}
	}

	queue<pair<int, int>> q;
	int sx = start_pos.first, sy = start_pos.second;
	q.push(start_pos);
	visited[sx][sy] = true;
	step[sx][sy] = 0;

	while (!q.empty()) {
		pair<int, int> curr_pos = q.front();
		q.pop();

		int x = curr_pos.first, y = curr_pos.second;
		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && !NonPass[nx][ny]) {
				visited[nx][ny] = true;
				step[nx][ny] = step[x][y] + 1;
				q.push(make_pair(nx, ny));
			}
		}
	}
}

void GoBase(int t) {
	BFS(store[t]);
	int mx = -1, my = -1;
	int min_dis = INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 1 && visited[i][j] &&  min_dis > step[i][j]) {
				mx = i;
				my = j;
				min_dis = step[i][j];
			}
		}
	}
	pos[t] = make_pair(mx, my);
	NonPass[mx][my] = true;
}

pair<int, int> GetNextPos(int x, int y, int num) {

	BFS(store[num]);
	int mx = -1, my = -1;
	int min_dis = INT_MAX;
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = x + dx[dir], ny = y + dy[dir];
		if (InRange(nx, ny) && visited[nx][ny] && min_dis > step[nx][ny]) {
			mx = nx;
			my = ny;
			min_dis = step[nx][ny];
		}
	}
	return make_pair(mx, my);
}

void GoStore() {
	for (int i = 1; i <= m; i++) {
		if (pos[i] == EMPTY || pos[i] == store[i]) continue;
		int x, y;
		tie(x, y) = pos[i];
		pos[i] = GetNextPos(x, y, i);
	}

	for (int i = 1; i <= m; i++) {
		if (pos[i] == store[i]) {
			int x, y;
			tie(x, y) = pos[i];
			NonPass[x][y] = true;
		}
	}
}

void Print() {
	cout << t << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << NonPass[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	
	for (int i = 1; i <= m; i++) {
		cout << "{" << pos[i].first << " " << pos[i].second << "}" << "\n";
	}
	cout << "--------------------------\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		store[i] = make_pair(x - 1, y - 1);
	}

	for (int i = 1; i <= m; i++) pos[i] = EMPTY;

	while (true) {
		t++;
		GoStore();
		//Print();
		if (CheckFinish()) break;

		if(t <= m) GoBase(t);
		//Print();
	}

	cout << t << "\n";
	return 0;
}