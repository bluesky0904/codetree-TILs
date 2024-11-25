#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

#define MAX_N 1000
#define INF (long long)1e18

// {다음 노드, 버스 번호, 탑승 순서, 탑승료}
typedef struct {
	int next_idx, bus_num, order;
	long long fee;
}Edge;

// pair<최소 비용, 최소 시간> dist[노드번호][버스번호]
pair<long long, int> dist[MAX_N + 1][MAX_N + 1];
vector<Edge> graph[MAX_N + 1];
// 우선 순위 : {비용, 시간, 노드 번호, 버스 번호, 탑승 순서}
priority_queue<tuple<long long, int, int, int, int>, vector<tuple<long long, int, int, int, int>>, greater<>> pq;

int A, B, N;

int main() {
	cin >> A >> B >> N;

	// 그래프 받기
	for (int i = 1; i <= N; i++) {
		long long fee;
		int cnt;
		cin >> fee >> cnt;
		vector<int> vertices;
		for (int j = 0; j < cnt; j++) {
			int x; cin >> x;
			vertices.push_back(x);
		}

		for (int j = 0; j < cnt - 1; j++) {
			graph[vertices[j]].push_back({ vertices[j + 1], i, j + 1, fee });
		}
	}

	// 기본값 설정
	for (int i = 1; i <= MAX_N; i++) {
		for (int j = 1; j <= N; j++) {
			dist[i][j] = { INF, INF };
		}
	} 

	for (int i = 1; i <= N; i++) {
		dist[A][i] = { 0, 0 };
	}
	pq.push({ 0, 0, A, 0, 0 });

	// 다익스트라 알고리즘
	// pair<최소 비용, 최소 시간> dist[노드번호][버스번호]
	// 간선 : {다음 노드, 버스 번호, 탑승 순서, 탑승료}
	// 우선 순위 : {비용, 시간, 노드 번호, 버스 번호, 탑승 순서}
	while (!pq.empty()) {
		long long cur_fee;
		int cur_time, cur_idx, cur_bus, cur_order;
		tie(cur_fee, cur_time, cur_idx, cur_bus, cur_order) = pq.top();
		pq.pop();

		// if (dist[cur_num][cur_bus] != make_pair(cur_fee, cur_time)) continue;

		for (int i = 0; i < (int)graph[cur_idx].size(); i++) {
			int next_idx, next_bus, next_order;
			long long next_fee;
			next_idx = graph[cur_idx][i].next_idx;
			next_bus = graph[cur_idx][i].bus_num;
			next_order = graph[cur_idx][i].order;
			next_fee = graph[cur_idx][i].fee;

			long long new_fee = cur_fee;
			int new_time = cur_time + 1;

			if (cur_bus != next_bus) {
				new_fee += next_fee;
			}

			if (dist[next_idx][next_bus] > make_pair(new_fee, new_time)) {
				dist[next_idx][next_bus] = {new_fee, new_time};
				pq.push(make_tuple(new_fee, new_time, next_idx, next_bus, next_order));
			}
		}
	}

	pair<long long, int> ans = {INF, INF};
	for (int i = 1; i <= N; i++) {
		ans = min(ans, dist[B][i]);
	}

	if (ans.first == INF) cout << "-1 -1\n";
	else cout << ans.first << " " << ans.second << "\n";
	return 0;
}