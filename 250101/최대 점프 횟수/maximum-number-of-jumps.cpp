#include <iostream>
#include <climits>
using namespace std;

#define MAX_N 1000
int n;
int a[MAX_N];
int dp[MAX_N];

void Initialize() {
	for (int i = 0; i < n; i++)
		dp[i] = INT_MIN;

	dp[0] = 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	Initialize();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (dp[j] == INT_MIN) continue;

			if (j + a[j] >= i) dp[i] = max(dp[i], dp[j] + 1);
		}
	}

	int ans = INT_MIN;
	for (int i = 0; i < n; i++) {
		ans = max(ans, dp[i]);
	}

	cout << ans << "\n";
	return 0;
}