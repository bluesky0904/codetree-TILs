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
		s.insert(-x);
	}

	int cnt = 0;
	for (auto it = s.begin(); cnt < k; it++) {
		cout << -(*it) << " ";
		cnt++;
	}	
}