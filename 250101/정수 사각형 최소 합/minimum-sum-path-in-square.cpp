#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 100

int n;
int a[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];

void Initialize() {
	dp[0][n - 1] = a[0][n - 1];

	for (int i = n - 2; i >= 0; i--) {
		dp[0][i] = dp[0][i + 1] + a[0][i];
	}

	for (int i = 1; i < n; i++) {
		dp[i][n - 1] = dp[i - 1][n - 1] + a[i][n-1];
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];

	Initialize();

	for (int i = 1; i < n; i++) {
		for (int j = n - 2; j >= 0; j--) {
			dp[i][j] = min(dp[i][j + 1], dp[i - 1][j]) + a[i][j];
		}
	}

	cout << dp[n - 1][0] << "\n";
	return 0;
}