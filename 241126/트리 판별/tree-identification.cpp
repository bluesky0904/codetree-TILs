#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 10000

vector<int> edge[MAX_N + 1];
bool is_node[MAX_N + 1];
bool visited[MAX_N + 1];
int parent[MAX_N + 1];

int m;
int root;

void DFS(int root) {
    visited[root] = true; // 방문 체크를 호출 전에 수행
    for (int next_idx : edge[root]) {
        if (!visited[next_idx]) {
            DFS(next_idx);
        }
    }
}

int main() {
    cin >> m;

    int node_count = 0;
    fill(is_node, is_node + MAX_N + 1, false);
    fill(parent, parent + MAX_N + 1, -1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        if (i == 0) root = a;
        is_node[a] = is_node[b] = true; // 노드 존재 여부 갱신

        if (parent[b] == -1) {
            parent[b] = a; // 부모 설정
        } else {
            cout << 0 << "\n"; // 부모가 이미 있으면 트리가 아님
            return 0;
        }
        edge[a].push_back(b); // 간선 연결
    }

    // 루트 노드 탐색
    while (parent[root] != -1) {
        root = parent[root];
    }

    // 루트 노드 개수 확인
    int root_count = 0;
    for (int i = 0; i <= MAX_N; i++) {
        if (is_node[i] && parent[i] == -1) {
            root_count++;
        }
    }
    if (root_count != 1) { // 루트가 여러 개면 트리가 아님
        cout << 0 << "\n";
        return 0;
    }

    // DFS로 연결된 모든 노드 방문
    fill(visited, visited + MAX_N + 1, false);
    DFS(root);

    // 방문되지 않은 노드가 있으면 트리가 아님
    for (int i = 0; i <= MAX_N; i++) {
        if (is_node[i] && !visited[i]) {
            cout << 0 << "\n";
            return 0;
        }
    }

    cout << 1 << "\n"; // 트리 조건 충족
    return 0;
}
