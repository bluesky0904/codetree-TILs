#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 1000

vector<pair<int, int>> edge[MAX_N + 1];
bool visited[MAX_N + 1];

int n, m;

int DFS(int start, int end, int dist) {
	visited[start] = true;
	if (start == end) return dist;

	for (int i = 0; i < (int)edge[start].size(); i++) {
		int next_idx, next_dist;
		tie(next_idx, next_dist) = edge[start][i];

		if (visited[next_idx]) continue;

		int rslt = DFS(next_idx, end, dist + next_dist);
		if (rslt != -1) return rslt;
	}
	return -1;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		edge[v1].push_back({ v2, d });
		edge[v2].push_back({ v1, d });
	}

	for (int i = 1; i <= m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		fill(visited, visited + n + 1, false);
		cout << DFS(v1, v2, 0) << "\n";
	}
	return 0;
}