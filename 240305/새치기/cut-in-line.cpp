#include <iostream>
using namespace std;

#define MAX_N 100000
#define MAX_M 10

int n, m, q;
int line_num[MAX_N + 1];

struct Node {
    int id;
    Node* prev, * next;
    Node(int id) : id(id), prev(nullptr), next(nullptr) {};
};

Node* nodes[MAX_N + 1];
Node* heads[MAX_M + 1], * tails[MAX_M + 1];

void connect(Node* s, Node* e) {
    if (s) s->next = e;
    if (e) e->prev = s;
}

void pop(Node* a) {
    if (line_num[a->id] == 0) return;
    int l = line_num[a->id];
    if (heads[l] == a) heads[l] = a->next;
    if (tails[l] == a) tails[l] = a->prev;
    if (a->prev) a->prev->next = a->next;
    if (a->next) a->next->prev = a->prev;
    a->prev = a->next = nullptr;
    line_num[a->id] = 0;
}

void insert_prev(Node* a, Node* b) {
    int b_line = line_num[b->id];
    pop(a); // Pop a first to correctly update any existing connections
    if (heads[b_line] == b) heads[b_line] = a;
    connect(b->prev, a);
    connect(a, b);
    line_num[a->id] = b_line;
}

void pop_range_insert_prev(Node* a, Node* b, Node* c) {
    int a_line = line_num[a->id], c_line = line_num[c->id];
    if (heads[a_line] == a) heads[a_line] = b->next;
    if (b->next) b->next->prev = a->prev;
    if (a->prev) a->prev->next = b->next;

    if (heads[c_line] == c) heads[c_line] = a;
    if (c->prev) c->prev->next = a;
    a->prev = c->prev;
    b->next = c;
    c->prev = b;

    Node* cur = a;
    while (cur) {
        line_num[cur->id] = c_line;
        if (cur == b) break;
        cur = cur->next;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) heads[i] = tails[i] = nullptr;
    for (int i = 1; i <= m; i++) {
        int people_num;
        cin >> people_num;
        Node* prev = nullptr;
        for (int j = 0; j < people_num; j++) {
            int id;
            cin >> id;
            Node* target = new Node(id);
            nodes[id] = target;
            if (!heads[i]) heads[i] = target;
            if (prev) connect(prev, target);
            prev = target;
            line_num[id] = i;
        }
        tails[i] = prev;
    }

    while (q--) {
        int command;
        cin >> command;
        if (command == 1) {
            int a, b;
            cin >> a >> b;
            insert_prev(nodes[a], nodes[b]);
        }
        else if (command == 2) {
            int a;
            cin >> a;
            pop(nodes[a]);
        }
        else if (command == 3) {
            int a, b, c;
            cin >> a >> b >> c;
            pop_range_insert_prev(nodes[a], nodes[b], nodes[c]);
        }
    }

    for (int i = 1; i <= m; i++) {
        Node* cur = heads[i];
        if (!cur) {
            cout << -1 << "\n";
        }
        else {
            while (cur) {
                cout << cur->id << " ";
                cur = cur->next;
            }
            cout << "\n";
        }
    }

    return 0;
}