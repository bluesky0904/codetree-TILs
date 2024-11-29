#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000

int n, m;
int uf[MAX_N + 1];

int Find(int x) {
	if (uf[x] == x) return x;
	int root_node = Find(uf[x]);
	uf[x] = root_node;
	return root_node;
}

void Union(int x, int y) {
	int X = Find(x), Y = Find(y);
	if (X != Y) {
		uf[X] = Y;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		uf[i] = i;

	for (int i = 1; i <= m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		if (Find(v1) == Find(v2)) {
			cout << i << "\n";
			return 0;
		}
		Union(v1, v2);
	}

	cout << "happy" << "\n";
	return 0;
}