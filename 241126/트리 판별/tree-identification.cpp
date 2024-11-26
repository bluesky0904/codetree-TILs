#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 10000

vector<int> edge[MAX_N + 1];
bool visited[MAX_N + 1];
int parent[MAX_N + 1];

int main() {
    int m;
    cin >> m;

    // 간선 정보 입력 및 초기화
    for (int i = 0; i < MAX_N + 1; i++) {
        parent[i] = -1;
    }

    int edge_count = 0;
    int node_count = 0;
    int root_candidate = -1;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        edge[a].push_back(b);
        edge_count++;
        node_count = max(node_count, max(a, b));

        if (parent[b] != -1) {
            // 부모가 두 개 이상이면 트리 아님
            cout << 0 << "\n";
            return 0;
        }
        parent[b] = a;

        if (parent[a] == -1) {
            root_candidate = a; // 루트 후보 갱신
        }
    }

    // 루트 노드가 유일한지 확인
    int root_count = 0;
    for (int i = 1; i <= node_count; i++) {
        if (parent[i] == -1) {
            root_count++;
            root_candidate = i;
        }
    }

    if (root_count != 1) {
        cout << 0 << "\n";
        return 0;
    }

    // DFS로 모든 노드 방문 확인
    fill(visited, visited + node_count + 1, false);

    queue<int> q;
    q.push(root_candidate);
    visited[root_candidate] = true;
    int visited_count = 0;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        visited_count++;

        for (int next : edge[curr]) {
            if (visited[next]) {
                // 사이클 발생 시 트리 아님
                cout << 0 << "\n";
                return 0;
            }
            visited[next] = true;
            q.push(next);
        }
    }

    // 방문한 노드 수와 간선 수 확인
    if (visited_count != node_count || edge_count != node_count - 1) {
        cout << 0 << "\n";
    } else {
        cout << 1 << "\n";
    }

    return 0;
}
