#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 100000
int n;
int max_dist;
int max_index;

vector<pair<int, int>> edges[MAX_N + 1];
bool visited[MAX_N + 1];

void Traversal(int x, int dist) {
	for (int i = 0; i < (int)edges[x].size(); i++) {
		int y, d;
		tie(y, d) = edges[x][i];
		if (!visited[y]) {
			visited[y] = true;
			if (max_dist < dist + d) {
				max_dist = dist + d;
				max_index = y;
			}
			Traversal(y, dist + d);
		}
	}
}

int main() {
	cin >> n;

	for (int i = 1; i <= n - 1; i++) {
		int x, y, d;
		cin >> x >> y >> d;

		edges[x].push_back(make_pair(y, d));
		edges[y].push_back(make_pair(x, d));
	}

	visited[1] = true;
	max_dist = 0;
	max_index = 0;
	Traversal(1, 0);
	int start_index = max_index;

	fill(visited, visited + MAX_N + 1, false);
	max_dist = 0;
	max_index = 0;
	visited[start_index] = true;
	Traversal(start_index, 0);

	cout << max_dist << "\n";
	return 0;
}