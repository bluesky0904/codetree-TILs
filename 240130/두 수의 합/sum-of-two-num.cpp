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
        if (freq[num] == 0) continue;

        freq[num]--;
        int complement = k - num;

        if (freq.find(complement) != freq.end() && freq[complement] > 0) {
            count++;
            freq[complement]--;
        }
    }

    return count;
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