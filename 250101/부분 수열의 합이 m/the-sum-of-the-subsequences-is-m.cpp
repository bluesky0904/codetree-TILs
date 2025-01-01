#include <iostream>
#include <climits>
using namespace std;

#define MAX_N 100
#define MAX_M 10000
#define MAX_ANS 101

int n, m;
int arr[MAX_N];
int dp[MAX_M + 1];

void Initialize() {
	for (int i = 0; i <= m; i++)
		dp[i] = MAX_ANS;
	dp[0] = 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	Initialize();

	for (int i = 0; i < n; i++) {
		for (int j = m; j >= 0; j--) {
			if (j >= arr[i]) dp[j] = min(dp[j], dp[j - arr[i]] + 1);
		}
	}

	int min_len = dp[m];

	if (min_len == MAX_ANS)
		min_len = -1;

	cout << min_len;
	return 0;
}