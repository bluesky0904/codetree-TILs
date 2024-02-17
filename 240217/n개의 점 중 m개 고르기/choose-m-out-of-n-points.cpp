#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <tuple>
using namespace std;

int n, m;
int ans = INT_MAX;
int max_dist;
vector<pair<int, int>> point;
vector<pair<int, int>> selected_m;
vector<pair<int, int>> selected_two;

int CalcMax() {
	int ax, ay, bx, by;
	tie(ax, ay) = selected_two[0];
	tie(bx, by) = selected_two[1];
	return (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
}

void FindMaxDist(int curr_idx, int cnt) {
	if (cnt == 2) {
		max_dist = max(max_dist, CalcMax());
		return;
	}
	if (curr_idx == selected_m.size()) return;

	FindMaxDist(curr_idx + 1, cnt);

	selected_two.push_back(selected_m[curr_idx]);
	FindMaxDist(curr_idx + 1, cnt + 1);
	selected_two.pop_back();
}

int CalcMin() {
	max_dist = 0;
	FindMaxDist(0, 0);
	return max_dist;
}

void FindMinDist(int curr_idx, int cnt) {
	if (cnt == m) {
		ans = min(ans, CalcMin());
		return;
	}
	if (curr_idx == point.size()) return;

	FindMinDist(curr_idx + 1, cnt);

	selected_m.push_back(point[curr_idx]);
	FindMinDist(curr_idx + 1, cnt + 1);
	selected_m.pop_back();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		point.push_back(make_pair(x, y));
	}

	FindMinDist(0, 0);
	cout << ans << "\n";
	return 0;
}