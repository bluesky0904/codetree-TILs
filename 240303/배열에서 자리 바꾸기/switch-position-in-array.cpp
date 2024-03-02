#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void swapSubarrays(vector<int>& arr, int a, int b, int c, int d) {
    // 인덱스 찾기
    int startA = find(arr.begin(), arr.end(), a) - arr.begin();
    int endB = find(arr.begin(), arr.end(), b) - arr.begin();
    int startC = find(arr.begin(), arr.end(), c) - arr.begin();
    int endD = find(arr.begin(), arr.end(), d) - arr.begin();

    // 교환할 부분배열의 길이 계산
    int lenAB = endB - startA + 1;
    int lenCD = endD - startC + 1;

    // 부분배열을 임시 벡터에 저장
    vector<int> subAB(arr.begin() + startA, arr.begin() + endB + 1);
    vector<int> subCD(arr.begin() + startC, arr.begin() + endD + 1);

    // 교환할 부분배열 삭제
    arr.erase(arr.begin() + startC, arr.begin() + endD + 1);
    arr.erase(arr.begin() + startA, arr.begin() + endB + 1);

    // 인덱스 조정
    if(startA < startC) {
        startC -= lenAB;
    } else {
        startA -= lenCD;
    }

    // 임시 벡터에서 부분배열을 원래 배열에 삽입
    arr.insert(arr.begin() + startC, subAB.begin(), subAB.end());
    arr.insert(arr.begin() + startA, subCD.begin(), subCD.end());
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

    for (auto& num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}