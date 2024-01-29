#include <iostream>
#include <unordered_map>
#include <cctype>
using namespace std;

#define MAX_N 100000

int n, m;
unordered_map<string, int> string_to_index;
unordered_map<int, string> index_to_string;

bool isNumber(const string& str) {
    for (char const &c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        string_to_index[temp] = i + 1;
        index_to_string[i + 1] = temp;
    }

    for (int i = 0; i < m; i++) {
        string command; cin >> command;
        if (isNumber(command)) {
            int num = stoi(command);
            cout << index_to_string[num] << "\n";
        }
        else {
            cout << string_to_index[command] << "\n";
        }
    }
    return 0;
}