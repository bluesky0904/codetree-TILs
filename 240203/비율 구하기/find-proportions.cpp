#include <iostream>
#include <map>
#include <string>
using namespace std;

int n;
map<string, int> m;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		m[s]++;
	}

	for (auto it = m.begin(); it != m.end(); it++) {
		double ratio = (double)(it->second) / n * 100;
		cout << fixed;
		cout.precision(4);
		cout << (it->first) << " " << ratio << "\n";
	}
}