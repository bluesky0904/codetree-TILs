#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 50

vector<int> graph[MAX_N];
bool is_deleted[MAX_N];
int parent[MAX_N];

int n;
int root;
int delete_num;
int leaf_count;

void DFS(int idx) {
	if (is_deleted[idx]) return;

	bool is_leaf = true;
	for (int i = 0; i < (int)graph[idx].size(); i++) {
		int next_idx = graph[idx][i];
		if (is_deleted[next_idx]) continue;
		DFS(next_idx);
		is_leaf = false;
	}
	if (is_leaf) leaf_count++;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		if (x == -1) {
			root = i;
			continue;
		}
		parent[i] = x;
	}
	cin >> delete_num;
	is_deleted[delete_num] = true;
	DFS(root);
	cout << leaf_count << "\n";
	return 0;
}