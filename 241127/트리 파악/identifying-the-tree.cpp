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
vector<int> leaf;
bool visited[MAX_N + 1];
int parent[MAX_N + 1];

int n;

void DFS(int x) {
	bool is_leaf = true;
	for (int i = 0; i < (int)edge[x].size(); i++) {
		int next_x = edge[x][i];

		if (visited[next_x]) continue;

		visited[next_x] = true;
		is_leaf = false;

		DFS(next_x);
	}
	if (is_leaf) leaf.push_back(x);
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
	DFS(1);

	// leaf : 2 5 cnt = 0
	// a : 5 -> 4, leaf : 2 4 cnt = 1
	// b : 4 -> 3, leaf : 2 3 cnt = 2
	// a : 3 -> 1, leaf : 2 cnt = 3
	// b : 2 -> 1, leaf : x cnt = 4
	// a 불가 즉 0이 답 cnt = 5

	int cnt = 0;
	while (!leaf.empty()) {
		int horse = leaf.back();
		leaf.pop_back(); 

		int next_horse = parent[horse];
		if(next_horse != 1) leaf.push_back(next_horse);

		cnt++;
	}
	
	if (cnt % 2 == 0) cout << 0 << "\n";
	else cout << 1 << "\n";
	return 0;
}