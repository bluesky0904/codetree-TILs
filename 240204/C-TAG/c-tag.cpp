#include <iostream>
#include <unordered_set>
using namespace std;

#define MAX_N 500

// 변수 선언
int n, m;
int ans;
string A[MAX_N], B[MAX_N];
unordered_set<string> s;

bool TestLocation(int x, int y, int z) {
    // x, y, z번째 자릿수를 선택했을 때 A와 B 그룹이
    // 완벽하게 구분되면 true, 그렇지 않다면 false를 반환합니다.
    s.clear();

    // A의 원소를 전부 HashSet에 넣어줍니다.
    for(int i = 0; i < n; i++) {
        s.insert(A[i].substr(x, 1) + A[i].substr(y, 1) + A[i].substr(z, 1));
    }

    // B의 원소 중 하나라도 A와 같은 경우가 있다면
    // A와 B를 구분해낼 수 없습니다.
    for(int i = 0; i < n; i++) {
        if(s.find(B[i].substr(x, 1) + B[i].substr(y, 1) + B[i].substr(z, 1)) != s.end())
            return false;
    }

    // 모든 B의 원소가 A와 다르다면 A와 B를 구분해낼 수 있습니다.
    return true;
}

int main() {
    // 입력:
    cin >> n >> m;

    for(int i = 0; i < n; i++)
        cin >> A[i];
    
    for(int i = 0; i < n; i++)
        cin >> B[i];

    // 서로 다른 세 자리의 조합을 모두 순회합니다.
    for (int i = 0; i < m; i++)
        for (int j = i + 1; j < m; j++)
            for (int k = j + 1; k < m; k++)
                // i, j, k 번째 자리를 선택했을 때 두 그룹을
                // 완벽하게 구분할 수 있는지 확인합니다.
                if (TestLocation(i, j, k)) ans++;
    
    // 두 그룹을 구분해낼 수 있는 조합 수를 출력합니다.
    cout << ans;
    return 0;
}