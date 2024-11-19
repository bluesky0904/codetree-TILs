#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <functional>
using namespace std;

#define MAX_N 100000

int N;
int arr[MAX_N];
int sum = 0;
double max_avg;
priority_queue<int, vector<int>, greater<>> pq;

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sum += arr[N - 1];
	pq.push(arr[N - 1]);
	for (int i = N - 2; i >= 1; i--) {
		pq.push(arr[i]);
		sum += arr[i];
		double avg = double(sum - pq.top()) / (N - i - 1);
		if (max_avg < avg) max_avg = avg;
	}

	cout << fixed << setprecision(2) << max_avg << "\n";
	return 0;
}