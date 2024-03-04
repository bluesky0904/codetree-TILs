#include <iostream>

using namespace std;

// 한 노드를 나타내는 구조체입니다.
struct Node {
    // 문자열을 값으로 가집니다.
    string data;
    Node *prev, *next;

    Node(string data) : data(data), prev(nullptr), next(nullptr) {};
};

// 두 도시를 연결해줍니다.
void connect(Node *s, Node *e) {
    if (nullptr != s) s->next = e;
    if (nullptr != e) e->prev = s;
}

// target 뒤에 s를 삽입합니다.
void insertNext(Node *target, Node *s) {
    connect(s, target->next);
    connect(target, s);
}

// 해당 도시를 삭제합니다.
void pop(Node *u) {
    connect(u->prev, u->next);
    u->prev = u->next = nullptr;
}

int main() {
    int n, q;
    cin >> n >> q;
    Node *cur, *prev;

    // 지구본이라 연결 리스트가 원형으로 이어져 있음에 유의합니다.
    for (int i = 1; i <= n; i++) {
        string x;
        cin >> x;
        Node *target = new Node(x);

        // 맨 첫 번째 도시가 핀셋으로 꽂혀 있는 도시입니다.
        if (i == 1) {
            cur = target;
        } else {
            // 그 전 도시들과 이어줍니다.
            connect(prev, target);
        }
        // 원형이기 때문에 마지막 도시는 핀셋이 꽂혀 있는 도시와 연결해줍니다.
        if (i == n) connect(target, cur);
        // 이전 도시들과 연결해주기 위함입니다.
        prev = target;
    }

    // q 개의 행동을 진행합니다.
    while (q--) {
        int option;
        cin >> option;

        if (option == 1) {
            if (cur->next) cur = cur->next;
        }

        if (option == 2) {
            if (cur->prev) cur = cur->prev;
        }

        if (option == 3) {
            if (cur->next != cur)
                pop(cur->next);
        }

        if (option == 4) {
            string x;
            cin >> x;
            insertNext(cur, new Node(x));
        }

        // 문제의 조건대로 출력해줍니다.
        if (cur->next == cur->prev || cur->next == nullptr || cur->prev == nullptr) cout << -1 << "\n";
        else cout << cur->prev->data << " " << cur->next->data << "\n";
    }
}