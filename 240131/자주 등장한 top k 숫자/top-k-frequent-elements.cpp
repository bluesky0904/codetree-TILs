#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int n, k;
int arr[MAX_N];
unordered_map<int, int> freq;

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        freq[arr[i]]++;
    }

    vector<pair<int, int>> freq_vec;
    for (auto& p : freq) {
        freq_vec.push_back(make_pair(p.second, p.first));
    }

    sort(freq_vec.rbegin(), freq_vec.rend()); // 빈도수가 높은 순, 그리고 값이 큰 순으로 정렬

    for (int i = 0; i < k; i++) {
        cout << freq_vec[i].second << " "; // 가장 자주 등장하는 숫자부터 출력
    }
    cout << "\n";

    return 0;
}