#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 5000

int n;
int arr[4][MAX_N];
unordered_map<int, int> sumMap; // 두 배열의 합을 저장하기 위한 해시맵

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }

    // 첫 번째 배열과 두 번째 배열의 모든 가능한 합을 계산하고, 이를 sumMap에 저장합니다.
    for (int num1 = 0; num1 < n; num1++) {
        for (int num2 = 0; num2 < n; num2++) {
            sumMap[arr[0][num1] + arr[1][num2]]++;
        }
    }

    int ans = 0;
    // 세 번째 배열과 네 번째 배열의 모든 가능한 합에 대해, sumMap에서 그 합의 반대되는 값이 있는지 확인합니다.
    for (int num3 = 0; num3 < n; num3++) {
        for (int num4 = 0; num4 < n; num4++) {
            ans += sumMap[-(arr[2][num3] + arr[3][num4])];
        }
    }

    cout << ans << "\n";
    return 0;
}