#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <cmath>
using namespace std;

int n;

priority_queue<int> pq;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x > 0) pq.push(x);
        else {
            if (pq.empty()) cout << 0 << "\n";
            else {
                cout << pq.top() << "\n";
                pq.pop();
            }
        }
    }

    return 0;
}