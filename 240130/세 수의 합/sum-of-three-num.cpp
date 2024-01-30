#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

#define MAX_N 1000

int main() {
    int n, k;
    cin >> n >> k;
    unordered_map<int, int> freq;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        freq[nums[i]]++;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        freq[nums[i]]--;  // 현재 숫자 제외
        for (int j = i + 1; j < n; j++) {
            freq[nums[j]]--;  // 다른 숫자 제외
            int diff = k - nums[i] - nums[j];
            if (freq.find(diff) != freq.end()) {
                ans += freq[diff];
            }
            freq[nums[j]]++;  // 다른 숫자 복원
        }
        freq[nums[i]]++;  // 현재 숫자 복원
    }

    cout << ans / 3 << endl;  // 각 쌍이 세 번씩 계산되므로 3으로 나눔
    return 0;
}