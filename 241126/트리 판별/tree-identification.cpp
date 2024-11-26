#include <iostream>
#include <vector>
#include <tuple>

#define MAX_N 10000

using namespace std;

// 변수 선언:
int m;
int root;
int deg[MAX_N + 1];
vector<int> edges[MAX_N + 1];
bool used[MAX_N + 1];
bool visited[MAX_N + 1];
bool is_tree = true;

// DFS를 통해 루트로부터 갈 수 있는 모든 정점을 탐색합니다.
void DFS(int x) {
    for(int i = 0; i < edges[x].size(); i++) {
        int y = edges[x][i];
        // 이미 방문한 노드는 스킵합니다.
        if(visited[y]) 
            continue;
        
        visited[y] = true;
        DFS(y);
    }

    return;
}

int main() {
    // 입력:
    cin >> m;
    // n개의 간선 정보를 입력받습니다.
    for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;

        // 간선 정보를 인접리스트에 넣어줍니다.
        edges[x].push_back(y);

        // 해당 번호가 그래프에 있는 정점 번호인지 판단합니다.
        used[x] = used[y] = true;

        // 정점 별 들어오는 간선의 개수를 저장합니다.
        deg[y]++;
    }

    // 루트 노드를 찾습니다. 들어오는 간선이 하나도 없는 노드가 여러개면 트리가 아닙니다.
    for(int i = 1; i <= MAX_N; i++) {
        if(used[i] && deg[i] == 0) {
            // 이미 선정된 루트가 있다면 
            // 루트가 여러 개인 것이므로 트리가 아닙니다.
            if(root != 0) 
                is_tree = false;
            root = i;
        }
    }

    // 루트 노드가 없으면 트리가 아닙니다.
    if(root == 0) 
        is_tree = false;
    
    // 루트 노드를 제외한 노드는 모두 들어오는 간선이 1개씩 있습니다. 그렇지 않으면 트리가 아닙니다.
    for(int i = 1; i <= MAX_N; i++) {
        if(used[i] && i != root && deg[i] != 1) {
            is_tree = false;
        }
    }

    if(is_tree && root != 0) {
        // root 정점으로부터 모든 정점을 갈 수 있는지 판단합니다.
        visited[root] = true;
        DFS(root);
    }

    // root 정점으로부터 탐색해 도달하지 못하는 정점이 있으면 트리가 아닙니다.
    for(int i = 1; i <= MAX_N; i++) {
        if(used[i] && !visited[i]) {
            is_tree = false;
        }
    }

    if(is_tree) cout << 1;
    else cout << 0;
    return 0;
}