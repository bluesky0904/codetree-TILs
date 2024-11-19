#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> v(N);

    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    double max_avg = -1e9;  // 최대 평균값을 저장할 변수

    for (int K = 1; K <= N - 2; K++) {
        multiset<int> ms;  // 정렬된 상태를 유지하는 멀티셋
        double sum = 0;

        // K개의 요소를 제외한 나머지 요소들을 멀티셋에 추가
        for (int i = K; i < N; i++) {
            ms.insert(v[i]);
            sum += v[i];
        }

        // 가장 작은 값을 하나 제거
        sum -= *ms.begin();
        ms.erase(ms.begin());

        int count = N - K - 1; // 남은 요소 수
        double avg = sum / count;
        max_avg = max(max_avg, avg);
    }

    cout << fixed << setprecision(2) << max_avg << "\n";
    return 0;
}