#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 10
#define MAX_M 5

int n, m, c;
int ans;
int max_val;
int grid[MAX_N][MAX_N];
int a[MAX_M];

bool Possible(int sx1, int sy1, int sx2, int sy2) {
	if (sy1 + m - 1 >= n || sy2 + m - 1 >= n) return false;
	if (sx1 == sx2) return sy1 + m - 1 < sy2 || sy2 + m - 1 < sy1;
	return true;
}

void FindMaxSum(int cur_idx, int cur_weight, int cur_val) {
	if (cur_idx == m) {
		if (cur_weight <= c) max_val = max(max_val, cur_val);
		return;
	}

	FindMaxSum(cur_idx + 1, cur_weight, cur_val);
	FindMaxSum(cur_idx + 1, cur_weight + a[cur_idx], cur_val + a[cur_idx] * a[cur_idx]);
}

int FindMax(int sx, int sy) {
	for (int i = sy; i <= sy + m - 1; i++) a[i - sy] = grid[sx][i];
	max_val = 0;
	FindMaxSum(0, 0, 0);
	return max_val;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	for (int sx1 = 0; sx1 < n; sx1++) {
		for (int sy1 = 0; sy1 < n; sy1++) {
			for (int sx2 = 0; sx2 < n; sx2++) {
				for (int sy2 = 0; sy2 < n; sy2++) {
					if (Possible(sx1, sy1, sx2, sy2)) ans = max(ans, FindMax(sx1, sy1) + FindMax(sx2, sy2));
				}
			}
		}
	}
	cout << ans << "\n";
}