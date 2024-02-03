#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
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

	int ans = 0;
	for (auto it = freq.begin(); it != freq.end(); it++) {
		if(it-> second  > ans) ans = max(ans, it->second);
	}
	cout << ans << "\n";
}