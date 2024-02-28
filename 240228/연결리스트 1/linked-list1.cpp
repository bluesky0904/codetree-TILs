#include <iostream>

using namespace std;

// 한 노드를 나타내는 구조체입니다.
struct Node {
    // 문자열을 값으로 가집니다.
    string data;
    Node *prev, *next;

    Node(string data) : data(data), prev(nullptr), next(nullptr) {};
};

// 두 노드를 연결해줍니다.
void connect(Node *s, Node *e) {
    if (nullptr != s) s->next = e;
    if (nullptr != e) e->prev = s;
}

// target 뒤에 s를 삽입합니다.
void insertNext(Node *target, Node *s) {
    connect(s, target->next);
    connect(target, s);
}

// target 앞에 s를 삽입합니다.
void insertPrev(Node *target, Node *s) {
    connect(target->prev, s);
    connect(s, target);
}

// target의 이전 노드, target, target의 다음 노드의 값을 출력합니다.
void printNode(Node *target) {
    string n = "(Null)";

    // 이전 노드가 존재하지 않는다면, Null을 출력합니다.
    // 아니라면, 이전 노드의 값을 출력합니다.
    if (target->prev == nullptr) cout << n << " ";
    else cout << target->prev->data << " ";

    // target의 값을 출력합니다.
    cout << target->data << " ";

    // 다음 노드가 존재하지 않는다면, Null을 출력합니다.
    if (target->next == nullptr) cout << n << "\n";
    else cout << target->next->data << "\n";
}

int main() {
    // 맨 처음 문자열을 입력 받습니다.
    string sInit;
    cin >> sInit;

    // 맨 처음 존재하는 노드를 만듭니다.
    Node *cur = new Node(sInit);

    // 연산의 개수를 입력 받습니다.
    int n;
    cin >> n;

    while (n--) {
        int option;
        cin >> option;

        // option이 1이라면, cur의 앞에 노드를 삽입합니다.
        if (option == 1) {
            // 삽입할 노드를 만듭니다.
            string data;
            cin >> data;
            Node *target = new Node(data);

            // cur의 앞에 삽입합니다.
            insertPrev(cur, target);
        }

        // option이 2라면, cur의 뒤에 노드를 삽입합니다.
        if (option == 2) {
            // 삽입할 노드를 만듭니다.
            string data;
            cin >> data;
            Node *target = new Node(data);

            // cur의 뒤에 삽입합니다.
            insertNext(cur, target);
        }

        if (option == 3) {
            // cur의 이전 노드가 존재한다면, cur을 cur의 이전 노드로 변경합니다.
            if (cur->prev != nullptr) cur = cur->prev;
        }

        if (option == 4) {
            // cur의 다음 노드가 존재한다면, cur을 cur의 다음 노드로 변경합니다.
            if (cur->next != nullptr) cur = cur->next;
        }

        // 매 연산이 진행될 때마다 cur의 값을 출력합니다.
        printNode(cur);
    }
}