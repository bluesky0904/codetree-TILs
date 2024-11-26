#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 100000

vector<pair<int, int>> graph[MAX_N + 1];
bool visited[MAX_N + 1];
int max_dist = 0;
int max_idx = 0;

int n;
void DFS(int vertex, int dist) {
	for (int i = 0; i < (int)graph[vertex].size(); i++) {
		int nv, nd;
		tie(nv, nd) = graph[vertex][i];
		if (visited[nv]) continue;
		visited[nv] = true;
		if (max_dist < dist + nd) {
			max_dist = dist + nd;
			max_idx = nv;
		}
		DFS(nv, dist + nd);
	}
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		graph[v1].push_back({ v2, d });
		graph[v2].push_back({ v1, d });
	}

	fill(visited, visited + MAX_N + 1, false);
	visited[1] = true;
	DFS(1, 0);

	fill(visited, visited + MAX_N + 1, false);
	visited[max_idx] = true;
	DFS(max_idx, 0);

	cout << max_dist << "\n";
	return 0;
}