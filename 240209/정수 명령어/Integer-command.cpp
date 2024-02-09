#include <iostream>
#include <set>
using namespace std;

int t, n;
set<int> s;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> t;
	while (t--) {
		s.clear();
		cin >> n;
		for (int i = 0; i < n; i++) {
			char command; int x;
			cin >> command >> x;
			if (command == 'I') s.insert(x);
			else if (command == 'D' && s.size() > 0) {
				if (x == 1) s.erase(*s.rbegin());
				else s.erase(*s.begin());
			}
		}
		if (s.size() == 0) cout << "EMPTY" << "\n";
		else cout << *s.rbegin() << " " << *s.begin() << "\n";
	}
}