#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 1000
#define MOD 10007

int memo[MAX_N + 1];
int n;

int countWays(int x) {
    if (x == 0) return 1;
    if (x == 1) return 0;
    if (x == 2) return 1;
    if (x == 3) return 1;

    if (memo[x] != -1) return memo[x];

    memo[x] = (countWays(x - 2) + countWays(x - 3)) % MOD;
    return memo[x];
}

int main() {
    cin >> n;
    fill(memo, memo + n + 1, -1);
    cout << countWays(n) << "\n";
}
