#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

#define MAX_N 1000
int dist[MAX_N + 1];
vector<pair<int, int>> graph[MAX_N + 1];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
int path[MAX_N + 1];
int n, m, A, B;

int main() {
	fill(path, path + MAX_N + 1, -1);

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		graph[v1].push_back(make_pair(v2, d));
		graph[v2].push_back(make_pair(v1, d));
	}
	cin >> A >> B;

	fill(dist, dist + MAX_N + 1, (int)1e9);

	dist[A] = 0;
	pq.push(make_pair(0, A));
	while (!pq.empty()) {
		int min_dist, min_index;
		tie(min_dist, min_index) = pq.top();
		pq.pop();

		if (min_dist != dist[min_index]) continue;

		for (int j = 0; j < (int)graph[min_index].size(); j++) {
			int target_dist, target_index;
			tie(target_index, target_dist) = graph[min_index][j];
			int new_dist = min_dist + target_dist;
			if (dist[target_index] > new_dist) {
				dist[target_index] = new_dist;
				path[target_index] = min_index;
				pq.push(make_pair(new_dist, target_index));
 			}
		}
	}

	cout << dist[B] << "\n";
	int x = B; // 이 부분에 도착지가 들어가야함. 실수 주의
	vector<int> vertices;
	while (x != -1) {
		vertices.push_back(x);
		x = path[x];
	}
	for (int i = (int)vertices.size() - 1; i >= 0; i--) {
		cout << vertices[i] << " ";
	}
	cout << "\n";

	return 0;
}