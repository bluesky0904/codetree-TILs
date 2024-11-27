#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000

vector<int> edge[MAX_N + 1];
bool visited[MAX_N + 1];
int depth[MAX_N + 1];

int n;

// DFS를 사용해 각 노드의 깊이를 계산
void DFS(int x, int d) {
    visited[x] = true;
    depth[x] = d;

    for (int next_x : edge[x]) {
        if (!visited[next_x]) {
            DFS(next_x, d + 1);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        edge[v1].push_back(v2);
        edge[v2].push_back(v1);
    }

    fill(visited, visited + MAX_N + 1, false);
    DFS(1, 0);

    long long total_depth = 0;
    for (int i = 2; i <= n; i++) {
        if (edge[i].size() == 1) {  // 리프 노드 판별
            total_depth += depth[i];
        }
    }

    if (total_depth % 2 == 1) {
        cout << 1 << "\n";  // a가 승리
    } else {
        cout << 0 << "\n";  // b가 승리
    }

    return 0;
}