#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 90000

int n, m;
vector<tuple<int, int, int>> edge;
int uf[MAX_N + 1];

int Find(int x) {
	if (uf[x] == x) return x;
	int root_node = Find(uf[x]);
	uf[x] = root_node;
	return root_node;
}

void Union(int x, int y) {
	int X = Find(x), Y = Find(y);
	if (X != Y) uf[X] = Y;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++) {
			int x = (i - 1) * m + j;
			int y = (i - 1) * m + j + 1;
			int d; cin >> d;
			edge.push_back(make_tuple(d, x, y));
		}
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			int x = (i - 1) * m + j;
			int y = (i - 1 + 1) * m + j;
			int d; cin >> d;
			edge.push_back(make_tuple(d, x, y));
		}
	}

	sort(edge.begin(), edge.end());
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int idx = (i - 1) * m + j;
			uf[idx] = idx;
		}
	}

	int total_weight = 0;
	for (int i = 0; i < (int)edge.size(); i++) {
		int d, x, y;
		tie(d, x, y) = edge[i];

		if (Find(x) != Find(y)) {
			Union(x, y);
			total_weight += d;
		}
	}

	cout << total_weight << "\n";
	return 0;
}