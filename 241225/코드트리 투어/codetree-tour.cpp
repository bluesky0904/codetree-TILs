#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define MAX_N 2000
#define INF (int)1e9

int q, n, m;
int source;
vector<pair<int, int>> graph[MAX_N];
int dist[MAX_N];
unordered_map<int, pair<int, int>> travel_list; // id -> {revenue, dest}
unordered_set<int> deleted_ids; // Lazy deletion for removed IDs

struct Product {
    int id;
    int profit; // revenue - cost

    // Custom comparator for priority queue (max heap)
    bool operator<(const Product& other) const {
        if (profit == other.profit)
            return id > other.id; // Smaller ID has higher priority
        return profit < other.profit; // Higher profit first
    }
};

priority_queue<Product> pq; // Priority queue for selecting optimal product

void construct_land() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int v1, v2, d;
        cin >> v1 >> v2 >> d;
        graph[v1].push_back({v2, d});
        graph[v2].push_back({v1, d});
    }
}

void rebuild_priority_queue() {
    // Clear the existing priority queue
    while (!pq.empty()) pq.pop();

    // Recalculate profit for all products and add them back to the queue
    for (const auto& entry : travel_list) {
        int id = entry.first;
        int revenue = entry.second.first;
        int dest = entry.second.second;

        if (dist[dest] != INF && revenue >= dist[dest]) {
            int profit = revenue - dist[dest];
            pq.push({id, profit});
        }
    }
}

void set_source() {
    // Reset distances and calculate shortest paths from the new source
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    fill(dist, dist + n, INF);
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int min_idx, min_dist;
        tie(min_dist, min_idx) = pq.top();
        pq.pop();

        if (dist[min_idx] != min_dist) continue;

        for (const auto& edge : graph[min_idx]) {
            int next_idx = edge.first, next_dist = edge.second;
            int new_dist = min_dist + next_dist;
            if (dist[next_idx] > new_dist) {
                dist[next_idx] = new_dist;
                pq.push({new_dist, next_idx});
            }
        }
    }

    // Rebuild priority queue based on updated distances
    rebuild_priority_queue();
}



void add_product(int id, int revenue, int dest) {
    travel_list[id] = {revenue, dest};
    if (dist[dest] != INF && revenue >= dist[dest]) {
        int profit = revenue - dist[dest];
        pq.push({id, profit});
    }
}

void delete_product(int id) {
    travel_list.erase(id);
    deleted_ids.insert(id); // Mark as deleted
}

void sell_product() {
    while (!pq.empty()) {
        Product top = pq.top();
        pq.pop();

        // Skip invalid products
        if (deleted_ids.count(top.id) || travel_list.find(top.id) == travel_list.end())
            continue;

        // Output the ID of the optimal product
        cout << top.id << "\n";
        delete_product(top.id); // Remove from travel_list
        return;
    }

    // No valid product found
    cout << -1 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> q;
    source = 0;

    while (q--) {
        int command;
        cin >> command;

        if (command == 100) {
            construct_land();
            set_source();
        } else if (command == 200) {
            int id, revenue, dest;
            cin >> id >> revenue >> dest;
            add_product(id, revenue, dest);
        } else if (command == 300) {
            int id;
            cin >> id;
            delete_product(id);
        } else if (command == 400) {
            sell_product();
        } else if (command == 500) {
            cin >> source;
            set_source();
        }
    }

    return 0;
}
