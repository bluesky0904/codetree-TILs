#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int n, m;
set<int> s;
int arr[MAX_N];
int ans = INT_MAX;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		s.insert(arr[i]);
	}

	for (int i = 0; i < n; i++) {
		int x = arr[i];
		if (s.lower_bound(x + m) != s.end()) {
			ans = min(ans, *s.lower_bound(x + m) - x);
		}
		auto it = s.upper_bound(x - m);
		if (it != s.begin()) {
			it--;
			ans = min(ans, x - *it);
		}
	}

	if (ans == INT_MAX) ans = -1;
	cout << ans << "\n";
}