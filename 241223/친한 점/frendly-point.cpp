#include <iostream>
#include <set>
using namespace std;

int n, m;
set<pair<int, int>> s;
 
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		s.insert(make_pair(x, y));
	}
	
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		if (s.lower_bound(make_pair(x, y)) == s.end())
			cout << -1 << " " << -1 << "\n";
		else {
			pair<int, int> friendest = *s.lower_bound(make_pair(x, y));
			cout << friendest.first << " " << friendest.second << "\n";
		}
	}
}