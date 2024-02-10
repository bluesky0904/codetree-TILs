#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

#define MAX_N 20
#define DIR_NUM 5

int n;
int ans;
int grid[MAX_N][MAX_N];
int explode_grid[MAX_N][MAX_N];

pair<int, int> bomb_shapes[3][5] = {
	{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}},
	{{-1, 0}, {1, 0}, {0, 0}, {0, -1}, {0, 1}},
	{{-1, -1}, {-1, 1}, {0, 0}, {1, -1},{1, 1}}
};

vector<pair<int, int>> explode_pair;

int CountExplodeGrid() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (explode_grid[i][j] > 0) cnt++;
		}
	}
	return cnt;
}

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void ExplodeExplodeGrid(int x, int y, int type) {
	for (int i = 0; i < 5; i++) {
		int dx, dy;
		tie(dx, dy) = bomb_shapes[type][i];
		int nx = x + dx, ny = y + dy;
		if (InRange(nx, ny)) explode_grid[nx][ny]++;
	}
}

void RestoreExplodeGrid(int x, int y, int type) {
	for (int i = 0; i < 5; i++) {
		int dx, dy;
		tie(dx, dy) = bomb_shapes[type][i];
		int nx = x + dx, ny = y + dy;
		if (InRange(nx, ny)) explode_grid[nx][ny]--;
	}
}

void Explode(int cnt) {
	if (cnt == explode_pair.size()) {
		ans = max(ans, CountExplodeGrid());
		return;
	}

	for (int i = 0; i < 3; i++) {
		ExplodeExplodeGrid(explode_pair[cnt].first, explode_pair[cnt].second, i);
		Explode(cnt + 1);
		RestoreExplodeGrid(explode_pair[cnt].first, explode_pair[cnt].second, i);
	}
	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 1) {
				explode_pair.push_back({ i, j });
			}
		}
	}

	Explode(0);
	cout << ans << "\n";
}