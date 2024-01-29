#include <iostream>
#include <tuple>

#define MAX_N 20
#define DIR_NUM 8

using namespace std;

int n, m;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> FindPos(int num) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (grid[i][j] == num) return make_pair(i, j);
}

pair<int, int> NextPos(pair<int, int> pos) {
	int dx[DIR_NUM] = {-1,-1,-1,0,0,1,1,1};
	int dy[DIR_NUM] = {-1,0,1,-1,1,-1,0,1};

	int x, y;
	tie(x, y) = pos;

	int max_val = -1;
	pair<int, int> max_pos;
	for (int i = 0; i < DIR_NUM; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (InRange(nx, ny) && grid[nx][ny] > max_val) {
			max_val = grid[nx][ny];
			max_pos = make_pair(nx, ny);
		}
	}

	return max_pos;
}

void Swap(pair<int, int> pos, pair<int, int> next_pos) {
	int x, y, nx, ny;
	tie(x, y) = pos;
	tie(nx, ny) = next_pos;

	int temp = grid[x][y];
	grid[x][y] = grid[nx][ny];
	grid[nx][ny] = temp;
}

void Simulate() {
	for (int num = 1; num <= n * n; num++) {
		pair<int, int> pos = FindPos(num);
		pair<int, int> next_pos = NextPos(pos);
		Swap(pos, next_pos);
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> grid[i][j];

	while (m--)
		Simulate();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << grid[i][j] << " ";
		cout << "\n";
	}

	return 0;
}