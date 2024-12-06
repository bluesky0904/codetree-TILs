#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits> // LLONG_MAX를 사용하기 위한 헤더 추가
using namespace std;

long long calculate_steps(long long target, long long m) {
    long long steps = 0;
    long long left = 1, right = m; // 탐색 범위 초기화
    while (left <= right) {
        long long mid = (left + right) / 2; // 중간값 계산
        steps++;
        if (mid == target) {
            break;
        } else if (mid > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return steps;
}

int main() {
    long long m, a, b;
    cin >> m >> a >> b;

    long long min_cnt = LLONG_MAX; // LLONG_MAX를 사용해 초기화
    long long max_cnt = 0; // 최댓값 초기화

    for (long long target = a; target <= b; target++) {
        long long steps = calculate_steps(target, m); // 이분 탐색 횟수 계산
        min_cnt = min(min_cnt, steps); // 최소 횟수 갱신
        max_cnt = max(max_cnt, steps); // 최대 횟수 갱신
    }

    cout << min_cnt << " " << max_cnt << "\n"; // 결과 출력
    return 0;
}
