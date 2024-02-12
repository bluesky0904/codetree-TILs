#include <iostream>
#include <algorithm>
#include <string>
#include <climits>
using namespace std;

#define MAX_N 6

int n = 6;
int num[MAX_N];
int ans = INT_MIN;
string expression;

int Conv(int idx) {
	return num[expression[idx] - 'a'];
}

int Calc() {
	int val = Conv(0);
	int length = expression.size();
	for (int i = 2; i < length; i+=2) {
		if (expression[i - 1] == '+') val += Conv(i);
		else if (expression[i - 1] == '-') val -= Conv(i);
		else  val *= Conv(i);
	}
	return val;
}

void FindMax(int cnt) {
	if (cnt == n) {
		ans = max(ans, Calc());
		return;
	}

	for (int i = 1; i <= 4; i++) {
		num[cnt] = i;
		FindMax(cnt + 1);
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> expression;
	FindMax(0);
	cout << ans << "\n";
	return 0;
}