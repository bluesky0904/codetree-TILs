#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

int n, k;
unordered_map<int, int> m;
int arr[MAX_N + 1];

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int num;
        cin >> num;
        arr[i] = num;
        m[num] = i;
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (m.find(k - arr[i]) != m.end() && m[k - arr[i]] > i) {
            cnt++;
            m.erase(arr[i]);       // 중복 방지
            m.erase(k - arr[i]);   // 쌍으로 이루어진 값 제거
        }
    }

    cout << cnt << "\n"; // cnt는 중복 없이 계산됨
    return 0;
}
