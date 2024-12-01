#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

#define MAX_N 200
int n, m;
pair<int, int> point[MAX_N + 1];
vector<tuple<double, int, int>> edge;
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

double GetDist(int idx1, int idx2) {
	int x1, y1, x2, y2;
	tie(x1, y1) = point[idx1];
	tie(x2, y2) = point[idx2];
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		int x, y;
		cin >> x >> y;
		point[i] = { x, y };
	}

	for (int i = 1; i <= n - 1; i++) {
		for (int j = i + 1; j <= n; j++) {
			double dist = GetDist(i, j);
			edge.push_back(make_tuple(dist, i, j));
		}
	}

	sort(edge.begin(), edge.end());
	for (int i = 1; i <= n; i++) {
		uf[i] = i;
	}

	for (int i = 1; i <= m; i++) {
		int idx1, idx2;
		cin >> idx1 >> idx2;
		Union(idx1, idx2);
	}

	double ans = 0;
	for (int i = 0; i < (int)edge.size(); i++) {
		double dist;
		int idx1, idx2;

		tie(dist, idx1, idx2) = edge[i];
		if (Find(idx1) != Find(idx2)) {
			Union(idx1, idx2);
			ans += dist;
		}
	}

	cout << fixed << setprecision(2) << ans << endl;
	return 0;
}