#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

#define MAX_N 100000

int n, m;
unordered_map<string, int> string_to_num;
string num_to_string[MAX_N + 1];

bool is_number(string s) {
	for (char c : s) {
		if (!isdigit(c)) return false;
	}
	return true;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		string_to_num[s] = i;
		num_to_string[i] = s;
	}

	for (int i = 1; i <= m; i++) {
		string s; cin >> s;
		if (is_number(s))cout << num_to_string[stoi(s)] << "\n";
		else cout << string_to_num[s] << "\n";
	}

	return 0;
}