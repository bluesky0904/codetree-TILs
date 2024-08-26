#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

#define MAX 101
#define DIR_NUM 4

int n;
int x, y, d, g;

int grid[MAX][MAX];

int dx[DIR_NUM] = { 0, -1, 0, 1 };
int dy[DIR_NUM] = { 1, 0, -1, 0 };

void drawDragonCurve(int x, int y, int d, int g) {
	vector<int> directions;
	directions.push_back(d);

	for (int i = 0; i < g; i++) {
		int size = directions.size();
		for (int j = size - 1; j >= 0; j--) {
			directions.push_back((directions[j] + 1) % 4);
		}
	}

	grid[x][y] = 1;
	for (int i = 0; i < directions.size(); i++) {
		x += dx[directions[i]];
		y += dy[directions[i]];
		grid[x][y] = 1;
	}
}

int countSquare() {
	int rslt = 0;
	for (int i = 0; i < MAX - 1; i++) {
		for (int j = 0; j < MAX - 1; j++) {
			if (grid[i][j] && grid[i][j + 1] && grid[i + 1][j] && grid[i + 1][j + 1])
				rslt++;
		}
	}
	return rslt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> d >> g;
		drawDragonCurve(x, y, d, g);
	}
	
	cout << countSquare() << '\n';
	return 0;
}