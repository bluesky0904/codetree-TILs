#include <iostream>
#include <iomanip> // std::fixed와 std::setprecision을 사용하기 위해 필요
#include <map>
using namespace std;

int n;
map<string, int> m;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        m[s]++;
    }

    int total = 0;
    for (auto it = m.begin(); it != m.end(); it++) {
        total += it->second;
    }

    for (auto it = m.begin(); it != m.end(); it++) {
        // 부동 소수점 나눗셈을 사용하고, 결과를 소수점 4자리까지 반올림
        cout << fixed << setprecision(4);
        cout << it->first << " " << (double)(it->second) * 100 / total << "\n";
    }
}