// 간선의 정보를 입력받아서 해당 구조가 트리인지 판별하는 프로그램
// 트리일 경우 1, 트리가 아닐 경우 0

#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 10000

vector<int> edge[MAX_N + 1];
bool is_node[MAX_N + 1];
bool visited[MAX_N + 1];
int parent[MAX_N + 1];

int m;
int root;

void DFS(int root) {
	if (visited[root]) return;

	for (int i = 0; i < (int)edge[root].size(); i++) {
		int next_idx = edge[root][i];

		if (visited[next_idx]) continue;
		DFS(next_idx);
		visited[next_idx] = true;
	}
	visited[root] = true;
}

int main() {
	cin >> m;
	fill(is_node, is_node + MAX_N + 1, false);
	fill(parent, parent + MAX_N + 1, -1);

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		if (i == 0) root = a;
		is_node[a] = true;
		is_node[b] = true;
		if (parent[b] == -1) {
			parent[b] = a;
		}
		else {
			cout << 0 << "\n";
			return 0;
		}
		edge[a].push_back(b);
	}

	int x;
	while (parent[root] != -1) {
		x = parent[root];
		root = x;
	}

	int root_count = 0;
	for (int i = 0; i <= MAX_N; i++) {
		if (!is_node[i]) continue;
		if (parent[i] == -1) root_count++;
	}
	if (root_count != 1) {
		cout << 0 << "\n";
		return 0;
	}

	fill(visited, visited + MAX_N + 1, false);
	DFS(root);

	for (int i = 0; i <= MAX_N; i++) {
		if (!is_node[i]) continue;
		if (!visited[i]) {
			cout << 0 << "\n";
			return 0;
		}
	}

	cout << 1 << "\n";
	return 0;
}