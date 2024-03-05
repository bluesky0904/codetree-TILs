#include <iostream>
using namespace std;

#define MAX_N 100000
#define MAX_M 10

int n, m, q;

struct Node {
	int data;
	Node* prev, *next;

	Node(int data) : data(data), prev(nullptr), next(nullptr) {};
};

Node* nodes[MAX_N + 1];
Node* heads[MAX_M + 1], *tails[MAX_M + 1];

int lineNum[MAX_N + 1];

void connect(Node* s, Node* e) {
	if (s) s->next = e;
	if (e) e->prev = s;
}

void pop(Node *i) {
	int l = lineNum[i->data];

	if (l == 0) return;

	if (heads[l] == i) heads[l] = heads[l]->next;
	if (tails[l] == i) tails[l] = tails[l]->prev;

	connect(i->prev, i->next);
	lineNum[i->data] = 0;
	i->prev = i->next = nullptr;
}

void insert_prev(Node* a, Node* b) {
	int lineNumB = lineNum[b->data];

	if (heads[lineNumB] == b) heads[lineNumB] = a;
	pop(a);
	connect(b->prev, a);
	connect(a, b);
	lineNum[a->data] = lineNumB;
}

void pop_range_insert_prev(Node* a, Node* b, Node* c) {
	int lineNumA = lineNum[a->data];
	int lineNumC = lineNum[c->data];

	if (heads[lineNumA] == a) heads[lineNumA] = b->next;
	if (tails[lineNumA] == b) tails[lineNumA] = a->prev;

	connect(a->prev, b->next);

	if (heads[lineNumC] == c) {
		connect(b, c);
		heads[lineNumC] = a;
	}
	else {
		connect(c->prev, a);
		connect(b, c);
	}

	Node* cur = a;
	while (cur != b) {
		lineNum[cur->data] = lineNumC;
		cur = cur->next;
	}
	lineNum[cur->data] = lineNumC;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) nodes[i] = new Node(i);
	for (int i = 1; i <= m; i++) {
		heads[i] = tails[i] = nullptr;
	}

	for (int i = 1; i <= m; i++) {
		int people_num;
		cin >> people_num;
		for (int j = 1; j <= people_num; j++) {
			int num;
			cin >> num;
			lineNum[num] = i;
			if (j == 1) heads[i] = tails[i] = nodes[num] = new Node(num);
			else {
				nodes[num] = new Node(num);
				connect(tails[i], nodes[num]);
				tails[i] = nodes[num];
			}
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
		else {
			while (cur) {
				cout << cur->data << " ";
				cur = cur->next;
			}
			cout << "\n";
		}
	}

	return 0;
}