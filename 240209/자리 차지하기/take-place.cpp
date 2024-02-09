/*
3 4
4 1 1

1 2 3 4

*/
#include <iostream>
#include <set>
using namespace std;

int n, m;
set<int> s;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		s.insert(i);
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		auto it = s.upper_bound(x);
		if (it == s.begin()) {
			cout << cnt << "\n";
			return 0;
		}
		else {
			it--;
			s.erase(it);
			cnt++;
		}
	}
	cout << cnt << "\n";
	return 0;
}