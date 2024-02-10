#include <iostream>
#include <vector>
using namespace std;

int n;
int cnt;
vector<int> ans;

void Choose() {
	if (ans.size() >= n) {
		if (ans.size() == n) cnt++;
		return;
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= i; j++) {
			ans.push_back(i);
		}
		Choose();
		for (int j = 1; j <= i; j++) {
			ans.pop_back();
		}
	}
	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	cnt = 0;
	Choose();
	cout << cnt << "\n";
	return 0;
}