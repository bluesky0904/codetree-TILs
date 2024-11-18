#include <iostream>
#include <queue>
using namespace std;

#define MAX_N 1000

int n, m;
priority_queue<int> pq;

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        pq.push(x);
    }

    while(m--){
        int x;
        x = pq.top();
        pq.pop();
        pq.push(x-1);
    }

    cout << pq.top() << "\n";
    return 0;
}