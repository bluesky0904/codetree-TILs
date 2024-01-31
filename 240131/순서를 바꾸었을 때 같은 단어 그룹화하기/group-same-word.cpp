#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define MAX_N 1000

int n;
unordered_map<string, int> freq;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		sort(s.begin(), s.end());
		freq[s]++;
	}

	int max_cnt = 0;
	for (auto it = freq.begin(); it != freq.end(); it++) {
		if (it->second > max_cnt) max_cnt = it->second;
	}
	cout << max_cnt << "\n";
}