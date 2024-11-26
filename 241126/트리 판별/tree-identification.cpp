#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

#define MAX_N 10000

vector<int> graph[MAX_N + 1];
int in_degree[MAX_N + 1];
bool visited[MAX_N + 1];
unordered_set<int> nodes;

void reset(int n) {
    for (int i = 0; i <= n; i++) {
        graph[i].clear();
        in_degree[i] = 0;
        visited[i] = false;
    }
    nodes.clear();
}

bool is_tree(int m) {
    int root = -1;

    // 루트 노드 판별: 들어오는 간선(in_degree)이 0인 노드
    for (int node : nodes) {
        if (in_degree[node] == 0) {
            if (root != -1) return false; // 루트 노드가 2개 이상
            root = node;
        }
    }

    if (root == -1) return false; // 루트 노드가 없음

    // BFS로 모든 노드 탐색
    queue<int> q;
    q.push(root);
    visited[root] = true;

    int visited_count = 0;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        visited_count++;

        for (int next : graph[curr]) {
            if (visited[next]) return false; // 사이클 발생
            visited[next] = true;
            q.push(next);
        }
    }

    // 모든 노드 방문 확인
    if (visited_count != nodes.size()) return false;

    return true;
}

int main() {
    int m;
    cin >> m;

    reset(MAX_N);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        in_degree[b]++;
        nodes.insert(a);
        nodes.insert(b);
    }

    cout << (is_tree(m) ? 1 : 0) << "\n";
    return 0;
}
