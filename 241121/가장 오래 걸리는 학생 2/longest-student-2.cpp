#include<iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

#define MAX_N 100000

int dist[MAX_N + 1];
vector<pair<int, int>> graph[MAX_N + 1];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

int n, m;
int ans = 0;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		graph[v2].push_back(make_pair(v1, d));
	}

	for (int i = 1; i <= n; i++) {
		dist[i] = (int)1e9;
	}

	dist[n] = 0;
	pq.push(make_pair(0, n));
	while (!pq.empty()) {
		int min_dist, min_index;
		tie(min_dist, min_index) = pq.top();
		pq.pop();

		if (min_dist != dist[min_index]) continue;

		for (int j = 0; j < (int)graph[min_index].size(); j++) {
			int target_dist, target_index;
			tie(target_index, target_dist) = graph[min_index][j]; // 이 위치 실수하기 딱 좋음. target_index랑 target_dist 위치 주의하기
			int new_dist = dist[min_index] + target_dist;
			if (dist[target_index] > new_dist) {
				dist[target_index] = new_dist;
				pq.push(make_pair(new_dist, target_index));
			}
		}
	}

	for (int i = 1; i < n; i++) {
		if (dist[i] == (int)1e9) dist[i] = -1;
	}

	for (int i = 1; i < n; i++) {
		ans = max(ans, dist[i]);
	}

	cout << ans << "\n";
	return 0;
}