#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 1001

vector<pair<int, int>> edge[MAX_N];
bool visited[MAX_N];

int DFS(int start, int end, int dist) {
    visited[start] = true;

    if (start == end) return dist;

    for (auto [next, weight] : edge[start]) {
        if (!visited[next]) {
            int result = DFS(next, end, dist + weight);
            if (result != -1) return result;
        }
    }
    return -1; // 경로를 찾지 못한 경우
}

int main() {
    int n, m;
    cin >> n >> m;

    // 간선 입력
    for (int i = 0; i < n - 1; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        edge[u].push_back({v, d});
        edge[v].push_back({u, d});
    }

    // 질의 입력 및 처리
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        fill(visited, visited + n + 1, false); // 방문 배열 초기화
        cout << DFS(u, v, 0) << "\n";
    }

    return 0;
}
