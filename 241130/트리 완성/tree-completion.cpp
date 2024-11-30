/*
그래프 -> 트리
*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define MAX_N 100000

int n, m;
int uf[MAX_N + 1];
int ans = 0;

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
	}
}
int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		uf[i] = i;

	for (int i = 1; i <= m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		if (Find(v1) != Find(v2)) Union(v1, v2);
		else ans++;
	}

	set<int> roots;
	for (int i = 1; i <= n; i++) {
		roots.insert(Find(i));
	}
	
	ans += ((int)roots.size() - 1);
	cout << ans << "\n";
	return 0;
}