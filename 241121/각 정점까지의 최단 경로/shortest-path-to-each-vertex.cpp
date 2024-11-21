#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

#define MAX_N 5

vector<pair<int, int>> graph[MAX_N + 1];
priority_queue<pair<int, int>> pq;

int dist[MAX_N + 1];

int n, m, k;

int main() {
    cin >> n >> m >> k;

    for (int i = 1; i <= m; i++) {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        graph[v1].push_back(make_pair(v2, w));
        graph[v2].push_back(make_pair(v1, w));
    }

    for (int i = 1; i <= n; i++)
        dist[i] = (int)1e9;

    dist[k] = 0;
    pq.push(make_pair(-0, k)); // (-거리, 정점번호) 형태로 넣어주어야 함.

    while (!pq.empty()) {
        int min_dist, min_index;
        tie(min_dist, min_index) = pq.top();
        pq.pop();

        min_dist = -min_dist;

        if (min_dist != dist[min_index]) continue; // 방문 여부 표시

        for (int j = 0; j < (int)graph[min_index].size(); j++) {
            int target_index, target_dist;
            tie(target_index, target_dist) = graph[min_index][j];

            int new_dist = dist[min_index] + target_dist;
            if (dist[target_index] > new_dist) {
                dist[target_index] = new_dist;
                pq.push(make_pair(-new_dist, target_index));
            }
        }
    }

    for (int i = 1; i <= n; i++)
        if (dist[i] == 1e9) dist[i] = -1;

    for (int i = 1; i <= n; i++)
        cout << dist[i] << "\n";

    return 0;
}