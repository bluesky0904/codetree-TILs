#include <iostream>
#include <vector>
#include <queue>
#include<functional>
#include <cmath>
using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int m; cin >> m;
		priority_queue<int> max_heap;
		priority_queue<int, vector<int>, greater<>> min_heap;
		int num;
		cin >> num;
		max_heap.push(num);
		cout << max_heap.top() << " ";
		for (int i = 2; i <= m; i++) {
			cin >> num;
			if (num <= max_heap.top())
				max_heap.push(num);
			else min_heap.push(num);

			while (max_heap.size() > min_heap.size() + 1) {
				min_heap.push(max_heap.top());
				max_heap.pop();
			}
			while (min_heap.size() > max_heap.size()) {
				max_heap.push(min_heap.top());
				min_heap.pop();
			}

			if (i % 2 == 1) cout << max_heap.top() << " ";
		}
		cout << "\n";
	}
}