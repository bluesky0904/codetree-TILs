#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 10000
#define MAX_M 100000

vector<tuple<int, int, int>> edge;
int n, m;
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
	for (int i = 0; i < m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		edge.push_back(make_tuple(d, v1, v2));
	}

	sort(edge.begin(), edge.end());

	for (int i = 1; i <= n; i++)
		uf[i] = i;

	int ans = 0;
	for (int i = 0; i < m; i++) {
		int d, v1, v2;
		tie(d, v1, v2) = edge[i];
		if (Find(v1) != Find(v2)) {
			ans += d;
			Union(v1, v2);
		}
	}

	cout << ans << "\n";
	return 0;
}