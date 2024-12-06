/*
각 선분 위에 몇 개의 점이 존재하는지 출력
m n logn

10^5 10^5 5
5 10^10

1000ms = 1s -> 10^8

lower bound = target 이상인 값 중에서 최소 idx
upper bound = target 초과인 값 중에서 최소 idx

10 30 50 : 정렬된 배열
1 5
(1) (5) 10 30 50 ... 0 
5 21
(5) 10 (21) 30 50 ... 1
22 59
10 (22) 30  50 (59)  ... 2
210 293 
10 30 50 (210) (293) ... 0
*/
#include <iostream>
using namespace std;

#define MAX_N 100000

int n, m;
int point[MAX_N];

int lower_bound(int target) {
	int min_idx = n;
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (point[mid] >= target) {
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
		if (point[mid] > target) {
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
	for (int i = 0; i < n; i++) {
		int num;
		cin >> point[i];
	}

	for (int i = 0; i < m; i++) {
		int start, end;
		cin >> start >> end;
		cout << upper_bound(end) - lower_bound(start) << "\n";
	}
	return 0;
}