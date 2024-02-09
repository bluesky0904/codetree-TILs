#include <iostream>
#include <set>

#define MAX_N 100000

using namespace std;

// 변수 선언
int n, m;
int arr[MAX_N];

set<int> seats;

int main() {
    // 입력:
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    // 1번부터 m번까지 전부 비어져 있으므로
    // 빈 위치를 treeset으로 관리합니다.
    for(int i = 1; i <= m; i++)
        seats.insert(i);

    // 답을 구해줍니다.
    int ans = 0;

    // 순서대로 앉혀봅니다.
    // 최선의 자리 선택은
    // ai보다 같거나 작은 최대 위치에 자리배치를 하는 것입니다.
    for(int i = 0; i < n; i++) {
        // ai보다 큰 최초의 위치를 먼저 찾습니다.
        set<int>::iterator idx = seats.upper_bound(arr[i]);
        
        // 만약 큰 최초의 위치가 
        // 첫 번째 위치가 아니라면,
        // 바로 전 위치가
        // ai보다 같거나 작은 최대 위치가 구해지므로,
        // 해당 위치에 사람을 앉혀줍니다.
        if(idx != seats.begin()) {
            idx--;
            seats.erase(*idx);
            
            // 답을 갱신해줍니다.
            ans++;
        }
        else
            break;
    }

    cout << ans;
    return 0;
}