#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// 변수 선언
unordered_map<char, int> freq;
string str;

int main() {
    // 입력:
    cin >> str;

    // 각 알파벳이 몇 번씩 나왔는지를
    // hashmap에 기록해줍니다.
    for(int i = 0; i < str.length(); i++) {
        freq[str[i]]++;
    }

    // 문자열을 앞에서부터 순회하여
    // 딱 1회만 등장한 알파벳을 찾습니다.
    for(int i = 0; i < str.length(); i++) {
        if(freq[str[i]] == 1) {
            // 만약 그런 알파벳이 존재한다면,
            // 알파벳을 출력하고 프로그램을 종료합니다.
            cout << str[i];
            return 0;
        }
    }

    // 문자열을 전부 순회할 때까지 프로그램이 종료되지
    // 않았으므로 그러한 문자가 없는 경우입니다.
    cout << "None";

    return 0;
}