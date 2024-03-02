#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void swapSubarrays(vector<int>& arr, int a, int b, int c, int d) {
    // a, b, c, d 위치를 찾음 (0-based index)
    int start1 = find(arr.begin(), arr.end(), a) - arr.begin();
    int end1 = find(arr.begin(), arr.end(), b) - arr.begin();
    int start2 = find(arr.begin(), arr.end(), c) - arr.begin();
    int end2 = find(arr.begin(), arr.end(), d) - arr.begin();

    // 부분배열을 임시 벡터에 저장
    vector<int> temp1(arr.begin() + start1, arr.begin() + end1 + 1);
    vector<int> temp2(arr.begin() + start2, arr.begin() + end2 + 1);

    // 교환될 부분배열의 길이 차이 계산
    int lenDiff = (end2 - start2) - (end1 - start1);

    // 첫 번째 부분배열 삭제
    arr.erase(arr.begin() + start1, arr.begin() + end1 + 1);

    // 첫 번째 위치에 두 번째 부분배열 삽입
    arr.insert(arr.begin() + start1, temp2.begin(), temp2.end());

    // 두 번째 부분배열 삭제 (위치 조정 필요)
    if (start2 > start1) {
        start2 += lenDiff;
    }
    arr.erase(arr.begin() + start2, arr.begin() + start2 + temp1.size());

    // 두 번째 위치에 첫 번째 부분배열 삽입
    arr.insert(arr.begin() + start2, temp1.begin(), temp1.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        swapSubarrays(arr, a, b, c, d);
    }

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    return 0;
}