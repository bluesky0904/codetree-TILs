#include <iostream>
using namespace std;

#define MAX_N 100000

int uf[MAX_N + 1];
int sequence[MAX_N + 1];
int n, m, k;

int Find(int x) {
	if (uf[x] == x) return x;
	int root_node = Find(uf[x]);
	uf[x] = root_node;
	return root_node;
}

void Union(int x, int y) {
	int X = Find(x), Y = Find(y);
	uf[X] = Y;
}

int main() {
	cin >> n >> m >> k;

	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;

		Union(x, y);
	}

	for (int i = 1; i <= k; i++) {
		int x; cin >> x;
		sequence[i] = x;
	}

	bool move_possible = true;
	for (int i = 1; i <= k - 1; i++) {
		if (uf[i] != uf[i + 1]) {
			move_possible = false;
			break;
		}
	}

	if (move_possible) cout << 1 << "\n";
	else cout << 0 << "\n";
	return 0;
}