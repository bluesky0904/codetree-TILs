#include <iostream>
#include <set>
using namespace std;

int n;
set<int> s;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		string command; cin >> command;
		if (command == "add") {
			cin >> x;
			s.insert(x);
		}
		else if (command == "remove") {
			cin >> x;
			s.erase(x);
		}
		else if (command == "find") {
			cin >> x;
			if (s.find(x) == s.end())
				cout << "false" << "\n";
			else
				cout << "true" << "\n";
		}
		else if (command == "lower_bound") {
			cin >> x;
			if (s.lower_bound(x) == s.end())
				cout << "None" << "\n";
			else
				cout << *s.lower_bound(x) << "\n";
		}
		else if (command == "upper_bound") {
			cin >> x;
			if (s.upper_bound(x) == s.end())
				cout << "None" << "\n";
			else
				cout << *s.upper_bound(x) << "\n";
		}
		else if (command == "largest") {
			if (s.empty())
				cout << "None" << "\n";
			else
				cout << *s.rbegin() << "\n";
		}
		else {
			if (s.empty())
				cout << "None" << "\n";
			else
				cout << *s.begin() << "\n";
		}
	}
}