#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 100000

int n;
int max_dist, max_index;
vector<pair<int, int>> edges[MAX_N + 1];
bool visited[MAX_N + 1];

void DFS(int vertex, int dist) {
	for (int i = 0; i < (int)edges[vertex].size(); i++) {
		int v, d;
		tie(v, d) = edges[vertex][i];
		if (!visited[v]) {
			visited[v] = true;
			if (max_dist < d + dist) {
				max_dist = d + dist;
				max_index = v;
			}
			DFS(v, dist + d);
		}
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n - 1; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		edges[v1].push_back(make_pair(v2, d));
		edges[v2].push_back(make_pair(v1, d));
	}

	max_index = 0, max_dist = 0;
	visited[1] = true;
	DFS(1, 0);

	fill(visited, visited + MAX_N + 1, false);
	max_dist = 0;
	visited[max_index] = true;
	DFS(max_index, 0);

	cout << max_dist << "\n";
	return 0;
}