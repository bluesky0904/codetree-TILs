#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

#define MAX_N 100000

using namespace std;

// 변수 선언
int n;
string words[MAX_N];
unordered_map<string, int> freq;

int ans; // 가장 많이 나온 횟수를 기록합니다.

int main() {
    // 입력:
    cin >> n;

    for(int i = 0; i < n; i++)
        cin >> words[i];
    
    // 각 문자열이 몇 번씩 나왔는지를
    // hashmap에 기록해줍니다.
    for(int i = 0; i < n; i++) {
        // 처음 나온 문자열이라면 1을 직접 적어줘야 합니다.
        if(freq.find(words[i]) == freq.end())
            freq[words[i]] = 1;
        // 이미 나와있던 문자열이라면 1을 더해줍니다.
        else
            freq[words[i]]++;
        
        // 최댓값을 갱신합니다.
        ans = max(ans, freq[words[i]]);
    }

    cout << ans;
    return 0;
}