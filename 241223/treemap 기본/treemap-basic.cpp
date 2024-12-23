#include <iostream>
#include <map>
using namespace std;

int n;
map<int, int> m;

int main() {
	cin >> n;
	while (n--) {
		string command;
		int k, v;
		cin >> command;
		
		if (command == "add") {
			cin >> k >> v;
			m[k] = v;
		}
		else if (command == "remove") {
			cin >> k;
			m.erase(k);
		}
		else if (command == "find") {
			cin >> k;
			if (m.find(k) == m.end())
				cout << "None" << "\n";
			else
				cout << m[k] << "\n";
		}
		else {
			if (m.empty())
				cout << "None" << "\n";
			else {
				map<int, int> ::iterator it;
				for (it = m.begin(); it != m.end(); it++) {
					cout << it->second << " ";
				}
				cout << "\n";
			}
		}
	}

	return 0;
}