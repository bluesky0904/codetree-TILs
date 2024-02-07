#include <iostream>
#include <string>
#include <climits>
using namespace std;

string A;
int n;

void Rotate(int cnt) {
	while (cnt--) {
		char temp = A[n - 1];
		for (int i = n - 1; i >= 1; i--) {
			A[i] = A[i - 1];
		}
		A[0] = temp;
	}
}

int RunLengthEncoding() {
	int cnt = 1;
	string s = "";
	for (int i = 0; i < n; i++) {
		if (i + 1 < n && A[i] == A[i + 1]) cnt++;
		else {
			s += A[i];
			s += to_string(cnt);
			cnt = 1;
		}
	}
	return s.length();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> A;
	n = A.length();

	int min_length = INT_MAX;
	for (int cnt = 1; cnt <= n; cnt++) {
		Rotate(cnt);
		min_length = min(min_length, RunLengthEncoding());
	}

	cout << min_length << "\n";
}