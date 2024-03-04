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
    if (node->prev == node->next) {
        nodes[node->data] = nullptr; // 리스트에서 유일한 노드를 제거
    } else {
        connect(node->prev, node->next);
        if (nodes[node->data] == node) {
            nodes[node->data] = nullptr; // 노드 배열 업데이트
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

        prev = target;
    }
    // 순환을 위한 마지막 노드와 첫 번째 노드 연결
    if (n > 1) {
        connect(prev, nodes[cur->data]);
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