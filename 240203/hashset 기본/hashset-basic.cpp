#include <iostream>
#include <unordered_set>
using namespace std;

int n;
unordered_set<int> s;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		string str; int x; cin >> str >> x;
		if (str == "add") s.insert(x);
		else if (str == "remove") s.erase(x);
		else {
			if (s.find(x) != s.end()) cout << "true" << "\n";
			else cout << "false" << "\n";
		}
	}
	return 0;
}