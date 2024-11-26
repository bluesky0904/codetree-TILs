#include<iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <functional>
using namespace std;

#define MAX_N 100000
#define INF (int)1e9

vector<pair<int, int>> graph[MAX_N + 1];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
int dist[MAX_N + 1];

int n, m, a, b, c;

void dijkstra(int start) {
	fill(dist, dist + MAX_N + 1, INF);
	dist[start] = 0;
	pq.push({ 0, start });
	while (!pq.empty()) {
		int min_dist, min_idx;
		tie(min_dist, min_idx) = pq.top();
		pq.pop();

		if (dist[min_idx] != min_dist) continue;

		for (int j = 0; j < (int)graph[min_idx].size(); j++) {
			int target_idx, target_dist;
			tie(target_idx, target_dist) = graph[min_idx][j];

			int new_dist = min_dist + target_dist;
			if (dist[target_idx] > new_dist) {
				dist[target_idx] = new_dist;
				pq.push({ new_dist, target_idx });
			}
		}
	}
}

int main() {
	cin >> n >> m >> a >> b >> c;
	for (int i = 1; i <= m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		graph[v1].push_back({ v2, d });
		graph[v2].push_back({ v1, d });
	}

	int ans = 0;

	vector<int> min_dist_a(n + 1), min_dist_b(n + 1), min_dist_c(n + 1);
	dijkstra(a);
	copy(dist, dist + n + 1, min_dist_a.begin());
	dijkstra(b);
	copy(dist, dist + n + 1, min_dist_b.begin());
	dijkstra(c);
	copy(dist, dist + n + 1, min_dist_c.begin());

	for (int i = 1; i <= n; i++) {
		if (i == a || i == b || i == c) continue;
		int min_dist = min({ min_dist_a[i], min_dist_b[i], min_dist_c[i] });
		 ans = max(ans, min_dist);
	}

	cout << ans << "\n";
	return 0;
}