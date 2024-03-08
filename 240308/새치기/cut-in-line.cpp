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

void connect(Node* a, Node* b) {
	if (a) a->next = b;
	if (b) b->prev = a;
}

void pop(Node* a) {
	int a_line = line_num[a->id];
	if (a == heads[a_line]) heads[a_line] = heads[a_line]->next;
	if (a == tails[a_line]) tails[a_line] = tails[a_line]->prev;
	connect(a->prev, a->next);
	line_num[a->id] = 0;
}

void insert_prev(Node* a, Node* b) {
	int a_line = line_num[a->id];
	int b_line = line_num[b->id];

	pop(a);

	if (b == heads[b_line]) {
		connect(a, b);
		heads[b_line] = a;
	}
	else {
		connect(b->prev, a);
		connect(a, b);
	}
	line_num[a->id] = b_line;
}

void pop_range_insert_prev(Node* a, Node* b, Node* c) {
	int a_line = line_num[a->id];
	int c_line = line_num[c->id];

	if (a == heads[a_line]) heads[a_line] = heads[a_line]->next;
	if (b == tails[a_line]) tails[a_line] = tails[a_line]->prev;
	connect(a->prev, b->next);

	if (c == heads[c_line]) heads[c_line] = a;
	connect(c->prev, a);
	connect(b, c);

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
			int num;
			cin >> num;
			Node* target = new Node(num);
			nodes[num] = target;
			line_num[num] = i;
			if (j == 1) heads[i] = target;
			if (j == people_num) tails[i] = target;
			connect(prev, target);
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
		if (nullptr == cur) cout << -1 << "\n";
		while (cur) {
			cout << cur->id << " ";
			cur = cur->next;
		}
		cout << "\n";
	}
}