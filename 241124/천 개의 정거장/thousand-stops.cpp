#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
using namespace std;

#define INF (long long)1e18
#define MAX_N 1000

// 간선 구조 {다음 지점, 버스 번호, 탑승료, 노선 순서}
struct Edge {
    int next_index, bus_number, order;
    long long fee;
};

// 그래프 정의
vector<Edge> graph[MAX_N + 1];

// 우선순위 큐 {현재 비용, 현재 시간, 현재 버스 번호, 현재 지점, 노선 순서}
priority_queue<tuple<long long, int, int, int, int>, vector<tuple<long long, int, int, int, int>>, greater<>> pq;

// 최소 비용 및 시간 기록
pair<long long, int> dist[MAX_N + 1][MAX_N + 1]; // [지점][버스 번호]

int A, B, N;

int main() {
    cin >> A >> B >> N;

    // 그래프 입력 처리
    for (int i = 1; i <= N; i++) {
        long long fee;
        int cnt;
        cin >> fee >> cnt;

        vector<int> stops(cnt);
        for (int j = 0; j < cnt; j++) {
            cin >> stops[j];
        }

        for (int j = 0; j < cnt - 1; j++) {
            graph[stops[j]].push_back({stops[j + 1], i, j + 1, fee}); // 순서대로 간선 추가
        }
    }

    // 거리 초기화
    for (int i = 1; i <= MAX_N; i++) {
        for (int j = 1; j <= N; j++) {
            dist[i][j] = {INF, INF};
        }
    }

    // 시작점 초기화
    for (int i = 1; i <= N; i++) {
        dist[A][i] = {0, 0};
    }
    pq.push({0, 0, 0, A, 0}); // {비용, 시간, 버스 번호, 현재 지점, 순서}

    // 다익스트라 알고리즘
    while (!pq.empty()) {
        long long cur_fee;
        int cur_time, cur_bus, cur_index, cur_order;
        tie(cur_fee, cur_time, cur_bus, cur_index, cur_order) = pq.top();
        pq.pop();

        // 현재 노드에서 갈 수 있는 모든 간선을 탐색
        for (const auto& edge : graph[cur_index]) {
            int next_index = edge.next_index;
            int next_bus = edge.bus_number;
            int next_order = edge.order;
            long long next_fee = edge.fee;

            long long new_fee = cur_fee;
            int new_time = cur_time + 1;

            // 다른 버스로 환승 시 비용 추가
            if (cur_bus != next_bus) {
                new_fee += next_fee;
            }

            // 현재 경로가 더 최적이라면 갱신
            if (dist[next_index][next_bus] > make_pair(new_fee, new_time)) {
                dist[next_index][next_bus] = {new_fee, new_time};
                pq.push({new_fee, new_time, next_bus, next_index, next_order});
            }
        }
    }

    // 결과 출력
    pair<long long, int> result = {INF, INF};
    for (int i = 1; i <= N; i++) {
        result = min(result, dist[B][i]);
    }

    if (result.first == INF) {
        cout << "-1 -1\n"; // 도달 불가능
    } else {
        cout << result.first << " " << result.second << "\n"; // 최소 비용과 시간 출력
    }

    return 0;
}