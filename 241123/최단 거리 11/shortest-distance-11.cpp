#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

#define MAX_N 1000

int dist[MAX_N + 1];
vector<pair<int, int>> graph[MAX_N + 1];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

int n, m, A, B;

int main() {
	cin >> n >> m;

	for (int i = 1; i <= m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		graph[v1].push_back(make_pair(v2, d));
		graph[v2].push_back(make_pair(v1, d));
	}

	for (int i = 1; i <= n; i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	cin >> A >> B;

	fill(dist, dist + MAX_N + 1, (int)1e9);

	dist[B] = 0;
	pq.push(make_pair(0, B));
	while (!pq.empty()) {
		int min_dist, min_index;
		tie(min_dist, min_index) = pq.top();
		pq.pop();

		if (min_dist != dist[min_index]) continue;

		for (int i = 0; i < (int)graph[min_index].size(); i++) {
			int target_index, target_dist;
			tie(target_index, target_dist) = graph[min_index][i];

			int new_dist = min_dist + target_dist;
			if (dist[target_index] > new_dist) {
				dist[target_index] = new_dist;
				pq.push(make_pair(new_dist, target_index));
			}
		}
	}

	cout << dist[A] << "\n";

	int x = A;
	cout << x << " ";
	while (x != B) {
		for (int i = 0; i < (int)graph[x].size(); i++) {
			int target_index, target_dist;
			tie(target_index, target_dist) = graph[x][i];

			if (dist[target_index] + target_dist == dist[x]) {
				x = target_index;
				break;
			}
		}
		cout << x << " ";
	}
	return 0;
}