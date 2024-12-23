#include <iostream>
#include <set>
#include <cmath>
using namespace std;

int n;
set<int> s;

int main() {
	cin >> n;
	s.insert(0);

	int ans = (int)1e9;
	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;

		set<int>::iterator it = s.upper_bound(num);
		if (it != s.end()) {
			ans = min(ans, abs(num - *it));
		}

		it--;
		ans = min(ans, abs(num - *it));
		s.insert(num);

		cout << ans << "\n";
	}

	return 0;
}