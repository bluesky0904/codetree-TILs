/*
기사 : r, c, h, w, k(생존 여부 판단)
*/

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
int ori_k[MAX_N + 1], k[MAX_N + 1];

bool visited[MAX_N + 1];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool MovePossible(int idx, int d) {
	int new_r = r[idx] + dx[d], new_c = c[idx] + dy[d];

	if (new_r < 1 || new_r + h[idx] - 1 > l || new_c < 1 || new_c + w[idx] - 1 > l) return false;

	for (int i = new_r; i < new_r + h[idx]; i++) {
		for (int j = new_c; j < new_c + w[idx]; j++) {
			if (grid[i][j] == 2) return false;
		}
	}
	return true;
}

bool IsIntersect(int idx1, int idx2) {
	return !(nr[idx1] + h[idx1] - 1 < nr[idx2] || nr[idx2] + h[idx2] - 1 < nr[idx1] ||
		     nc[idx1] + w[idx1] - 1 < nc[idx2] || nc[idx2] + w[idx2] - 1 < nc[idx1]);
}

void GetDamage(int idx) {
	int cnt = 0;
	for (int i = r[idx]; i < r[idx] + h[idx]; i++) {
		for (int j = c[idx]; j < c[idx] + w[idx]; j++) {
			if (grid[i][j] == 1) cnt++;
		}
	}

	k[idx] -= cnt;
	if (k[idx] < 0) k[idx] = 0;
}

void MoveKnight(int idx, int d) {
	queue<int> q;
	fill(visited, visited + n + 1, false);

	for (int i = 1; i <= n; i++) {
		nr[i] = r[i];
		nc[i] = c[i];
	}

	q.push(idx);
	visited[idx] = true;
	while (!q.empty()) {
		int x = q.front(); q.pop();

		if (!MovePossible(x, d)) return;
		nr[x] += dx[d], nc[x] += dy[d];

		for (int i = 1; i <= n; i++) {
			if (i == x || visited[i] || k[i] == 0) continue;
			if (IsIntersect(x, i)) {
				q.push(i);
				visited[i] = true;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (!visited[i]) continue;
		r[i] = nr[i];
		c[i] = nc[i];
	}

	for (int i = 1; i <= n; i++) {
		if (i == idx) continue;
		if (!visited[i]) continue;
		GetDamage(i);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> l >> n >> q;

	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= l; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
		ori_k[i] = k[i];
	}

	while (q--) {
		int idx, d; cin >> idx >> d;
		if (k[idx] == 0) continue;
		MoveKnight(idx, d);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (k[i] == 0) continue;
		ans += (ori_k[i] - k[i]);
	}

	cout << ans << "\n";
	return 0;
}