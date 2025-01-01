#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int findMinSubsequenceLength(int n, int m, const vector<int>& a) {
    vector<int> dp(m + 1, INT_MAX); // dp[i]: 합이 i가 되도록 하는 최소 부분 수열 길이
    dp[0] = 0; // 합이 0이 되는 부분 수열의 길이는 0

    for (int i = 0; i < n; ++i) {
        for (int j = m; j >= a[i]; --j) {
            if (dp[j - a[i]] != INT_MAX) {
                dp[j] = min(dp[j], dp[j - a[i]] + 1);
            }
        }
    }

    return (dp[m] == INT_MAX) ? -1 : dp[m]; // 합이 m이 되는 부분 수열이 없다면 -1 반환
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int result = findMinSubsequenceLength(n, m, a);
    cout << result << endl;

    return 0;
}
