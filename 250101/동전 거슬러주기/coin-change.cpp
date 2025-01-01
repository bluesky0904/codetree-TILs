#include <iostream>
#include <climits>
using namespace std;

#define MAX_N 100
#define MAX_M 10000

int n, m;
int dp[MAX_M];
int coin[MAX_N];

void Initialize() {
	for (int i = 0; i <= m; i++) {
		dp[i] = INT_MAX;
	}

	dp[0] = 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> coin[i];

	Initialize();
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (i >= coin[j]) {
				if (dp[i - coin[j]] == INT_MAX) continue;
				dp[i] = min(dp[i], dp[i - coin[j]] + 1);
			}
		}
	}

	int ans = dp[m];
	if (ans == INT_MAX)
		ans = -1;
	cout << ans << "\n";
	return 0;
}