#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000

int n;
vector<int> graph[MAX_N + 1];
int parent[MAX_N + 1];

int main() {
	cin >> n;
	for (int i = 2; i <= n; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
		parent[v2] = v1;
	}

	for (int i = 2; i <= n; i++) {
		cout << parent[i] << "\n";
	}
}