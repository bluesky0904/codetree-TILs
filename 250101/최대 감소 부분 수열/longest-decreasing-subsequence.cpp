#include <iostream>
#include <climits>
using namespace std;

#define MAX_N 1000

int n;
int dp[MAX_N + 1];
int a[MAX_N + 1];

void Initialize() {
	for (int i = 0; i < n; i++)
		dp[i] = 1;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	Initialize();

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[j] > a[i])
				dp[i] = max(dp[i], dp[j] + 1);
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans = max(ans, dp[i]);
	}

	cout << ans << "\n";
	return 0;
}