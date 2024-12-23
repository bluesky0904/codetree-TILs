#include <iostream>
#include <set>
using namespace std;

int t, k;
set<int> s;

int main() {
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		cin >> k;
		for (int i = 1; i <= k; i++) {
			char op; cin >> op;
			if (op == 'I') {
				int n; cin >> n;
				s.insert(n);
			}
			else {
				int x; cin >> x;
				if (x == 1) {
					if (s.empty()) continue;
					s.erase(*s.rbegin());
				}
				else {
					if (s.empty()) continue;
					s.erase(*s.begin());
				}
			}
		}

		if (s.empty()) cout << "EMPTY" << "\n";
		else cout << *s.rbegin() << " " << *s.begin() << "\n";
	}
}