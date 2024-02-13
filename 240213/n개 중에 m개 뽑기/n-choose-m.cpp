#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> ans;

void Print() {
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
	cout << "\n";
}

void Choose(int cur_num, int prev) {
	if (cur_num == m) {
		Print();
		return;
	}

	for (int i = 1; i <= n; i++) {
		if (prev < i) {
			ans.push_back(i);
			Choose(cur_num + 1, i);
			ans.pop_back();
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	Choose(0, 0);
}