#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
using namespace std;

#define DIR_NUM 4

int N;
vector<vector<char>> grid;
int dx[DIR_NUM] = {0,-1,0,1};
int dy[DIR_NUM] = {1,0,-1,0};

bool InRange(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

void Simulate(int x, int y) {
	set<tuple<int, int, int>> visited;
	int t = 0;
	int cx = x; int cy = y; int dir = 0; // dir 0 우 1 상 2 좌 3 하 
	while (true) {
		if (visited.find(make_tuple(cx, cy, dir )) != visited.end()) {
			cout << -1 << " ";
			return;
		}
		visited.insert(make_tuple(cx, cy, dir));
		if (InRange(cx + dx[dir], cy + dy[dir]) && grid[cx + dx[dir]][cy + dy[dir]] == '#') dir = (dir + 1) % 4;
		else if (!InRange(cx + dx[dir], cy + dy[dir])) {
			t++;
			break;
		}
		else if (InRange(cx + dx[dir], cy + dy[dir]) && grid[cx + dx[dir]][cy + dy[dir]] == '.' && grid[cx + dx[dir] + dx[(dir + 3) % 4]][cy + dy[dir] + dy[(dir + 3) % 4]] == '#') {
			cx += dx[dir];
			cy += dy[dir];
			t++;
		}
		else if (InRange(cx + dx[dir], cy + dy[dir]) && grid[cx + dx[dir]][cy + dy[dir]] == '.' && grid[cx + dx[dir] + dx[(dir + 3) % 4]][cy + dy[dir] + dy[(dir + 3) % 4]] == '.') {
			cx += dx[dir] + dx[(dir + 3) % 4];
			cy += dy[dir] + dy[(dir + 3) % 4];
			dir = (dir + 3) % 4;
			t+=2;
		}
	}

	cout << t << " ";
	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	int x, y; cin >> x >> y;
	x--; y--;
	grid.resize(N, vector<char>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> grid[i][j];
		}
		cin.ignore();
	}

	Simulate(x, y);

	return 0;
}