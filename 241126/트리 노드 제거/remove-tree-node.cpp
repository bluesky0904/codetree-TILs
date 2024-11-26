#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 50

vector<int> edge[MAX_N];
int parent[MAX_N];
bool is_deleted[MAX_N];

int n;
int root;
int leaf_count = 0;

void DFS(int idx) {
	if (is_deleted[idx]) return;

	bool is_leaf = true;
	for (int i = 0; i < (int)edge[idx].size(); i++) {
		int next_idx = edge[idx][i];
		if (is_deleted[next_idx]) continue;
		DFS(next_idx);
		is_leaf = false;
	}
	if (is_leaf) leaf_count++;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int p; cin >> p;
		parent[i] = p;
		if (p == -1) {
			root = i;
			continue;
		}
		edge[p].push_back(i);
	}
	int delete_idx; cin >> delete_idx;
	is_deleted[delete_idx] = true;
	DFS(root);
	cout << leaf_count << "\n";
	return 0;
}