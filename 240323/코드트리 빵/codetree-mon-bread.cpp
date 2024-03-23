#include <iostream>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

#define MAX_N 15
#define MAX_M 30
#define EMPTY make_pair(-1, -1)
#define DIR_NUM 4

int n, m;
int t = 0;

int grid[MAX_N][MAX_N];
bool NonPass[MAX_N][MAX_N];
pair<int, int> pos[MAX_M];
pair<int, int> store[MAX_M];

bool visited[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];

int dx[DIR_NUM] = { -1,0,0,1 };
int dy[DIR_NUM] = { 0,-1,1,0 };

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void BFS(pair<int, int> start_pos) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
			dist[i][j] = 0;
		}
	}

	queue<pair<int, int>> q;
	q.push(start_pos);
	visited[start_pos.first][start_pos.second] = true;
	dist[start_pos.first][start_pos.second] = 0;
	
	while (!q.empty()) {
		int cx = q.front().first, cy = q.front().second;
		q.pop();

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && !NonPass[nx][ny]) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
				dist[nx][ny] = dist[cx][cy] + 1;
			}
		}
	}
}

pair<int, int> GetNextPos(int x, int y, int num) {
	BFS(store[num]);

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
	for (int i = 0; i < m; i++) {
		if (pos[i] == EMPTY || pos[i] == store[i]) continue;
		int x, y;
		tie(x, y) = pos[i];
		pos[i] = GetNextPos(x, y, i);
	}

	for (int i = 0; i < m; i++) {
		if(pos[i] == store[i]) NonPass[pos[i].first][pos[i].second] = true;
	}
}

void GoBase(int num) {
	BFS(store[num]);

	int mx = -1, my = -1;
	int min_dist = INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 1 && visited[i][j] && min_dist > dist[i][j]) {
				mx = i;
				my = j;
				min_dist = dist[i][j];
			}
		}
	}

	pos[num] = make_pair(mx, my);
	NonPass[mx][my] = true;
}

void Print() {
	cout << t << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << NonPass[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "------------------------------\n";
}

bool Finish() {
	for (int i = 0; i < m; i++) if (pos[i] != store[i]) return false;
		return true;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		store[i] = make_pair(x - 1, y - 1);
	}

	for (int i = 0; i < m; i++) pos[i] = EMPTY;
	
	while (true) {
		t++;
		GoStore();
		//Print();
		if (t <= m) GoBase(t - 1);
		//Print();

		if (Finish()) break;
	}

	cout << t << "\n";
	return 0;
}