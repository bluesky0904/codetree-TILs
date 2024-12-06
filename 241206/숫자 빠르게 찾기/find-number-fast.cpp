#include <iostream>
using namespace std;

#define MAX_N 100000

int n, m;
int arr[MAX_N];

int binary_search(int target) {
	int idx = -1;
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (arr[mid] == target) {
			return mid;
		}

		if (arr[mid] > target) {
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	return -2;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < m; i++) {
		int num; cin >> num;
		cout << binary_search(num) + 1 << "\n";
	}

	return 0;
}