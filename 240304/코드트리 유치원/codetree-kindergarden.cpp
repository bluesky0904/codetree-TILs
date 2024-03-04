#include <bits/stdc++.h>

using namespace std;

#define MAXN (200000)

// 학생들을 나타내는 노드입니다.
struct Node {
    // 학생의 번호를 나타냅니다.
    int id;
    Node *prev, *next;

    Node(int id) : id(id), prev(nullptr), next(nullptr) {}
};

// 학생들을 나타내는 노드들을 저장합니다.
Node *nodes[MAXN + 2];

// 현재까지 줄을 서고 있는 총 학생의 수를 나타냅니다.
int nodeCnt;

// 두 학생들을 연결해 줍니다.
void connect(Node *s, Node *e) {
    if (nullptr != s) s->next = e;
    if (nullptr != e) e->prev = s;
}

// 번호가 s부터 e까지의 학생들을 번호가 v인 학생 뒤에 연결해 줍니다.
void insertNextRange(Node *s, Node *e, Node *v) {
    Node *nextV = v->next;
    connect(v, s);
    connect(e, nextV);
}

// 번호가 s부터 e까지의 학생들을 번호가 v인 학생 앞에 연결해 줍니다.
void insertPrevRange(Node *s, Node *e, Node *v) {
    connect(v->prev, s);
    connect(e, v);
}

int main() {
    int q;
    cin >> q;

    // 맨 처음에는 1번 학생이 줄을 서고 있습니다.
    // 따라서 현재까지의 줄을 서고 있는 총 학생의 수는 1입니다.
    nodeCnt = 1;
    nodes[1] = new Node(1);

    // q개의 행동을 진행합니다.
    while (q--) {
        int option;
        cin >> option;

        if (option == 1) {
            int a, b;
            cin >> a >> b;

            // 다음 줄을 서야 할 학생의 번호는
            // 제일 마지막으로 줄을 세웠던 학생의 번호 + 1 입니다.
            int init = nodeCnt + 1;

            // b명의 학생들을 줄을 세워야하기 때문에 nodeCnt를 b만큼 증가시켜줍니다.
            nodeCnt += b;

            // 학생 번호 init ~ init + b - 1 까지의 학생들을 줄을 먼저 세웁니다.
            for (int i = 0; i < b; i++) {
                nodes[init + i] = new Node(init + i);
                if (i != 0) connect(nodes[init + i - 1], nodes[init + i]);
            }

            // 해당 학생들을 번호가 a인 학생 뒤에 연결해 줍니다.
            insertNextRange(nodes[init], nodes[init + b - 1], nodes[a]);
        }

        if (option == 2) {
            int a, b;
            cin >> a >> b;

            // 다음 줄을 서야 할 학생의 번호는
            // 제일 마지막으로 줄을 세웠던 학생의 번호 + 1 입니다.
            int init = nodeCnt + 1;
            nodeCnt += b;

            // 학생 번호 init ~ init + b - 1 까지의 학생들을 줄을 먼저 세웁니다.
            for (int i = 0; i < b; i++) {
                nodes[init + i] = new Node(init + i);
                if (i != 0) connect(nodes[init + i - 1], nodes[init + i]);
            }

            // 해당 학생들을 번호가 a인 학생 앞에 연결해 줍니다.
            insertPrevRange(nodes[init], nodes[init + b - 1], nodes[a]);
        }

        if (option == 3) {
            int a;
            cin >> a;
            
            // 문제의 조건 대로 출력을 진행합니다.
            if (nodes[a]->prev == nullptr || nodes[a]->next == nullptr) cout << -1 << "\n";
            else cout << nodes[a]->prev->id << " " << nodes[a]->next->id << "\n";
        }
    }
}