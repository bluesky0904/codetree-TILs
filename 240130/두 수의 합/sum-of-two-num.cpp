#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int countPairsWithSum(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }

    int count = 0;
    for (auto& entry : freq) {
        int num = entry.first;
        int complement = k - num;

        if (num == complement) {
            count += (entry.second * (entry.second - 1)) / 2;
        } else if (freq.find(complement) != freq.end()) {
            count += entry.second * freq[complement];
        }

        // Mark the pair as counted
        freq[num] = 0;
        freq[complement] = 0;
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