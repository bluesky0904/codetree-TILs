#include <iostream>
#include <set>
using namespace std;

int n;
set<int> s;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string str; cin >> str;
		int x;
		if (str == "add") {
			cin >> x;
			s.insert(x);
		}
		else if (str == "remove") {
			cin >> x;
			s.erase(x);
		}
		else if (str == "find") {
			cin >> x;
			if (s.find(x) != s.end()) cout << "true" << "\n";
			else cout << "false" << "\n";
		}
		else if (str == "lower_bound") {
			cin >> x;
			if (s.lower_bound(x) != s.end()) cout << *s.lower_bound(x) << "\n";
			else cout << "None" << "\n";
		}
		else if (str == "upper_bound") {
			cin >> x;
			if (s.upper_bound(x) != s.end()) cout << *s.upper_bound(x) << "\n";
			else cout << "None" << "\n";
		}
		else if (str == "largerst") {
			if (s.rbegin() != s.rend()) cout << *s.rbegin() << "\n";
			else cout << "None" << "\n";
		}
		else if (str == "smallest") {
			if (s.begin() != s.end()) cout << *s.begin() << "\n";
			else cout << "None" << "\n";
		}
	}
}