#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Cluster {
	int cnt;
	int red_cnt;
	int cx;
	int cy;

	bool operator < (const Cluster& other) const {
		if (cnt != other.cnt) return cnt < other.cnt;
		if (red_cnt != other.red_cnt) return red_cnt > other.red_cnt;
		if (cx != other.cx) return cx < other.cx;
		return cy > other.cy;
	}
};

const int MAXN = 20;
const int INF = 1e9;

int score;
int n, m; // 격자의 크기 n, 빨간색 이외의 서로 다른 폭탄의 종류 m
int grid[MAXN + 10][MAXN + 10];
int next_grid[MAXN + 10][MAXN + 10];

bool visited[MAXN + 10][MAXN + 10];
vector<Cluster> v;
vector<pair<int ,int>> pos[MAXN + 10][MAXN + 10];

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

void print() {
	cout << "grid" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "v" << "\n";
	for (int i = 0; i < (int)v.size(); i++) {
		cout << i << " : " << v[i].cnt << " " << v[i].red_cnt << " " << v[i].cx << " " << v[i].cy << "\n";
	}
	cout << "pos" << "\n";
	for (int i = 0; i < (int)v.size(); i++) {
		cout << i << " : ";
		for (int j = 0; j < (int)pos[v[i].cx][v[i].cy].size(); j++) {
			cout << "{ ";
			cout << pos[v[i].cx][v[i].cy][j].first << " " << pos[v[i].cx][v[i].cy][j].second;
			cout << " } ";
		}
		cout << "\n";
	}

	cout << "\n";

	cout << "score : " << score << "\n";
}

bool inRange(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < n);
}

void BFS(int x, int y) {
	int cnt = 1;
	int red_cnt = 0;
	int criteria_x = x;
	int criteria_y = y;

	int num = grid[x][y];

	vector<pair<int, int>> tmp;
	queue<pair<int, int>> q;
	

	q.push({ x, y });
	visited[x][y] = true;
	tmp.push_back({ x, y });
	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];

			if (inRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == num || grid[nx][ny] == 0)) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
				tmp.push_back({ nx, ny });
				cnt++;
				if (grid[nx][ny] == 0) red_cnt++;
				else { // 기준점 설정하는거 주의!!!
					if (criteria_x < nx || (criteria_x == nx && criteria_y > ny)) {
						criteria_x = nx;
						criteria_y = ny;
					}
				}
			}
		}
	}
	if (cnt >= 2) {
		v.push_back({ cnt, red_cnt, criteria_x, criteria_y });
		for (pair<int, int> p : tmp) {
			pos[criteria_x][criteria_y].push_back(p);
		}
	}
}

void findMaxCluster() {
	v.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			pos[i][j].clear();
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if(grid[i][j] == 0) visited[i][j] = 0;
				}
			}

			if (grid[i][j] != -2 && grid[i][j] != -1 && grid[i][j] != 0 && !visited[i][j]) BFS(i, j);
		}
	}
}

void gravityGrid() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[i][j] = -2;
		}
	}

	for (int j = 0; j < n; j++) {
		int idx = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (grid[i][j] == -2) continue;
			else if (grid[i][j] == -1) {
				next_grid[i][j] = -1;
				idx = i - 1;
			}
			else {
				next_grid[idx][j] = grid[i][j];
				idx--;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

void removeCluster() {
	sort(v.begin(), v.end());
	int sz = (int)v.size();
	int criteria_x = v[sz - 1].cx;
	int criteria_y = v[sz - 1].cy;
	int cnt = v[sz - 1].cnt;
	for (int i = 0; i < (int)pos[criteria_x][criteria_y].size(); i++) {
		int x = pos[criteria_x][criteria_y][i].first;
		int y = pos[criteria_x][criteria_y][i].second;

		grid[x][y] = -2;
	}
	score += cnt * cnt;

	gravityGrid();
}

void rotateGrid() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_grid[n - j - 1][i] = grid[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	//print();
	score = 0;
	for (int turn = 1;; turn++) {
		//cout << "turn : " << turn << "\n";

		//cout << "findMaxCluster" << "\n";
		findMaxCluster();
		//print();
		if (v.empty()) break;
		
		//cout << "removeCluster" << "\n";
		removeCluster();
		//print();
		
		//cout << "rotateGrid" << "\n";
		rotateGrid();
		//print();
	
		//cout << "gravityGrid" << "\n";
		gravityGrid();
		//print();
	}

	cout << score << "\n";
	return 0;
}