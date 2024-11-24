#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

#define MAX_N 1000
#define INF (long long)1e18

// {다음 지점, 버스 번호, 탑승료, 현재 순서}
struct Edge {
    int next_index;
    int bus_number;
    long long fee;
    int order;
};

vector<Edge> graph[MAX_N + 1]; // 그래프 정의
priority_queue<tuple<long long, long long, int, int, int>, vector<tuple<long long, long long, int, int, int>>, greater<>> pq;
// {현재 비용, 현재 시간, 현재 버스 번호, 현재 지점, 노선 순서}

pair<long long, long long> dist[MAX_N + 1]; // {최소 비용, 최소 시간}

int A, B, N;

int main() {
    cin >> A >> B >> N;

    // 그래프 입력
    for (int i = 1; i <= N; i++) {
        long long fee;
        int cnt;
        cin >> fee >> cnt;

        vector<int> stops(cnt);
        for (int j = 0; j < cnt; j++) {
            cin >> stops[j];
        }

        for (int j = 0; j < cnt - 1; j++) {
            graph[stops[j]].push_back({stops[j + 1], i, fee, j + 1}); // 순서대로 간선 연결
        }
    }

    // 거리 초기화
    for (int i = 1; i <= MAX_N; i++) {
        dist[i] = {INF, INF};
    }

    dist[A] = {0, 0};
    pq.push({0, 0, 0, A, 0}); // {비용, 시간, 버스 번호, 현재 지점, 순서}

    // 다익스트라 알고리즘
    while (!pq.empty()) {
        long long cur_fee, cur_time;
        int cur_bus, cur_index, cur_order;
        tie(cur_fee, cur_time, cur_bus, cur_index, cur_order) = pq.top();
        pq.pop();

        if (dist[cur_index] < make_pair(cur_fee, cur_time)) {
            continue;
        }

        for (const auto& edge : graph[cur_index]) {
            int next_index = edge.next_index;
            int next_bus = edge.bus_number;
            long long next_fee = edge.fee;
            int next_order = edge.order;

            long long new_fee = cur_fee;
            long long new_time = cur_time + 1;

            // 다른 버스로 환승할 경우 비용 추가
            if (cur_bus != next_bus) {
                new_fee += next_fee;
            }

            // 마지막 지점에서 내려야 함
            if (next_order == 1) { // 노선 시작점에서만 환승 가능
                new_fee = cur_fee + next_fee;
            }

            // 최소 비용과 시간 갱신
            if (dist[next_index] > make_pair(new_fee, new_time)) {
                dist[next_index] = {new_fee, new_time};
                pq.push({new_fee, new_time, next_bus, next_index, next_order});
            }
        }
    }

    // 결과 출력
    if (dist[B].first == INF) {
        cout << "-1 -1\n";
    } else {
        cout << dist[B].first << " " << dist[B].second << "\n";
    }

    return 0;
}