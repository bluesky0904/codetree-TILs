#include <iostream>
#include <map>
using namespace std;

int n;
map<int, int> m;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		if(m[x] == 0) m[x] = i;
	}

	map<int, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
		cout << it->first << " " << it->second << "\n";

	return 0;
}