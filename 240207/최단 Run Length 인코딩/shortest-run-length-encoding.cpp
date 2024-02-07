#include <iostream>
#include <string>
#include <climits>
using namespace std;

string A;
int length_A;

void Rotate(int cnt) {
	while (cnt--) {
		int temp = A[length_A - 1];
		for (int i = length_A - 1; i >= 1; i--) {
			A[i] = A[i - 1];
		}
		A[0] = temp;
	}
}

int RunLengthEncoding() {
	int cnt = 1;
	string s = "";
	for (int i = 0; i < length_A; i++) {
		if (i + 1 < length_A && A[i] == A[i + 1]) cnt++;
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
	length_A = A.length();

	int min_length = INT_MAX;
	for (int cnt = 1; cnt <= A.length(); cnt++) {
		Rotate(cnt);
		min_length = min(min_length, RunLengthEncoding());
	}
	cout << min_length << "\n";
}