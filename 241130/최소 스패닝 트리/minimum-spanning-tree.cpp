#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 10000

int n, m;
vector<pair<int, int>> edge[MAX_N + 1];
vector<tuple<int, int, int>> edges;
int uf[MAX_N + 1];

int Find(int x){
	if (uf[x] == x) return x;
	int root_node = Find(uf[x]);
	uf[x] = root_node;
	return root_node;
}

void Union(int x, int y) {
	int X = Find(x), Y = Find(y);
	if (X != Y) {
		uf[X] = Y;
	}
}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		edge[v1].push_back({ v2,d });
		edge[v2].push_back({ v1,d });
		edges.push_back(make_tuple(d, v1, v2));
	}

	vector<int> mst;
	sort(edges.begin(), edges.end());
	for (int i = 1; i <= n; i++)
		uf[i] = i;

	int edge_count = 0;
	int idx = 0;
	while (1) {
		if (edge_count == n - 1) break;
		int d, v1, v2;
		tie(d, v1, v2) = edges[idx++];
		if (Find(v1) != Find(v2)) {
			mst.push_back(d);
			Union(v1, v2);
			edge_count++;
		}
	}

	int weight_sum = 0;
	for (int i = 0; i < (int)mst.size(); i++) {
		weight_sum += mst[i];
	}
	cout << weight_sum << "\n";
	return 0;
}