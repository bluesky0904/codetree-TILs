#include <iostream>
#include <set>
using namespace std;

#define MAX_N 100000
int n, m;
set<int> s;


int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x;  cin >> x;
		s.insert(x);
	}
	for (int i = 0; i < m; i++) {
		int x; cin >> x;
		if (s.lower_bound(x) == s.end()) cout << -1 << "\n";
		else cout << *s.lower_bound(x) << "\n";
	}
	return 0;
}