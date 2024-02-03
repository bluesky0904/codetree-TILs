#include <iostream>
#include <unordered_map>
using namespace std;

int n;
unordered_map<int, int> Coord;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		if (Coord.find(x) == Coord.end() || Coord[x] > y) Coord[x] = y;
	}
	
	int ans = 0;
	for (auto it = Coord.begin(); it != Coord.end(); it++) {
		ans += it->second;
	}
	cout << ans << "\n";
}