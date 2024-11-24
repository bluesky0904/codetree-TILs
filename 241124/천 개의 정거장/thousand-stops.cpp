#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

#define MAX_N 1000
#define INF (int)1e9

// {다음 지점, 버스 번호, 탑승료}
vector<tuple<int, int, int>> graph[MAX_N + 1];

// {현재 비용, 현재 시간, 현재 버스 번호, 현재 위치}
priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> pq;

// 최소 비용 및 시간 기록
int dist[MAX_N + 1];
int time_dist[MAX_N + 1];

int A, B, N;

int main() {
    cin >> A >> B >> N;

    // 그래프 구성
    for (int i = 1; i <= N; i++) {
        int fee, cnt;
        cin >> fee >> cnt;

        vector<int> stops(cnt);
        for (int j = 0; j < cnt; j++) {
            cin >> stops[j];
        }

        // 노선 순서대로 간선 추가
        for (int j = 0; j < cnt - 1; j++) {
            graph[stops[j]].emplace_back(stops[j + 1], i, fee);
        }
    }

    // 거리 배열 초기화
    fill(dist, dist + MAX_N + 1, INF);
    fill(time_dist, time_dist + MAX_N + 1, INF);

    // 시작점 초기화
    dist[A] = 0;
    time_dist[A] = 0;
    pq.push({0, 0, 0, A}); // {비용, 시간, 버스 번호, 현재 지점}

    // 다익스트라 알고리즘
    while (!pq.empty()) {
        int cur_fee, cur_time, cur_bus, cur_index;
        tie(cur_fee, cur_time, cur_bus, cur_index) = pq.top();
        pq.pop();

        // 이미 더 짧은 경로가 있으면 스킵
        if (dist[cur_index] < cur_fee || (dist[cur_index] == cur_fee && time_dist[cur_index] < cur_time))
            continue;

        // 현재 지점에서 갈 수 있는 모든 간선을 확인
        for (const auto& edge : graph[cur_index]) {
            int next_index, next_bus, next_fee;
            tie(next_index, next_bus, next_fee) = edge;

            int new_fee = cur_fee;
            int new_time = cur_time + 1;

            // 다른 버스로 환승 시 탑승료 추가
            if (cur_bus != next_bus) {
                new_fee += next_fee;
            }

            // 최소 비용 및 시간 갱신
            if (dist[next_index] > new_fee || (dist[next_index] == new_fee && time_dist[next_index] > new_time)) {
                dist[next_index] = new_fee;
                time_dist[next_index] = new_time;
                pq.push({new_fee, new_time, next_bus, next_index});
            }
        }
    }

    // 결과 출력
    if (dist[B] == INF) {
        cout << "-1 -1\n"; // 도달 불가능
    } else {
        cout << dist[B] << " " << time_dist[B] << "\n"; // 최소 비용과 시간 출력
    }

    return 0;
}
