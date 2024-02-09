#include <iostream>
#include <set>
using namespace std;

int n, k;
set<int> s;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		s.insert(x);
	}

	while (k--) {
		cout << *s.rbegin() << " ";
		s.erase(*s.rbegin());
	}
}