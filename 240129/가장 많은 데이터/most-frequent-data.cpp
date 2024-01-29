#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

int n;
string arr[MAX_N];
unordered_map<string, int> freq;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		freq[arr[i]]++;
	}

	int ans = 0;
	for (auto it = freq.begin(); it != freq.end(); it++) {
		if (it->second > ans) ans = it->second;
	}
	cout << ans << " ";
}