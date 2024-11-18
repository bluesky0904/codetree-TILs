#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

int n;
priority_queue<int, vector<int>, greater<int>> pq;

int main(){
    cin >> n;
    while(n--){
        int x;
        cin >> x;
        if(x > 0) pq.push(x);
        else {
            if(!pq.empty()){
            cout << pq.top() << "\n";
            pq.pop();
            }
            else cout << 0 << "\n";
        }
    }
    return 0;
}