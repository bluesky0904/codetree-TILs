#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<int> answer;

void Print() {
	for (int i = 0; i < answer.size(); i++) {
		cout << answer[i] << " ";
	}
	cout << "\n";
}

void Choose(int curr_num) {
	if (curr_num == n + 1) {
		Print();
		return;
	}

	for (int i = 1; i <= k; i++) {
		answer.push_back(i);
		Choose(curr_num + 1);
		answer.pop_back();
	}

	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> k >> n;
	Choose(1);
	return 0;
}