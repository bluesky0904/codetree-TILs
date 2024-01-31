#include <iostream>
#include <unordered_map>

using namespace std;

#define MAX_N 5000

// 변수 선언
int n;
int A[MAX_N], B[MAX_N], C[MAX_N], D[MAX_N];
unordered_map<int, int> freq;

int main() {
    // 입력:
    cin >> n;
    for(int i = 0; i < n; i++) cin >> A[i];
    for(int i = 0; i < n; i++) cin >> B[i];
    for(int i = 0; i < n; i++) cin >> C[i];
    for(int i = 0; i < n; i++) cin >> D[i];

    long long ans = 0;

    // A 수열에서 숫자 하나, B 수열에서 숫자 하나를 골랐을 때
    // 나올 수 있는 두 숫자의 합들을 hashmap에 기록해줍니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            freq[A[i] + B[j]]++;

    // C, D 수열을 순회하며 쌍을 만들어줍니다.
    // 앞서 계산한 hashmap을 이용하면
    // C, D 수열에서 고른 값으로 A, B와 쌍을 만들 때
    // 총합이 0이 되는 쌍의 개수를 쉽게 구할 수 있습니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            int diff = - C[i] - D[j];
            if(freq.count(diff) > 0)
                ans += freq[diff];
        }

    // 출력:
    cout << ans;

    return 0;
}