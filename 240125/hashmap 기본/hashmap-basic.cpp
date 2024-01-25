#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n; cin >> n;
	unordered_map<int, int> m;

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
		else {
			cin >> k;
			if (m.find(k) != m.end()) {
				cout << m[k] << "\n";
			}
			else {
				cout << "None" << "\n";
			}
		}
	}

	return 0;
}