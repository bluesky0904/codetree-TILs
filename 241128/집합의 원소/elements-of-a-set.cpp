#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000

int n, m;
int uf[MAX_N + 1];

int find_function(int a) {
	if (uf[a] == a) return a;
	int root_node = find_function(uf[a]);
	uf[a] = root_node;
	return root_node;
}

void union_function(int a, int b) {
	int A = find_function(a), B = find_function(b);
	uf[A] = B;
}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		uf[i] = i;
	}

	for (int i = 1; i <= m; i++) {
		int command, a, b;
		cin >> command >> a >> b;
		if (command == 0) union_function(a, b);
		else if (command == 1) {
			if (find_function(a) == find_function(b)) cout << 1 << "\n";
			else cout << 0 << "\n";
		}
	}

	return 0;
}