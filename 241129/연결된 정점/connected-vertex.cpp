#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000

int n, m;
int uf[MAX_N + 1];
int uf_size[MAX_N + 1];

int Find(int a) {
	if (uf[a] == a) return a;
	int root_node = Find(uf[a]);
	uf[a] = root_node;
	return root_node;
}

void Union(int a, int b) {
	int A = Find(a), B = Find(b);
	if (A != B) {
		uf[A] = B;
		uf_size[B] += uf_size[A];
	}
}

int main() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		uf[i] = i;
		uf_size[i] = 1;
	}

	for (int i = 1; i <= m; i++) {
		char op; cin >> op;
		int a, b;
		if (op == 'x') {
			cin >> a >> b;
			Union(a, b);
		}
		else if (op == 'y') {
			cin >> a;
			cout << uf_size[Find(a)] << "\n";
		}
	}

	return 0;
}