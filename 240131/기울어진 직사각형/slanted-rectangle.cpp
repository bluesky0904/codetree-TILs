#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n;
int grid[MAX_N][MAX_N];
int dx[DIR_NUM] = {-1, -1, 1, 1};
int dy[DIR_NUM] = {1, -1, -1, 1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int GetRecSum(int x, int y, int w, int h) {
	int rec_sum = 0;
	int cnt[DIR_NUM] = { w, h, w, h };

	for (int i = 0; i < DIR_NUM; i++) {
		for (int j = 0; j < cnt[i]; j++) {
			x += dx[i], y += dy[i];
			if (!InRange(x, y)) return 0;
			rec_sum += grid[x][y];
		}
	}
	return rec_sum;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int width = 1; width < n; width++) {
				for (int height = 1; height < n; height++) {
					ans = max(ans, GetRecSum(i, j, width, height));
				}
			}
		}
	}

	cout << ans << "\n";
}