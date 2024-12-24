#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <set>
using namespace std;

#define MAX_N 2000
#define INF (int)1e9

int q, n, m;
int source;
vector<pair<int, int>> graph[MAX_N];
vector<int> dist(MAX_N, INF); // 최단 거리
map<int, pair<int, int>> travel_list; // 상품 목록
priority_queue<tuple<int, int, int>> pq; // (profit, -id, dest) 우선순위 큐

// 다익스트라 알고리즘
void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_pq;
    fill(dist.begin(), dist.end(), INF);

    dist[start] = 0;
    min_pq.push({0, start});
    while (!min_pq.empty()) {
        int cur_dist, cur_node;
        tie(cur_dist, cur_node) = min_pq.top();
        min_pq.pop();

        if (dist[cur_node] < cur_dist) continue;

        for (const auto& edge : graph[cur_node]) {
            int next_node = edge.first;
            int weight = edge.second;

            if (dist[next_node] > cur_dist + weight) {
                dist[next_node] = cur_dist + weight;
                min_pq.push({dist[next_node], next_node});
            }
        }
    }
}

// 우선순위 큐 갱신
void update_priority_queue() {
    priority_queue<tuple<int, int, int>> new_pq;

    for (const auto& [id, info] : travel_list) {
        int revenue = info.first;
        int dest = info.second;

        if (dist[dest] == INF || revenue < dist[dest]) continue; // 판매 불가 상품
        int profit = revenue - dist[dest];
        new_pq.push({profit, -id, dest});
    }

    pq = move(new_pq); // 업데이트된 우선순위 큐로 교체
}

// 코드트리 랜드 건설
void construct_land() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int v1, v2, d;
        cin >> v1 >> v2 >> d;
        graph[v1].push_back({v2, d});
        graph[v2].push_back({v1, d});
    }
    dijkstra(source);
    update_priority_queue();
}

// 최적의 여행 상품 판매
void sell_product() {
    while (!pq.empty()) {
        auto [profit, neg_id, dest] = pq.top();
        int id = -neg_id;
        pq.pop();

        // 유효성 검사 (삭제된 상품 또는 업데이트된 dist 확인)
        if (travel_list.find(id) == travel_list.end() || dist[dest] == INF) continue;
        if (travel_list[id].first - dist[dest] != profit) continue;

        // 상품 판매
        cout << id << "\n";
        travel_list.erase(id);
        return;
    }
    cout << -1 << "\n";
}

// 메인 함수
int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    source = 0;
    cin >> q;
    while (q--) {
        int command;
        cin >> command;
        if (command == 100) {
            construct_land();
        } else if (command == 200) {
            int id, revenue, dest;
            cin >> id >> revenue >> dest;
            travel_list[id] = {revenue, dest};
            update_priority_queue();
        } else if (command == 300) {
            int id;
            cin >> id;
            travel_list.erase(id);
            update_priority_queue();
        } else if (command == 400) {
            sell_product();
        } else if (command == 500) {
            cin >> source;
            dijkstra(source);
            update_priority_queue();
        }
    }

    return 0;
}
