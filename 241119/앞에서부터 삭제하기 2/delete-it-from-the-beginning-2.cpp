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
        int x;
        cin >> x;
        v.push_back(x);
    }

    priority_queue<int, vector<int>, greater<>> pq;  // 최소값을 관리하는 우선순위 큐

    // 초기 설정: 첫 번째 구간을 처리
    for (int i = 1; i < N; i++) {
        pq.push(v[i]);
    }
    pq.pop();  // 최소값 제거

    double sum = 0;
    int count = pq.size();
    // 첫 구간의 합 계산
    for (priority_queue<int, vector<int>, greater<>> temp_pq = pq; !temp_pq.empty(); temp_pq.pop()) {
        sum += temp_pq.top();
    }
    avg_v.push(sum / count);

    // 이후 구간을 하나씩 이동하며 처리
    for (int k = 2; k <= N - 2; k++) {
        sum -= pq.top();  // 가장 작은 값을 제외
        pq.pop();
        pq.push(v[k + N - k - 1]);  // 새로운 원소 추가
        sum += v[k + N - k - 1];

        avg_v.push(sum / count);  // 새로운 평균 추가
    }

    cout << fixed << setprecision(2) << avg_v.top() << "\n";
    return 0;
}
