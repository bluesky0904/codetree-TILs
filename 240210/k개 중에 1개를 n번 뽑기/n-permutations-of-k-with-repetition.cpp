#include <iostream>
#include <vector>
using namespace std;

int k, n;
vector<int> ans;

void Print() {
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
	cout << "\n";
}

void Choose(int curr_num) {
	if (curr_num == n + 1) {
		Print();
		return;
	}

	for (int i = 1; i <= k; i++) {
		ans.push_back(i);
		Choose(curr_num + 1);
		ans.pop_back();
	}

	return;
}


int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> k >> n;
	Choose(1);
	return 0;
}