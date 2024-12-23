#include <iostream>
#include <map>
using namespace std;

int n;
map<string, int> m;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		m[s]++;
	}

	map<string, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << " " << it->second << "\n";
	}

	return 0;
}