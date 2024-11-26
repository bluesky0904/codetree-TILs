#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000

int n;
vector<int> graph[MAX_N + 1];
int parent[MAX_N + 1];
bool visited[MAX_N + 1];

void traversal(int root) {
	for (int i = 0; i < (int)graph[root].size(); i++) {
		int y = graph[root][i];
		if (visited[y]) continue;
		visited[y] = true;
		parent[y] = root;
		traversal(y);
	}
}

int main() {
	cin >> n;
	for (int i = 2; i <= n; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}

	fill(visited, visited + MAX_N + 1, false);
	visited[1] = true;
	traversal(1);
	for (int i = 2; i <= n; i++) {
		cout << parent[i] << "\n";
	}
}