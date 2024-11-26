#include<iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 10000

int m;
int root;
bool is_tree = true;
vector<int> edge[MAX_N + 1]; // 트리
bool used[MAX_N + 1]; // 사용되는 노드
int deg[MAX_N + 1]; // 들어오는 간선 수
bool visited[MAX_N + 1]; // 방문 여부

void DFS(int idx) {
	visited[idx] = true;
	for (int i = 0; i < (int)edge[idx].size(); i++) {
		int next_idx = edge[idx][i];
		DFS(next_idx);
	}
}

int main() {
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int a, b; cin >> a >> b;
		used[a] = used[b] = true;
		deg[b]++;
		edge[a].push_back(b);
	}

	// 조건 1
	for (int i = 1; i <= MAX_N; i++) {
		if (used[i] && deg[i] == 0) {
			if (root != 0) {
				is_tree = false;
				break;
			}
			root = i;
		}
	}
	if (root == 0) is_tree = false;

	// 조건 2
	if (is_tree) {
		for (int i = 1; i <= MAX_N; i++) {
			if (used[i] && i != root && deg[i] != 1) {
				is_tree = false;
				break;
			}
		}
	}

	// 조건 3
	if (is_tree) {
		DFS(root);
		for (int i = 1; i <= MAX_N; i++) {
			if (used[i] && !visited[i]) {
				is_tree = false;
				break;
			}
		}
	}

	if (is_tree) cout << 1 << "\n";
	else cout << 0 << "\n";
	return 0;
}