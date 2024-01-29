#include <iostream>
#include <unordered_map>
#include <sstream>
using namespace std;

#define MAX_N 100000

int n, m;
string arr[MAX_N];
unordered_map<string, int> string_to_index;

bool isNumber(const string& str) {
	stringstream ss(str);
	double d;
	char c;
	if (!(ss >> d)) return false;
	if (ss >> c) return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		string_to_index[arr[i]] = i + 1;
	}

	for (int i = 0; i < m; i++) {
		string command; cin >> command;
		if (isNumber(command)) {
			// 숫자일 경우 key값인 문자열을 출력해야 하는데 어떻게 하지?
			int num = stoi(command);
			for (auto it = string_to_index.begin(); it != string_to_index.end(); it++) {
				if (it->second == num) {
					cout << it->first << "\n";
					break;
				}
			}
		}
		else {
			cout << string_to_index[command] << "\n";
		}
	}
	return 0;
}