#include <iostream>
#include <unordered_map>
using namespace std;

int n;
unordered_map<int, int> m;

int main() {
	cin >> n;
	while (n--) {
		string command; cin >> command;
		int k, v;
		if (command == "add") {
			cin >> k >> v;
			m[k] = v;
		}
		else if (command == "remove") {
			cin >> k;
			m.erase(k);
		}
		else {
			cin >> k;
			if (m.find(k) != m.end())
				cout << m[k] << "\n";
			else
				cout << "None" << "\n";
		}
	}
	return 0;
}