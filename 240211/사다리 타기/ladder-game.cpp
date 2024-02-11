#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define MAX_N 11

int n, m;
int ans = INT_MAX;
vector<pair<int, int>> lines;
vector<pair<int, int>> selected_lines;

bool Possible() {
	int num1[MAX_N], num2[MAX_N];
	for (int i = 0; i < n; i++) {
		num1[i] = num2[i] = i;
	}

	for (int i = 0; i < lines.size(); i++) {
		int idx = lines[i].second;
		swap(num1[idx], num1[idx + 1]);
	}

	for (int i = 0; i < selected_lines.size(); i++) {
		int idx = selected_lines[i].second;
		swap(num2[idx], num2[idx + 1]);
	}

	for (int i = 0; i < n; i++) {
		if (num1[i] != num2[i]) return false;
	}
	return true;
}

void FindMinLines(int cnt) {
	if (cnt == m) {
		if (Possible()) ans = min(ans, (int)selected_lines.size());
		return;
	}

	selected_lines.push_back(lines[cnt]);
	FindMinLines(cnt + 1);
	selected_lines.pop_back();

	FindMinLines(cnt + 1);
	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		lines.push_back(make_pair(b, a - 1));
	}

	sort(lines.begin(), lines.end());

	FindMinLines(0);
	cout << ans << "\n";
	return 0;
}