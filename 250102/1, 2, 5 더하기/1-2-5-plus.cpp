#include <iostream>
using namespace std;

#define MAX_N 1000
#define MOD 10007

int n;
int dp[MAX_N + 1];

void Initialize() {
	for (int i = 0; i <= n; i++)
		dp[i] = 0;
	dp[0] = 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;

	Initialize();

	for (int i = 1; i <= n; i++) {
		if (i - 1 >= 0) dp[i] = (dp[i] + dp[i - 1]) % MOD;
		if (i - 2 >= 0) dp[i] = (dp[i] + dp[i - 2]) % MOD;
		if (i - 5 >= 0) dp[i] = (dp[i] + dp[i - 5]) % MOD;
	}

	cout << dp[n] << "\n";
	return 0;
}