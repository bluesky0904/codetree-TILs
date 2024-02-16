#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> nums;
int ans = 0;

// cur_idx: 현재 탐색하는 인덱스, count: 현재까지 선택한 숫자의 개수, cur_xor: 현재까지의 XOR 결과
void findMaxXor(int cur_idx, int count, int cur_xor) {
    // m개를 모두 선택했으면, 최댓값을 갱신하고 반환
    if (count == m) {
        ans = max(ans, cur_xor);
        return;
    }

    // 더 이상 선택할 수 있는 숫자가 없으면 종료
    if (cur_idx == n) return;

    // 현재 인덱스의 숫자를 선택하는 경우
    findMaxXor(cur_idx + 1, count + 1, cur_xor ^ nums[cur_idx]);

    // 현재 인덱스의 숫자를 선택하지 않는 경우
    findMaxXor(cur_idx + 1, count, cur_xor);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    nums.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    findMaxXor(0, 0, 0); // 초기 상태에서는 아무 숫자도 선택하지 않았으므로, XOR 결과는 0입니다.

    cout << ans << endl;
    return 0;
}