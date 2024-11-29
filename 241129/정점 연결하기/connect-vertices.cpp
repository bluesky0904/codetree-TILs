#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int n;
int uf[MAX_N + 1];

// Union-Find: Find 연산
int Find(int a) {
    if (uf[a] == a) return a;
    return uf[a] = Find(uf[a]); // 경로 압축
}

// Union-Find: Union 연산
void Union(int a, int b) {
    int rootA = Find(a), rootB = Find(b);
    if (rootA != rootB) uf[rootA] = rootB; // 병합
}

int main() {
    cin >> n;

    // Union-Find 초기화
    for (int i = 1; i <= n; i++) uf[i] = i;

    // 간선 입력 및 Union 수행
    for (int i = 0; i < n - 2; i++) {
        int u, v;
        cin >> u >> v;
        Union(u, v);
    }

    // 각 노드의 루트를 구하고 컴포넌트 그룹 생성
    vector<int> roots(n + 1, 0); // 각 노드의 루트 저장
    for (int i = 1; i <= n; i++) {
        roots[i] = Find(i);
    }

    // 두 컴포넌트를 구분
    vector<int> comp1, comp2;
    for (int i = 1; i <= n; i++) {
        if (roots[i] == Find(1)) {
            comp1.push_back(i); // 첫 번째 컴포넌트에 속하는 노드
        } else {
            comp2.push_back(i); // 두 번째 컴포넌트에 속하는 노드
        }
    }

    // 두 컴포넌트의 사전순으로 가장 작은 노드 선택
    int u = *min_element(comp1.begin(), comp1.end());
    int v = *min_element(comp2.begin(), comp2.end());

    // 사전순 정렬
    if (u > v) swap(u, v);
    cout << u << " " << v << endl;

    return 0;
}
