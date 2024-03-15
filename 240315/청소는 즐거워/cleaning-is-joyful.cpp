#include <iostream>
using namespace std;

#define MAX_N 499
#define DIR_NUM 4

int n;
int ans = 0;

int grid[MAX_N][MAX_N];

int dx[DIR_NUM] = {0,1,0,-1};
int dy[DIR_NUM] = {-1,0,1,0};

bool Finish(int x, int y) {
	return x == 0 && y == 0;
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void MoveDust(int x, int y, int dir) {
	int for_a = 0;
	if (InRange(x + dx[(dir+3)%4] * 2 , y + dy[(dir + 3) % 4] * 2)) {
		grid[x + dx[(dir + 3) % 4] * 2][y + dy[(dir + 3) % 4] * 2] += int(grid[x][y] * 0.02);
	}
	else ans += int(grid[x][y] * 0.02);
	for_a += int(grid[x][y] * 0.02);

	if (InRange(x + dx[dir] + dx[(dir+3)%4], y + dy[dir] + dy[(dir + 3)%4])) {
		grid[x + dx[dir] + dx[(dir + 3) % 4]][y + dy[dir] + dy[(dir + 3) % 4]] += int(grid[x][y] * 0.1);
	}
	else ans += int(grid[x][y] * 0.1);
	for_a += int(grid[x][y] * 0.1);

	if (InRange(x + dx[(dir + 3) % 4], y + dy[(dir + 3) % 4])) {
		grid[x + dx[(dir + 3) % 4]][y + dy[(dir + 3) % 4]] += int(grid[x][y] * 0.07);
	}
	else ans += int(grid[x][y] * 0.07);
	for_a += int(grid[x][y] * 0.07);

	if (InRange(x + dx[(dir+2)%4] + dx[(dir + 3) % 4], y + dy[(dir+2)%4] + dy[(dir + 3) % 4])) {
		grid[x + dx[(dir + 2) % 4] + dx[(dir + 3) % 4]][y + dy[(dir + 2) % 4] + dy[(dir + 3) % 4]] += int(grid[x][y] * 0.01);
	}
	else ans += int(grid[x][y] * 0.01);
	for_a += int(grid[x][y] * 0.01);

	if (InRange(x + dx[dir] * 2, y + dy[dir] * 2)) {
		grid[x + dx[dir] * 2][y + dy[dir] * 2] += int(grid[x][y] * 0.05);
	}
	else ans += int(grid[x][y] * 0.05);
	for_a += int(grid[x][y] * 0.05);

	if (InRange(x + dx[dir] + dx[(dir + 1) % 4], y + dy[dir] + dy[(dir + 1) % 4])) {
		grid[x + dx[dir] + dx[(dir + 1) % 4]][y + dy[dir] + dy[(dir + 1) % 4]] += int(grid[x][y] * 0.1);
	}
	else ans += int(grid[x][y] * 0.1);
	for_a += int(grid[x][y] * 0.1);

	if (InRange(x + dx[(dir + 1) % 4], y + dy[(dir + 1) % 4])) {
		grid[x + dx[(dir + 1) % 4]][y + dy[(dir + 1) % 4]] += int(grid[x][y] * 0.07);
	}
	else ans += int(grid[x][y] * 0.07);
	for_a += int(grid[x][y] * 0.07);
	
	if (InRange(x + dx[(dir + 1) % 4] + dx[(dir + 2) % 4], y + dy[(dir + 1) % 4] + dy[(dir + 2) % 4])) {
		grid[x + dx[(dir + 1) % 4] + dx[(dir + 2) % 4]][y + dy[(dir + 1) % 4] + dy[(dir + 2) % 4]] += int(grid[x][y] * 0.01);
	}
	else ans += int(grid[x][y] * 0.01);
	for_a += int(grid[x][y] * 0.01);

	if (InRange(x + dx[(dir + 1) % 4] * 2, y + dy[(dir + 1) % 4] * 2)) {
		grid[x + dx[(dir + 1) % 4] * 2][y + dy[(dir + 1) % 4] * 2] += int(grid[x][y] * 0.02);
	}
	else ans += int(grid[x][y] * 0.02);
	for_a += int(grid[x][y] * 0.02);

	if (InRange(x + dx[dir], y + dy[dir])) {
		grid[x + dx[dir]][y + dy[dir]] += (grid[x][y] - for_a);
	}
	else ans += (grid[x][y] - for_a);

	grid[x][y] = 0;
}

void Print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << ans << "\n";
	cout << "--------------------------------------\n";
}

void Simulate() {
	int cx = n / 2, cy = n / 2, dir = 0, dis = 1;
	while (true) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < dis; j++) {
				cx += dx[dir], cy += dy[dir];
				MoveDust(cx, cy, dir);
				//Print();
				if (Finish(cx, cy)) return;
			}
			dir = (dir + 1) % 4;
		}
		dis++;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	Simulate();
	cout << ans << "\n";
	return 0;
}