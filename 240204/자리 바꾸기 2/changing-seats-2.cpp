#include <iostream>
#include <unordered_set>
using namespace std;

#define MAX_N 100000
#define MAX_K 100000

// 변수 선언
int n, k;
int a[MAX_K], b[MAX_K];
int arr[MAX_N + 1];
int ans[MAX_N + 1];
unordered_set<int> s[MAX_N + 1];

int main(){
    // 입력:
    cin >> n >> k;
    for(int i = 0; i < k; i++)
        cin >> a[i] >> b[i];
    
    // 시작 array를 arr에 표시합니다.
    for(int i = 1; i <= n; i++) {
        arr[i] = i;
        // 각 i 숫자가 위치할 수 있는 자리를 HashSet에 넣어 저장합니다.
        s[i].insert(i);
        ans[i] = 1;
    }

    // 3k번 자리를 바꿉니다.
    for(int cnt = 0; cnt < 3; cnt++) {
        for(int i = 0; i < k; i++) {
            // a[i]와 b[i]의 자리를 바꿔줍니다.
            // 이때 자리가 변화한 값은 arr[a[i]]와 arr[b[i]]밖에 없습니다.
            // 이 값들만 새로운 자리를 HashSet에 넣어 저장합니다.
            swap(arr[a[i]], arr[b[i]]);

            if(s[arr[a[i]]].find(a[i]) == s[arr[a[i]]].end()) {
                s[arr[a[i]]].insert(a[i]);
                ans[arr[a[i]]]++;
            }
            
            if(s[arr[b[i]]].find(b[i]) == s[arr[b[i]]].end()) {
                s[arr[b[i]]].insert(b[i]);
                ans[arr[b[i]]]++;
            }
        }
    }
    
    // 3k번 자리를 바꾸면서 각 숫자들이 위치할 수 있는 값들의 개수를 ans 배열에서 확인합니다.
    for(int i = 1; i <= n; i++)
        cout << ans[i] << endl;
    return 0;
}