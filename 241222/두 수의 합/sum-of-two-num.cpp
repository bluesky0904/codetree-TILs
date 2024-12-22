#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

int n, k;
unordered_map<int, int> m;
int arr[MAX_N + 1];

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		int num; cin >> num;
		arr[i] = num;
		m[num] = i;
	}

	int cnt = 0;
	for (int i = 1; i <= n/2; i++) {
		if (m.find(k - arr[i]) != m.end()) cnt++;
	}

	cout << cnt << "\n";
	return 0;
}