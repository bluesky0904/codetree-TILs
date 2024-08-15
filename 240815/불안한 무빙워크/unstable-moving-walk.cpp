#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<pair<int, int>> v;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;

	for (int i = 0; i < 2 * n; i++) {
		int num;
		cin >> num;
		v.push_back({ num, 0 });
	}

	int turn = 0;
	while (1) {
		turn++;

		// 과정1
		pair<int, int> tmp = v[2 * n - 1];
		for (int i = 2 * n - 1; i > 0; i--) {
			v[i] = v[i - 1];
		}
		v[0] = tmp;
		if (v[n - 1].second == 1) v[n - 1].second = 0;

		// 과정2
		for (int i = n - 2; i >= 0; i--) {
			if (v[i].second == 1) {
				if (v[i + 1].second == 0 && v[i + 1].first > 0) {
					v[i + 1].second = 1;
					v[i + 1].first--;
					v[i].second = 0;
				}
			}
			if (v[n - 1].second == 1) v[n - 1].second = 0;
		}

		// 과정3
		if (v[0].second == 0 && v[0].first != 0) {
			v[0].second = 1;
			v[0].first--;
		}

		// 과정4
		int zero_cnt = 0;
		for (int i = 0; i < 2 * n; i++) {
			if (v[i].first == 0) zero_cnt++;
		}
		if (zero_cnt >= k) {
			cout << turn << "\n";
			return 0;
		}
	}
}