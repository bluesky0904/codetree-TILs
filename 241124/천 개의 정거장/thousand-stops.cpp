#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

#define MAX_N 1000
#define INF (long long)1e17

// {목적지, 버스 번호, 탑승료}
vector<tuple<int, int, int>> graph[MAX_N + 1];

// {현재 비용, 현재 소요 시간, 현재 버스 번호, 현재 위치}
priority_queue<tuple<long long, long long, int, int>, vector<tuple<long long, long long, int, int>>, greater<>> pq;

pair<long long, long long> dist[MAX_N + 1]; // {최소 비용, 최소 시간}

int A, B, N;

int main() {
    cin >> A >> B >> N;

    // 그래프 초기화 및 입력 처리
    for (int i = 1; i <= N; i++) {
        int fee, cnt, v1, v2;
        cin >> fee >> cnt;
        cin >> v1;

        for (int j = 2; j <= cnt; j++) {
            cin >> v2;
            graph[v1].emplace_back(v2, i, fee); // {목적지, 버스 번호, 탑승료}
            v1 = v2;
        }
    }

    // 거리 배열 초기화
    for (int i = 1; i <= MAX_N; i++) {
        dist[i] = {INF, INF};
    }

    dist[A] = {0, 0};
    pq.push({0, 0, 0, A}); // {비용, 시간, 버스 번호, 현재 위치}

    // 다익스트라 알고리즘
    while (!pq.empty()) {
        long long cur_fee, cur_time;
        int cur_bus, cur_index;
        tie(cur_fee, cur_time, cur_bus, cur_index) = pq.top();
        pq.pop();

        // 이미 최적 비용과 시간이 더 작은 경우 스킵
        if (dist[cur_index] < make_pair(cur_fee, cur_time)) {
            continue;
        }

        // 현재 노드에서 갈 수 있는 모든 노드 탐색
        for (const auto& edge : graph[cur_index]) {
            int next_index, next_bus, next_fee;
            tie(next_index, next_bus, next_fee) = edge;

            long long new_fee = cur_fee;
            long long new_time = cur_time + 1;

            // 다른 버스로 환승하면 추가 비용 발생
            if (cur_bus != next_bus) {
                new_fee += next_fee;
            }

            // 비용과 시간을 동시에 비교하여 갱신
            if (dist[next_index] > make_pair(new_fee, new_time)) {
                dist[next_index] = {new_fee, new_time};
                pq.push({new_fee, new_time, next_bus, next_index});
            }
        }
    }

    // 출력
    if (dist[B] == make_pair(INF, INF)) {
        cout << "-1 -1\n"; // 도달 불가
    } else {
        cout << dist[B].first << " " << dist[B].second << "\n"; // 최소 비용, 최소 시간
    }

    return 0;
}