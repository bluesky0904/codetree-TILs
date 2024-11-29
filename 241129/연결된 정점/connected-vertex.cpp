#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100000

int n, m;
int uf[MAX_N + 1]; // 부모 노드 저장
int size[MAX_N + 1]; // 각 컴포넌트의 크기 저장

int Find(int a) {
    if (uf[a] == a) return a;
    return uf[a] = Find(uf[a]); // 경로 압축
}

void Union(int a, int b) {
    int A = Find(a), B = Find(b);
    if (A != B) {
        if (size[A] < size[B]) swap(A, B);
        uf[B] = A; // B의 루트를 A로 설정
        size[A] += size[B]; // A의 크기에 B의 크기 추가
    }
}

int main() {
    cin >> n >> m;
    
    // 초기화
    for (int i = 1; i <= n; i++) {
        uf[i] = i; // 자기 자신을 부모로 설정
        size[i] = 1; // 초기 크기는 1
    }

    for (int i = 1; i <= m; i++) {
        char op; cin >> op;
        if (op == 'x') {
            int a, b; cin >> a >> b;
            Union(a, b);
        } else if (op == 'y') {
            int a; cin >> a;
            int root = Find(a); // a의 루트 찾기
            cout << size[root] << "\n"; // 루트의 크기 출력
        }
    }

    return 0;
}
