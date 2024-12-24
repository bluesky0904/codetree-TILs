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
vector<int> dist(MAX_N, INF); // 벡터로 변경
map<int, pair<int, int>> travel_list;
map<int, vector<int>> dist_cache; // 출발지별 최단 거리 캐싱

// 다익스트라 알고리즘 (캐싱 활용)
void set_source() {
    if (dist_cache.find(source) != dist_cache.end()) {
        dist = dist_cache[source]; // 캐싱된 결과 사용
        return;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    fill(dist.begin(), dist.end(), INF); // 초기화

    dist[source] = 0;
    pq.push({0, source});
    while (!pq.empty()) {
        int min_dist, min_idx;
        tie(min_dist, min_idx) = pq.top();
        pq.pop();

        if (dist[min_idx] != min_dist) continue;

        for (const auto& edge : graph[min_idx]) {
            int next_idx = edge.first;
            int next_dist = edge.second;

            int new_dist = min_dist + next_dist;
            if (dist[next_idx] > new_dist) {
                dist[next_idx] = new_dist;
                pq.push({new_dist, next_idx});
            }
        }
    }

    dist_cache[source] = dist; // 계산 결과 캐싱
}

// 코드트리 랜드 건설
void construct_land() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int v1, v2, d;
        cin >> v1 >> v2 >> d;
        if (v1 == v2) {
            if (graph[v1].empty() || graph[v1][0].second > d) {
                graph[v1].clear(); // 기존 간선 삭제
                graph[v1].push_back({v1, d}); // 최소 가중치 간선 추가
            }
        } else {
            graph[v1].push_back({v2, d});
            graph[v2].push_back({v1, d});
        }
    }
}

// 최적의 여행 상품 판매
void sell_product() {
    priority_queue<pair<int, int>> choose_list;

    for (const auto& [id, info] : travel_list) {
        int revenue = info.first;
        int dest = info.second;

        if (dist[dest] == INF || revenue < dist[dest]) continue; // 판매 불가 조건

        int profit = revenue - dist[dest];
        choose_list.push({profit, -id}); // id를 음수로 저장해 오름차순 처리
    }

    if (choose_list.empty()) {
        cout << -1 << "\n";
    } else {
        int id = -choose_list.top().second; // 가장 높은 우선순위 상품 선택
        cout << id << "\n";
        travel_list.erase(id); // 관리 목록에서 제거
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    source = 0;

    cin >> q;
    while (q--) {
        int command; cin >> command;
        if (command == 100) {
            construct_land();
            set_source();
        } else if (command == 200) {
            int id, revenue, dest;
            cin >> id >> revenue >> dest;
            travel_list[id] = make_pair(revenue, dest);
        } else if (command == 300) {
            int id; cin >> id;
            travel_list.erase(id);
        } else if (command == 400) {
            sell_product();
        } else if (command == 500) {
            cin >> source;
            set_source();
        }
    }

    return 0;
}
