#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 100000
int n, k;
int arr[MAX_N];
unordered_map<long long, int> cnt;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> arr[i];
	int ans = 0;
	for (int i = 0; i < n; i++) {
		long long diff = (long long)k - arr[i];
		ans += cnt[diff];
		cnt[arr[i]]++;
	}
	cout << ans << "\n";
	return 0;
}