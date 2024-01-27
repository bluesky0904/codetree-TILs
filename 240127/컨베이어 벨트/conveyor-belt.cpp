#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, t;
	cin >> n >> t;
	vector<int> belt(2 * n);
	for (int i = 0; i < 2*n; i++) {
		cin >> belt[i];
	}
	for (int time = 0; time < t; time++) {
		int tmp = belt[2 * n - 1];
		for (int i = 2 * n - 1; i > 0; i--) {
			belt[i] = belt[i - 1];
		}
		belt[0] = tmp;
	}

	for (int i = 0; i < n; i++) {
		cout << belt[i] << " ";
	}

	cout << "\n";

	for (int i = n; i < 2*n; i++) {
		cout << belt[i] << " ";
	}
}