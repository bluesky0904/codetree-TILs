#include <iostream>
#include <map>
using namespace std;

int n;
map<int, int> m;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		int k, v;
		if (s == "add") {
			cin >> k >> v;
			m[k] = v;
		}
		else if (s == "remove") {
			cin >> k;
			m.erase(k);
		}
		else if (s == "find") {
			cin >> k;
			if (m.find(k) != m.end()) cout << m[k] << "\n";
			else cout << "None" << "\n";
		}
		else {
			if (m.begin() == m.end()) cout << "None" << "\n";
			else {
				for (auto it = m.begin(); it != m.end(); it++)
					cout << it->second << " ";
				cout << "\n";
			}
		}
	}
	return 0;
}