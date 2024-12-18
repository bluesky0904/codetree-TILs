#include <iostream>
using namespace std;

int n;

typedef struct Node {
    string data;
    Node* prev, * next;
    Node(string data) : data(data), prev(nullptr), next(nullptr) {}
};

void InsertNext(Node* u, Node* singleton) {
    singleton->prev = u;
    singleton->next = u->next;

    if (singleton->prev != nullptr)
        singleton->prev->next = singleton;
    if (singleton->next != nullptr)
        singleton->next->prev = singleton;
}

void InsertPrev(Node* u, Node* singleton) {
    singleton->prev = u->prev;
    singleton->next = u;

    if (singleton->prev != nullptr)
        singleton->prev->next = singleton;
    if (singleton->next != nullptr)
        singleton->next->prev = singleton;
}

void Pop(Node* u) {
    if (u->prev != nullptr)
        u->prev->next = u->next;
    if (u->next != nullptr)
        u->next->prev = u->prev;

    u->prev = u->next = nullptr;
}

void PrintNode(Node* cur) {
    if (cur->prev != nullptr) cout << cur->prev->data << " ";
    else cout << "(Null)" << " ";

    cout << cur->data << " ";

    if (cur->next != nullptr) cout << cur->next->data << " ";
    else cout << "(Null)" << " ";
}

int main() {
    string s;
    cin >> s;
    Node* cur = new Node(s);

    cin >> n;
    while (n--) {
        int command;
        string str;
        cin >> command;

        if (command == 1) {
            cin >> str;
            Node* new_node = new Node(str);
            InsertPrev(cur, new_node);
        }
        else if (command == 2) {
            cin >> str;
            Node* new_node = new Node(str);
            InsertNext(cur, new_node);
        }
        else if (command == 3) {
            if (cur->prev != nullptr)
                cur = cur->prev;
        }
        else if (command == 4) {
            if (cur->next != nullptr)
                cur = cur->next;
        }

        PrintNode(cur);
        cout << "\n";
    }

    return 0;
}