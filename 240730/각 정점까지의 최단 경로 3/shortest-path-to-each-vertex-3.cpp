#include <iostream>
#include <vector>
#include <tuple>

#define MAX_N 100

using namespace std;

int n, m;

int graph[MAX_N + 1][MAX_N + 1];
bool visited[MAX_N + 1];

int dist[MAX_N + 1];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		graph[x][y] = z;
	}

	for (int i = 1; i <= n; i++)
		dist[i] = (int)1e9;

	dist[1] = 0;

	for (int i = 1; i <= n; i++) {
		int min_index = -1;
		for (int j = 1; j <= n; j++) {
			if (visited[j])
				continue;

			if (min_index == -1 || dist[min_index] > dist[j])
				min_index = j;
		}

		visited[min_index] = true;

		for (int j = 1; j <= n; j++) {
			if (graph[min_index][j] == 0)
				continue;
			dist[j] = min(dist[j], dist[min_index] + graph[min_index][j]);
		}
	}

	for(int i = 2; i <= n; i++)
		cout << dist[i] << "\n";

	return 0;
}