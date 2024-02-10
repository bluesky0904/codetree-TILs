#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

#define MAX_N 20

int n;
int ans;
int grid[MAX_N][MAX_N];
int explode_grid[MAX_N][MAX_N];
vector<pair<int, int>> explode_pair;

pair<int, int> explode_type[3][5] = {
	{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}},
	{{0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1}},
	{{0 ,0}, {-1, 1}, {-1, -1}, {1, -1}, {1, 1}}
};

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
		tie(dx, dy) = explode_type[type][i];
		int nx = x + dx, ny = y + dy;
		if (InRange(nx, ny)) explode_grid[nx][ny]++;
	}
}

void RestoreExplodeGrid(int x, int y, int type) {
	for (int i = 0; i < 5; i++) {
		int dx, dy;
		tie(dx, dy) = explode_type[type][i];
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
		int x = explode_pair[cnt].first, y = explode_pair[cnt].second;
		ExplodeExplodeGrid(x, y, i);
		Explode(cnt + 1);
		RestoreExplodeGrid(x, y, i);
	}
	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 1) explode_pair.push_back(make_pair(i, j));
		}
	}

	Explode(0);
	cout << ans << "\n";
}