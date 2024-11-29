#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000

int n, m;
int uf[MAX_N + 1];

int Find(int a) {
	if (uf[a] == a) return a;
	int root_node = Find(uf[a]);
	uf[a] = root_node;
	return root_node;
}

void Union(int a, int b) {
	int A = Find(a), B = Find(b);
	uf[A] = B;
}

int main() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		uf[i] = i;

	for (int i = 1; i <= m; i++) {
		char op; cin >> op;
		int a, b;
		if (op == 'x') {
			cin >> a >> b;
			Union(a, b);
		}
		else if (op == 'y') {
			cin >> a;
			int root = Find(a);
			int cnt = 0;
			for (int i = 1; i <= n; i++) {
				if (root == Find(i)) cnt++;
			}
			cout << cnt << "\n";
		}
	}

	return 0;
}