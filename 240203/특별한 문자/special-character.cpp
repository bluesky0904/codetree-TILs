#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<char, int> freq;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string s; cin >> s;
	for (int i = 0; i < s.size(); i++) {
		freq[s[i]]++;
	}

	for (auto it = freq.begin(); it != freq.end(); it++) {
		if (it->second == 1) {
			cout << it->first << "\n";
			return 0;
		}
	}
	cout << "None" << "\n";
	return 0;
}