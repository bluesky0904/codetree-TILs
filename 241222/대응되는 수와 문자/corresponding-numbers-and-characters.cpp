#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

#define MAX_N 10000

int n, m;
unordered_map<string, int> string_to_num;
string num_to_string[MAX_N + 1];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		string_to_num[s] = i;
		num_to_string[i] = s;
	}

	while (m--) {
		string s; cin >> s;
		if ('0' <= s[0] && s[0] <= '9')
			cout << num_to_string[stoi(s)] << "\n";
		else
			cout << string_to_num[s] << "\n";
	}
}