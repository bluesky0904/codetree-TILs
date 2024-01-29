#include <iostream>
#include <unordered_map>

#define MAX_N 100000

using namespace std;

// 변수 선언
int n, m;
int arr[MAX_N];
unordered_map<int, int> freq;

int main() {
    // 입력:
    cin >> n >> m;

    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    // 각 숫자가 몇 번씩 나왔는지를
    // hashmap에 기록해줍니다.
    for(int i = 0; i < n; i++) {
        // 처음 나온 숫자라면 1을 직접 적어줘야 합니다.
        if(freq.find(arr[i]) == freq.end())
            freq[arr[i]] = 1;
        // 이미 나와있던 숫자라면 1을 더해줍니다.
        else
            freq[arr[i]]++;
    }

    // m개의 질의에 대해
    // 몇 번씩 나왔는지를 출력합니다.
    for(int i = 0; i < m; i++) {
        int num;
        cin >> num;

        // 처음 나온 숫자라면 0을 출력합니다.
        if(freq.find(num) == freq.end())
            cout << 0 << " ";
        // 나온 적이 있는 숫자라면, 빈도수를 출력해줍니다.
        else
            cout << freq[num] << " ";
    }
    return 0;
}