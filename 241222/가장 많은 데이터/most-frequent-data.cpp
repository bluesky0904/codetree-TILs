#include <iostream>
#include <unordered_map>
using namespace std;

int n;
int ans;
unordered_map<string, int> string_cnt;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		string_cnt[s]++;

		ans = max(ans, string_cnt[s]);
	}

	cout << ans << "\n";
}