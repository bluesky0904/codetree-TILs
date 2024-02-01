#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 20
int n, m;
int grid[MAX_N][MAX_N];

bool IsPositiveRec(int sx, int sy, int ex, int ey) {
	for (int i = sx; i <= ex; i++) {
		for (int j = sy; j <= ey; j++) {
			if (grid[i][j] <= 0) return false;
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	int ans = -1;
	for (int sx = 0; sx < n; sx++) {
		for (int sy = 0; sy < m; sy++) {
			for (int ex = sx; ex < n; ex++) {
				for (int ey = sy; ey < m; ey++) {
					if (IsPositiveRec(sx, sy, ex, ey)) {
						ans = max(ans, (ex - sx + 1) * (ey - sy + 1));
					}
				}
			}
		}
	}
	cout << ans << "\n";

	return 0;
}