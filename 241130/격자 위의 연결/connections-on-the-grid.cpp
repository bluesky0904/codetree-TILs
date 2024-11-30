#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 300
#define MAX_M 300

int n, m;
vector<tuple<int, int, int, int, int>> edge;
pair<int, int> uf[MAX_N + 1][MAX_N + 1];

pair<int, int> Find(int x, int y) {
	if (uf[x][y].first == x && uf[x][y].second == y) return make_pair(x, y);
	pair<int, int> root_node = Find(uf[x][y].first, uf[x][y].second);
	uf[x][y] = root_node;
	return root_node;
}

void Union(int x1, int y1, int x2, int y2) {
	int X1, Y1, X2, Y2;
	tie(X1, Y1) = Find(x1, y1);
	tie(X2, Y2) = Find(x2, y2);
	if (tie(X1, Y1) != tie(X2, Y2)) uf[X1][Y1] = { X2, Y2 };
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m - 1; j++) {
			int d; cin >> d;
			edge.push_back(make_tuple(d, i, j, i, j + 1));
		}
	}

	for (int i = 1; i <= n -1; i++) {
		for (int j = 1; j <= m; j++) {
			int d; cin >> d;
			edge.push_back(make_tuple(d, i, j, i + 1, j));
		}
	}

	sort(edge.begin(), edge.end());
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			uf[i][j] = { i, j };
		}
	}

	int total_weight = 0;
	for (int i = 0; i < (int)edge.size(); i++) {
		int d, x1, y1, x2, y2;
		tie(d, x1, y1, x2, y2) = edge[i];

		if (Find(x1, y1) != Find(x2, y2)) {
			Union(x1, y1, x2, y2);
			total_weight += d;
		}
	}

	cout << total_weight << "\n";
	return 0;
}