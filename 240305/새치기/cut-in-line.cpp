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
	connect(a->prev, a->next);
	line_num[a->id] = 0;
}

void insert_prev(Node* a, Node* b) {
	int b_line = line_num[b->id];
	pop(a);
	if (heads[b_line] == b) heads[b_line] = a;
	connect(b->prev, a);
	connect(a, b);
	line_num[a->id] = b_line;
}

void pop_range_insert_prev(Node* a, Node* b, Node* c) {
	int a_line = line_num[a->id];
	int c_line = line_num[c->id];
	if (heads[a_line] == a) heads[a_line] = b->next;
	if (tails[a_line] == b) tails[a_line] = a->prev;

	connect(a->prev, b->next);

	if (heads[c_line] == c) {
		connect(b, c);
		heads[c_line] = a;
	}
	else {
		connect(c->prev, a);
		connect(b, c);
	}

	Node* cur = a;
	while (cur != b) {
		line_num[cur->id] = c_line;
		cur = cur->next;
	}
	line_num[cur->id] = c_line;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++) heads[i] = tails[i] = nullptr;
	for (int i = 1; i <= m; i++) {
		int people_num;
		cin >> people_num;
		Node* prev = nullptr;
		for (int j = 1; j <= people_num; j++) {
			int id;
			cin >> id;
			line_num[id] = i;
			Node* target = new Node(id);
			nodes[id] = target;
			if (j == 1) heads[i] = target;
			else connect(prev, target);

			if (j == people_num) tails[i] = target;

			prev = target;
		}
	}

	while (q--) {
		int command;
		int a, b, c;
		cin >> command;
		if (command == 1) {
			cin >> a >> b;
			insert_prev(nodes[a], nodes[b]);
		}
		else if (command == 2) {
			cin >> a;
			pop(nodes[a]);
		}
		else if (command == 3) {
			cin >> a >> b >> c;
			pop_range_insert_prev(nodes[a], nodes[b], nodes[c]);
		}
	}

	for (int i = 1; i <= m; i++) {
		Node* cur = heads[i];
		if (nullptr == cur) {
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