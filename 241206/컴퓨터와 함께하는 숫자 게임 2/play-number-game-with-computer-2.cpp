/*
사람 : n명, 원형으로 앉아 있음. 답이 될 수 있는 범위 중 항상 가운데 값을 고름.
컴퓨터 : 1이상 m이하의 수 중 하나를 선택
사람 A가 그 숫자를 예측
컴퓨터는 사람이 예측한 숫자가 자신이 선택한 숫자보다 작은지 큰지 말함
작거나 클 경우 다음 사람 턴으로 넘어감
같을 경우 그 사람이 벌칙을 받음

컴퓨터가 처음 a이상 b이하인 수 만을 선택한다 했을 때,
게임이 가장 적게 지속될 때와 가장 오래 지속 될 때를 계산하는 프로그램

예제 1
입력 : 13 4 6
출력 3 4

컴퓨터 예측 : 4
1과 13의 중앙값 7
1과 6의 중앙값 3
4와 6의 중앙값 5
4와 4의 중앙값 4 ... 4회 ... 최대

컴퓨터 예측 : 5
1과 13의 중앙값 7
1과 6의 중앙값 3
4와 6의 중앙값 5 ... 3회 ... 최소

컴퓨터 예측 : 6
1과 13의 중앙값 7
1과 6의 중앙값 3
4와 6의 중앙값 5
6과 6의 중앙값 6 ... 4회
*/

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_M 100000
int m, a, b;
int arr[MAX_M];

int binary_search(int target) {
	int idx = -1;
	int cnt = 0;
	int left = 0, right = m - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		cnt++;
		if (arr[mid] == target) {
			return cnt;
		}

		if (arr[mid] > target)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

int main() {
	cin >> m >> a >> b;
	for (int i = 0; i < m; i++) {
		arr[i] = i + 1;
	}
	int min_cnt = m, max_cnt = 0;
	for (int target = a; target <= b; target++) {
		int rslt = binary_search(target);
		if (rslt == -1) continue;
		min_cnt = min(min_cnt, rslt);
		max_cnt = max(max_cnt, rslt);
	}

	cout << min_cnt << " " << max_cnt << "\n";
	return 0;
}