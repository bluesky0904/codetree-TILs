#include <iostream>
#include <unordered_set>

using namespace std;

// 변수 선언
int n, m;
unordered_set<int> s;

int main() {
    // 입력:
    cin >> n;

    // 수열 a의 원소를 전부 HashSet에 넣어줍니다.
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }

    cin >> m;

    // 수열 b의 각 원소가 수열 a에 있는지 확인합니다.
    for(int i = 0; i < m; i++) {
        int x;
        cin >> x;

        // 수열 a 안에 있다면 1을, 없다면 0을 출력합니다.
        cout << (int)(s.find(x) != s.end()) << endl;
    }
    return 0;
}