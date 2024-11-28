#include <iostream>
#include <vector>
using namespace std;

// Union-Find 클래스
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
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

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    UnionFind uf(n);

    // 간선 정보 입력 및 Union-Find로 연결
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        uf.unite(x, y);
    }

    // 주어진 순서 정보 입력
    vector<int> order(k);
    for (int i = 0; i < k; ++i) {
        cin >> order[i];
    }

    // 모든 노드가 같은 그룹에 속하는지 확인
    int group = uf.find(order[0]);
    for (int i = 1; i < k; ++i) {
        if (uf.find(order[i]) != group) {
            cout << 0 << endl;
            return 0;
        }
    }

    cout << 1 << endl;
    return 0;
}
