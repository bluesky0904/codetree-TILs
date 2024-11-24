#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

#define MAX_N 1000
#define INF (int)1e9

vector<tuple<int, int, int>> graph[MAX_N + 1]; // {목적지, 버스 번호, 탑승료}
priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> pq;
// {현재 비용, 현재 소요 시간, 이전 버스 번호, 현재 위치}
int dist[MAX_N + 1]; // 최소 비용 저장
int time_dist[MAX_N + 1]; // 최소 비용에 해당하는 최소 시간 저장

int A, B, N;

int main() {
    cin >> A >> B >> N;
    for (int i = 1; i <= N; i++) {
        int fee, cnt, v1, v2;
        cin >> fee >> cnt;
        cin >> v1;
        for (int j = 2; j <= cnt; j++) {
            cin >> v2;
            graph[v1].push_back(make_tuple(v2, i, fee));
            graph[v2].push_back(make_tuple(v1, i, fee)); // 양방향 연결
            v1 = v2;
        }
    }

    fill(dist, dist + MAX_N + 1, INF);
    fill(time_dist, time_dist + MAX_N + 1, INF);

    dist[A] = 0;
    time_dist[A] = 0;
    pq.push({0, 0, 0, A});

    while (!pq.empty()) {
        int cur_fee, cur_time, cur_bus, cur_index;
        tie(cur_fee, cur_time, cur_bus, cur_index) = pq.top();
        pq.pop();

        if (dist[cur_index] < cur_fee || (dist[cur_index] == cur_fee && time_dist[cur_index] < cur_time))
            continue;

        for (auto& edge : graph[cur_index]) {
            int next_index, next_bus, next_fee;
            tie(next_index, next_bus, next_fee) = edge;

            int new_fee = cur_fee;
            int new_time = cur_time + 1;

            if (cur_bus != next_bus) {
                new_fee += next_fee;
            }

            if (dist[next_index] > new_fee || (dist[next_index] == new_fee && time_dist[next_index] > new_time)) {
                dist[next_index] = new_fee;
                time_dist[next_index] = new_time;
                pq.push({new_fee, new_time, next_bus, next_index});
            }
        }
    }

    if (dist[B] == INF) {
        cout << "-1 -1\n";
    } else {
        cout << dist[B] << " " << time_dist[B] << "\n";
    }
    return 0;
}