#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

#define MAX_N 100

int n;
int a[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];

void Initialize() {
	dp[0][0] = a[0][0];

	for (int i = 1; i < n; i++)
		dp[i][0] = dp[i - 1][0] + a[i][0];

	for (int i = 1; i < n; i++)
		dp[0][i] = dp[0][i - 1] + a[0][i];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}

	Initialize();

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + a[i][j];
		}
	}

	cout << dp[n - 1][n - 1] << "\n";
	return 0;
}