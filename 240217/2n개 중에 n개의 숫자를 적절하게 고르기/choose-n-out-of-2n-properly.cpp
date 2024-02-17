#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define MAX_N 10

int n;
int sum;
int ans = INT_MAX;
vector<int> v;
vector<int> selected;

int Calc() {
	int partsum1 = 0, partsum2 = 0;
	for (int i = 0; i < selected.size(); i++) {
		partsum1 += selected[i];
	}
	partsum2 = sum - partsum1;

	return abs(partsum1 - partsum2);
}

void FindMinDiff(int curr_idx, int cnt) {
	if (cnt == n) {
		ans = min(ans, Calc());
		return;
	}
	if (curr_idx == v.size()) return;

	FindMinDiff(curr_idx + 1, cnt);

	selected.push_back(v[curr_idx]);
	FindMinDiff(curr_idx + 1, cnt + 1);
	selected.pop_back();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	sum = 0;
	for (int i = 0; i < 2 * n; i++) {
		int num; cin >> num;
		sum += num;
		v.push_back(num);
	}
	sort(v.begin(), v.end());

	FindMinDiff(0, 0);

	cout << ans << "\n";
	return 0;
}