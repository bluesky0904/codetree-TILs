#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int countPairsWithSum(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    int count = 0;

    for (int num : nums) {
        freq[num]++;
    }

    for (int num : nums) {
        int target = k - num;
        if (freq.find(target) != freq.end()) {
            count += freq[target];
            if (target == num) {
                count--; // 같은 숫자를 두 번 세는 것을 방지
            }
        }
    }
    
    return count / 2; // 각 쌍이 두 번씩 세어졌으므로 2로 나눔
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << countPairsWithSum(nums, k) << endl;

    return 0;
}