#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> v(N);

    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    double max_avg = -1e9;  // 초기값을 작은 값으로 설정
    for (int K = 1; K <= N - 2; K++) {
        priority_queue<int, vector<int>, greater<int>> pq;
        double sum = 0;

        // K개의 요소를 제외한 나머지 요소들을 처리
        for (int i = K; i < N; i++) {
            pq.push(v[i]);
            sum += v[i];
        }

        // 가장 작은 값을 하나 제거
        if (!pq.empty()) {
            sum -= pq.top();
            pq.pop();
        }

        int count = N - K - 1; // 남은 요소 수
        double avg = sum / count;
        max_avg = max(max_avg, avg);
    }

    cout << fixed << setprecision(2) << max_avg << "\n";
    return 0;
}