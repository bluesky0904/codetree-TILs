#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int N;
priority_queue<int> pq;

int main() {
    cin >> N;
    while (N--) {
        char command[6];
        int x;
        cin >> command;
        if (strcmp(command, "push") == 0) {
            cin >> x;
            pq.push(x);
        } else if (strcmp(command, "pop") == 0) {
            if (!pq.empty()) {
                cout << pq.top() << "\n";
                pq.pop();
            } else {
                cout << "Queue is empty\n";
            }
        } else if (strcmp(command, "size") == 0) {
            cout << pq.size() << "\n";
        } else if (strcmp(command, "empty") == 0) {
            cout << pq.empty() << "\n";
        } else {
            if (!pq.empty()) {
                cout << pq.top() << "\n";
            } else {
                cout << "Queue is empty\n";
            }
        }
    }

    return 0;
}