#include <iostream>
using namespace std;

#define MAX_N 100000

int n, m;
int arr[MAX_N];

int lower_bound(int target) {
	int min_idx = n;
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;

		if (arr[mid] >= target) {
			right = mid - 1;
			min_idx = min(min_idx, mid);
		}
		else 
			left = mid + 1;
	}
	return min_idx;
}

int upper_bound(int target) {
	int min_idx = n;
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;

		if (arr[mid] > target) {
			right = mid - 1;
			min_idx = min(min_idx, mid);
		}
		else
			left = mid + 1;
	}
	return min_idx;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int i = 0; i < m; i++) {
		int num; cin >> num;
		cout << upper_bound(num) - lower_bound(num) << "\n";
	}

	return 0;
}