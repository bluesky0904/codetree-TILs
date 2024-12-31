#include <iostream>
using namespace std;

#define MAX_N 45

int n;
int dp[MAX_N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;

	dp[1] = 1;
	dp[2] = 1;
	for (int i = 3; i <= n; i++)
		dp[i] = dp[i - 1] + dp[i - 2];

	cout << dp[n] << "\n";
}