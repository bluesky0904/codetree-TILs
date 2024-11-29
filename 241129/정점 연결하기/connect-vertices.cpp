#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int n;
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
	cin >> n;

	for (int i = 1; i <= n; i++) {
		uf[i] = i;
	}

	for (int i = 1; i <= n - 2; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		Union(v1, v2);
	}

	cout << 1 << " ";
	for (int i = 2; i <= n; i++) {
		if (Find(i) != Find(1)) {
			cout << i << "\n";
			break;
		}
	}

	return 0;
}