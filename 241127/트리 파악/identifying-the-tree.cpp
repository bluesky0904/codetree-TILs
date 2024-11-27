#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 100000

vector<int> edge[MAX_N + 1];
vector<int> leaf;
bool visited[MAX_N + 1];
int parent[MAX_N + 1];

int n;

void DFS(int x) {
    visited[x] = true;
    bool is_leaf = true;

    for (int next_x : edge[x]) {
        if (!visited[next_x]) {
            is_leaf = false;
            parent[next_x] = x;
            DFS(next_x);
        }
    }

    if (is_leaf) {
        leaf.push_back(x);
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
    visited[1] = true;
    DFS(1);

    queue<int> q;
    for (int l : leaf) q.push(l);

    int cnt = 0;
    while (!q.empty()) {
        int horse = q.front();
        q.pop();

        int next_horse = parent[horse];
        if (next_horse != 1) q.push(next_horse);

        cnt++;
    }

    if (cnt % 2 == 0) cout << 0 << "\n";
    else cout << 1 << "\n";

    return 0;
}
