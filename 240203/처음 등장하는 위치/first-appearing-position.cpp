#include <iostream>
#include <map>
using namespace std;

int n;
map<int, int> m;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		if (m.find(x) == m.end()) m[x] = i;
	}

	for (auto it = m.begin(); it != m.end(); it++) {
		cout << (it->first) << " " << (it->second) << "\n";
	}
}