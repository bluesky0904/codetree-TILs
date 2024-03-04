#include <iostream>
using namespace std;

#define MAX_N 100000

int n, m;

struct Node {
    int data;
    Node* prev, * next;
    Node(int data) : data(data), prev(nullptr), next(nullptr) {};
};

Node* nodes[MAX_N + 1];

void connect(Node* s, Node* e) {
    if (s) s->next = e;
    if (e) e->prev = s;
}

void pop(Node* node) {
    if (node->next == node) { // 리스트에 노드가 하나만 있을 경우
        nodes[node->data] = nullptr; // 해당 노드를 배열에서 제거
    } else {
        connect(node->prev, node->next);
        if (nodes[node->data] == node) {
            nodes[node->data] = nullptr;
        }
    }
    delete node; // 메모리 해제
}

void print_node(Node* node) {
    if (node == nullptr || node->next == nullptr || node->prev == nullptr) {
        cout << "Error: Node is isolated or does not exist." << "\n";
        return;
    }
    cout << node->next->data << " " << node->prev->data << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;

    Node* prev = nullptr;
    Node* cur = nullptr;

    for (int i = 1; i <= n; i++) {
        int num;
        cin >> num;
        Node* target = new Node(num);
        nodes[num] = target;

        if (i == 1) cur = target;
        else connect(prev, target);

        if (i == n && n > 1) connect(target, cur); // 순환 구조 생성

        prev = target;
    }

    while (m--) {
        int num;
        cin >> num;
        if (nodes[num] != nullptr) {
            print_node(nodes[num]);
            pop(nodes[num]);
        } else {
            cout << "Node does not exist or has been removed." << "\n";
        }
    }

    return 0;
}