#include <iostream>
#include <queue>
using namespace std;

#define MAX_L 40
#define MAX_N 30
#define DIR_NUM 4

int l, n, q;
int grid[MAX_L + 1][MAX_L + 1];
int r[MAX_N + 1], c[MAX_N + 1];
int nr[MAX_N + 1], nc[MAX_N + 1];
int h[MAX_N + 1], w[MAX_N + 1];
int k[MAX_N + 1], bef_k[MAX_N + 1], dmg[MAX_N + 1];
bool visited[MAX_N + 1];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool MoveCheck(int idx, int dir) {
	for (int i = 1; i <= n; i++) {
		nr[i] = r[i];
		nc[i] = c[i];
		dmg[i] = 0;
		visited[i] = false;
	}

	queue<int> q;
	q.push(idx);
	visited[idx] = true;

	while (!q.empty()) {
		int x = q.front(); q.pop();
		nr[x] += dx[dir], nc[x] += dy[dir];
		if (nr[x] < 1 || nr[x] + h[x] - 1 > l || nc[x] < 1 || nc[x] + w[x] - 1 > l) return false;
		for (int i = nr[x]; i <= nr[x] + h[x] - 1; i++) {
			for (int j = nc[x]; j <= nc[x] + w[x] - 1; j++) {
				if (grid[i][j] == 1) dmg[x]++;
				if (grid[i][j] == 2) return false;
			}
		}

		for (int i = 1; i <= n; i++) {
			if (visited[i] || k[i] <= 0) continue;
			if (r[i] + h[i] - 1 < nr[x] || nr[x] + h[x] - 1 < r[i] || c[i] + w[i] - 1 < nc[x] || nc[x] + w[x] - 1 < c[i]) continue;
			q.push(i);
			visited[i] = true;
		}
	}
	dmg[idx] = 0;
	return true;
}

void MoveKnight(int idx, int dir) {
	if (k[idx] <= 0) return;

	if (MoveCheck(idx, dir)) {
		for (int i = 1; i <= n; i++) {
			r[i] = nr[i];
			c[i] = nc[i];
			k[i] -= dmg[i];
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> l >> n >> q;
	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= l; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
		bef_k[i] = k[i];
	}

	while (q--) {
		int i, d;
		cin >> i >> d;
		MoveKnight(i, d);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (k[i] > 0) {
			ans += (bef_k[i] - k[i]);
		}
	}
	cout << ans << "\n";
	return 0;
}