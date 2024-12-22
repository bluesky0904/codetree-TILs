#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

int n, k;
int arr[MAX_N + 1];
unordered_map<long long, int> cnt;

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int diff = k - arr[i];
		ans += cnt[diff];
		cnt[arr[i]]++;
	}

	cout << ans << "\n";
	return 0;
}