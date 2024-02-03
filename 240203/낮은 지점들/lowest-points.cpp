#include <iostream>
#include <unordered_map>
using namespace std;

int n;
unordered_map<int, int> min_y;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		if (min_y.find(x) == min_y.end() || min_y[x] > y) min_y[x] = y;
	}

	long long ans = 0;
	for (auto it = min_y.begin(); it != min_y.end(); it++) {
		ans += it->second;
	}
	cout << ans << "\n";
}