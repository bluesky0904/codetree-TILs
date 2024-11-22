#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 50

int n;
vector<int> tree[MAX_N];
bool visited[MAX_N];
int parents[MAX_N];
int leaf_count = 0;

void removeNode(int delete_num) {
    visited[delete_num] = true;

    // 자식 노드들 제거
    for (int child : tree[delete_num]) {
        if (!visited[child]) removeNode(child);
    }

    // 부모 노드에서 삭제된 노드 제거
    for (int i = 0; i < n; i++) {
        if (!tree[i].empty()) {
            tree[i].erase(remove(tree[i].begin(), tree[i].end(), delete_num), tree[i].end());
        }
    }

    tree[delete_num].clear();
}

void countLeafNodes(int root) {
    visited[root] = true;

    // 리프 노드 확인
    if (tree[root].empty()) {
        leaf_count++;
        return;
    }

    // 자식 노드 탐색
    for (int child : tree[root]) {
        if (!visited[child]) countLeafNodes(child);
    }
}

int main() {
    cin >> n;

    int root = -1;
    for (int i = 0; i < n; i++) {
        cin >> parents[i];
        if (parents[i] == -1) {
            root = i;
        } else {
            tree[parents[i]].push_back(i);
        }
    }

    int delete_num;
    cin >> delete_num;

    // 루트 노드 삭제 처리
    if (delete_num == root) {
        cout << 0 << "\n";
        return 0;
    }

    visited[delete_num] = true;
    removeNode(delete_num);

    fill(visited, visited + n, false); // 방문 배열 초기화
    countLeafNodes(root);

    cout << leaf_count << "\n";
    return 0;
}
