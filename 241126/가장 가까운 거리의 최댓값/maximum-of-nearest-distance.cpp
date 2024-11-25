#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 100000
#define INF (int)1e9

vector<pair<int, int>> graph[MAX_N + 1];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
int dist[MAX_N + 1];
int ans = 0;

int n, m, a, b, c;

int main() {
	cin >> n >> m >> a >> b >> c;
	for (int i = 1; i <= m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		graph[v1].push_back({ v2, d });
		graph[v2].push_back({ v1, d });
	}

	for (int i = 1; i <= n; i++) {
		int abc_dist = INF;
		if (i == a || i == b || i == c) continue;

		for (int i = 1; i <= n; i++)
			dist[i] = INF;

		dist[i] = 0;
		pq.push({ 0, i });
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
		
		abc_dist = min(abc_dist, dist[a]);
		abc_dist = min(abc_dist, dist[b]);
		abc_dist = min(abc_dist, dist[c]);

		ans = max(ans, abc_dist);
	}
	
	cout << ans << "\n";
	return 0;
}