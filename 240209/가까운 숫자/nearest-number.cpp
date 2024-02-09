#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int n;
set<int> s;
int ans = INT_MAX;

int main() {
	cin >> n;
	s.insert(0);
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		set<int>::iterator it = s.upper_bound(x);
		if (it != s.end()) ans = min(ans, *it - x);
		it--;
		ans = min(ans, x - *it);
		s.insert(x);
		cout << ans << "\n";
	}
}