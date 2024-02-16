#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 20

int n, m;
int ans;
int A[MAX_N];

void Choose(int curr_idx, int cnt, int curr_val) {
	if (cnt == m) {
		ans = max(ans, curr_val);
		return;
	}
	if (curr_idx == n) return;

	Choose(curr_idx + 1, cnt, curr_val);
	Choose(curr_idx + 1, cnt + 1, curr_val ^= A[curr_idx]);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> A[i];
	Choose(0, 0, 0);
	cout << ans << "\n";
	return 0;
}