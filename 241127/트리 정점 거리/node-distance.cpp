#include <iostream>
#include <vector>
#include <tuple>

#define MAX_N 1000

using namespace std;

// 변수 선언:
int n, m;
vector<pair<int, int> > edges[MAX_N + 1];
bool visited[MAX_N + 1];
int dist[MAX_N + 1][MAX_N + 1];

// DFS를 통해 st로부터 모든 정점까지의 거리를 탐색합니다.
void DFS(int st, int x) {
    for(int i = 0; i < (int) edges[x].size(); i++) {
        int y, d;
        tie(y, d) = edges[x][i];
        // 이미 방문한 노드는 스킵합니다.
        if(visited[y]) continue;
        
        visited[y] = true;

        // st로부터의 거리를 갱신합니다.
        dist[st][y] = dist[st][x] + d;

        DFS(st, y);
    }
}

int main() {
    // 입력:
    cin >> n >> m;
    // n - 1개의 간선 정보를 입력받습니다.
    for(int i = 1; i <= n - 1; i++) {
        int x, y, d;
        cin >> x >> y >> d;

        // 간선 정보를 인접리스트에 넣어줍니다.
        edges[x].push_back({y, d});
        edges[y].push_back({x, d});
    }

    // 각 n개의 정점에 대해, 모든 노드간의 거리를 DFS로 갱신해줍니다.
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) 
            visited[j] = false;
        
        visited[i] = true;
        DFS(i, i);
    }

    // m개의 노드 쌍을 입력받고, 두 노드 쌍 간의 거리를 바로 출력해줍니다.
    for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        cout << dist[x][y] << endl;
    }

    return 0;
}