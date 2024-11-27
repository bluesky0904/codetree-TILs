/*
		1
	*2		3
			4
			*5
*/

#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000

vector<int> edge[MAX_N + 1];
bool visited[MAX_N + 1];
int parent[MAX_N + 1];

int n;
int total_depth = 0;

void DFS(int x, int depth) {
	bool is_leaf = true;
	for (int i = 0; i < (int)edge[x].size(); i++) {
		int next_x = edge[x][i];

		if (visited[next_x]) continue;

		visited[next_x] = true;
		is_leaf = false;

		DFS(next_x, depth + 1);
	}
	if (is_leaf) total_depth += depth;
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		parent[v2] = v1;
		edge[v1].push_back(v2);
		edge[v2].push_back(v1);
	}

	fill(visited, visited + MAX_N + 1, false);
	visited[1] = true;
	DFS(1, 0);

	if (total_depth % 2 == 0) cout << 0 << "\n";
	else cout << 1 << "\n";
	return 0;
}