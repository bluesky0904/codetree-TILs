#include <iostream>
#include <vector>
#include <algorithm> // sort 함수를 사용하기 위함
#include <climits> // INT_MAX를 사용하기 위함
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // 수열 정렬
    sort(arr.begin(), arr.end());

    int minDiff = INT_MAX;
    int start = 0, end = 1;

    while (end < n) {
        int diff = arr[end] - arr[start];

        // 차이가 m 이상인 경우
        if (diff >= m) {
            minDiff = min(minDiff, diff); // 최소 차이 갱신
            start++; // 더 작은 차이를 찾아볼 수 있도록 시작 포인터 이동
        } else {
            end++; // 차이가 m 미만인 경우, 끝 포인터를 이동하여 차이 증가
        }

        // 시작 포인터와 끝 포인터가 교차하는 경우, 끝 포인터를 다시 앞으로 이동
        if (start == end) {
            end++;
        }
    }

    // 찾은 최소 차이 출력
    cout << minDiff << "\n";

    return 0;
}