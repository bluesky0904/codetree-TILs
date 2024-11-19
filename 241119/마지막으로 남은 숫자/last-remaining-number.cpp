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
        pq.push(x);
    }

    while (pq.size() >= 2) {
        int x, y;
        x = pq.top();
        pq.pop();
        y = pq.top();
        pq.pop();
        if (x != y) pq.push(abs(x - y));
    }

    if (pq.empty()) cout << -1 << "\n";
    else cout << pq.top() << "\n";
    return 0;
}