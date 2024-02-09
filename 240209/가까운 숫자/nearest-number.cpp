#include <iostream>
#include <set>
#include <climits>
using namespace std;

int n;
set<int> s;

int main() {
	s.insert(0);
	cin >> n;
	int dist = INT_MAX;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		s.insert(x);
		
		auto it = s.find(x);
		

		if (it != s.begin()) dist = min(dist, x - *prev(it));

		if (next(it) != s.end()) dist = min(dist, *next(it) - x);

		cout << dist << "\n";
	}
	return 0;
}