#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000
int n;
vector<int> edges[MAX_N + 1];
bool visited[MAX_N + 1];
int parent[MAX_N + 1];

void Traversal(int x) {
	for (int i = 0; i < (int)edges[x].size(); i++) {
		int y = edges[x][i];
		if (!visited[y]) {
			visited[y] = true;
			parent[y] = x;
			Traversal(y);
		}
	}
}

int main() {
	cin >> n;
	
	for (int i = 1; i <= n - 1; i++) {
		int x, y;
		cin >> x >> y;

		edges[x].push_back(y);
		edges[y].push_back(x);
	}

	visited[1] = true;
	Traversal(1);

	for (int i = 2; i <= n; i++) {
		cout << parent[i] << "\n";
	}
	return 0;
}