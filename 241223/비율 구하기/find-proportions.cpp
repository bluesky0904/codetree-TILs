#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

int n;
map<string, double> m;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		m[s]++;
	}

	map<string, double>::iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << " " << fixed << setprecision(4) << it->second * 100 / n << "\n";
	}
}