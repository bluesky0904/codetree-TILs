#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int ans;
vector<int> v;
vector<int> selected;

int CalcXor() {
	int sum = selected[0];
	for (int i = 1; i < selected.size(); i++) {
		sum ^= selected[i];
	}
	return sum;
}

void Choose(int cur_num, int prev) {
	if (cur_num == m) {
		ans = max(ans, CalcXor());
		return;
	}

	for (int i = 0; i < n; i++) {
		if (prev < v[i]) {
			selected.push_back(v[i]);
			Choose(cur_num + 1, v[i]);
			selected.pop_back();
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		v.push_back(x);
	}
	
	sort(v.begin(), v.end());

	Choose(0, 0);

	cout << ans << "\n";
}