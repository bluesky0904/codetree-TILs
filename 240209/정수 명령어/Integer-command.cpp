#include <iostream>
#include <set>

using namespace std;

// 변수 선언
int t;
int n;

int main() {
    // 입력:
    cin >> t;
    while(t--) {
        set<int> s;
        cin >> n;
        
        for(int i = 0; i < n; i++) {
            char command; int x;
            cin >> command >> x;

            // treeset에 넣어줍니다.
            if(command == 'I')
                s.insert(x);
            // 큐가 비어있지 않을 경우에는 값을 제거해줍니다.
            else if(command == 'D' && (int) s.size() > 0) {
                // x가 1이면 최댓값을 삭제합니다.
                if(x == 1)
                    s.erase(*s.rbegin());
                // x가 -1이면 최솟값을 삭제합니다.
                else
                    s.erase(*s.begin());
            }
        }

        if((int) s.size() == 0)
            cout << "EMPTY" << endl;
        else
            cout << *s.rbegin() << " " << *s.begin() << endl;
    }

    return 0;
}