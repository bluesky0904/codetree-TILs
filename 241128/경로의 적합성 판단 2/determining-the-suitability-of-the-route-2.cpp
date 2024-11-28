#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// Union-Find 클래스
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // 경로 압축
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// BFS로 경로 존재 여부 확인
bool bfs(int start, int target, unordered_map<int, vector<int>>& graph, int n) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == target) {
            return true;
        }

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return false;
}

int main() {
    int n = 4; // 노드 수
    vector<pair<int, int>> edges = {{3, 1}, {3, 4}, {4, 2}}; // 간선
    vector<int> order = {1, 4}; // 이동 순서

    // Union-Find 초기화
    UnionFind uf(n + 1); // 1-based index 사용

    // 그래프 인접 리스트 생성
    unordered_map<int, vector<int>> graph;
    for (auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        graph[u].push_back(v);
        graph[v].push_back(u);
        uf.unite(u, v); // Union-Find에 간선 추가
    }

    // 모든 노드가 같은 연결 요소에 속하는지 확인
    if (uf.find(order[0]) != uf.find(order[1])) {
        cout << "0" << endl; // 서로 다른 연결 요소
    } else {
        // BFS로 이동 가능 여부 확인
        bool canMove = bfs(order[0], order[1], graph, n);
        cout << (canMove ? "1" : "0") << endl; // 이동 가능 여부 출력
    }

    return 0;
}