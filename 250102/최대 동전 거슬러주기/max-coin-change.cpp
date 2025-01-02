#include <iostream>
using namespace std;

#define MAX_N 100
#define MAX_M 10000

int n, m;
int coin[MAX_N];
int dp[MAX_M + 1];

void Initialize() {
	for (int i = 0; i <= m; i++)
		dp[i] = 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> coin[i];

	Initialize();

	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < n; j++) {
			if (i - coin[j] >= 0) dp[i] = max(dp[i], dp[i - coin[j]] + 1);
		}
	}

	if (dp[m] == 0) cout << -1 << "\n";
	else cout << dp[m] << "\n";
	return 0;
}