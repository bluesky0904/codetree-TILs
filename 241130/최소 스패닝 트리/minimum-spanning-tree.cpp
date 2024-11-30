#include <iostream>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 10000
#define MAX_M 100000

int n, m;
tuple<int, int, int> edge[MAX_M + 1];
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
	for (int i = 1; i <= m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		edge[i] = make_tuple(d, v1, v2);
	}

	int total_weight = 0;
	sort(edge + 1, edge + m + 1);
	for (int i = 1; i <= n; i++)
		uf[i] = i;

	for (int i = 1; i <= m; i++) {
		int d, v1, v2;
		tie(d, v1, v2) = edge[i];
		if (Find(v1) != Find(v2)) {
			Union(v1, v2);
			total_weight += d;
		}
	}

	cout << total_weight << "\n";
	return 0;
}