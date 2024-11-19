#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <iomanip>
using namespace std;

int N;
vector<int> v;
priority_queue<double> avg_v;

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x; cin >> x;
		v.push_back(x);
	}

	for (int k = 1; k <= N - 2; k++) {
		priority_queue<int, vector<int>, greater<>> pq;
		for (int i = k; i < N; i++) {
			pq.push(v[i]);
		}
		pq.pop();
		double sum = 0;
		int count = 0;
		while (!pq.empty()) {
			sum += pq.top();
			pq.pop();
			count++;
		}
		avg_v.push(sum / count);
	}

	cout << fixed << setprecision(2) << avg_v.top() << "\n";
	return 0;
}