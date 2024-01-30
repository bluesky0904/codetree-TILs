#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

#define MAX_N 100000
int n, m;
string arr[MAX_N+1];
unordered_map<string, int> mapper;

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        mapper[arr[i]] = i;
    }
    
    while (m--) {
        string command; cin >> command;
        if ('0' <= command[0] && command[0] <= '9') cout << arr[stoi(command)] << "\n";
        else cout << mapper[command] << "\n";
    }
}