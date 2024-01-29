#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

int n, m;
string words[MAX_N+1];
unordered_map<string, int> string_to_num;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> words[i];
        string_to_num[words[i]] = i;
    }
    while (m--) {
        string key; cin >> key;
        if ('0' <= key[0] && key[0] <= '9') cout << words[stoi(key)] << "\n";
        else cout << string_to_num[key] << "\n";
    }
    return 0;
}