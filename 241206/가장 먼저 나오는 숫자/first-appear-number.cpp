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
	if (arr[min_idx] == target) return min_idx + 1;
	else return -1;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int i = 0; i < m; i++) {
		int target; cin >> target;
		cout << lower_bound(target) << "\n";
	}
	return 0;
}