#include <iostream>
#include <vector>
#include <tuple>
#include <stack>
using namespace std;

#define MAX_N 10000

int n, m;
vector<pair<int, int>> edge[MAX_N + 1];
bool visited[MAX_N + 1];
int visit_counter = 0;
int visit_mark[MAX_N + 1];

int DFS(int start, int end, int dist) {
    visit_mark[start] = visit_counter;
    for (int i = 0; i < (int)edge[start].size(); i++) {
        int next_idx, next_dist;
        tie(next_idx, next_dist) = edge[start][i];

        if (visit_mark[next_idx] == visit_counter) continue;

        if (next_idx == end) {
            return dist + next_dist;
        }

        int rslt = DFS(next_idx, end, dist + next_dist);
        if (rslt != -1) return rslt;
    }
    return -1;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i < n; i++) {
        int v1, v2, d;
        cin >> v1 >> v2 >> d;
        edge[v1].push_back({v2, d});
        edge[v2].push_back({v1, d});
    }

    for (int i = 1; i <= m; i++) {
        int v1, v2;
        cin >> v1 >> v2;

        visit_counter++;
        cout << DFS(v1, v2, 0) << "\n";
    }

    return 0;
}
