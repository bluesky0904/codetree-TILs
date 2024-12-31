#include <iostream>
using namespace std;

#define MAX_N 1000
#define MOD 10007

int n;
int memo[MAX_N + 1];

int CountWays(int x) {
	if (memo[x] != -1) return memo[x];

	if (x == 1) return 1;
	if (x == 2) return 2;

	memo[x] = (CountWays(x - 1) + CountWays(x - 2)) % MOD;
	return memo[x] % MOD;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	fill(memo, memo + n + 1, - 1);

	cout << CountWays(n) << "\n";
	return 0;
}