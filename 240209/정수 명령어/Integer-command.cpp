#include <iostream>
#include <set>
using namespace std;

int t, k;
set<int> s;

int main() {
    cin >> t;
    while (t--) {
        s.clear();

        cin >> k;
        while (k--) {
            char c; int n; cin >> c >> n;
            if (c == 'D') {
                if (!s.empty()) {
                    if (n == -1) s.erase(s.begin());
                    else  s.erase(prev(s.end()));
                }
            }
            else if (c == 'I') {
                s.insert(n);
            }
        }
        if (!s.empty()) cout << *s.rbegin() << " " << *s.begin() << "\n";
        else cout << "EMPTY" << "\n";
    }
    
    return 0;
}