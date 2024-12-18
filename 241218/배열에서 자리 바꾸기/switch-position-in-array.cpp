#include <iostream>
using namespace std;

#define MAX_N 250000

typedef struct Node {
	int id;
	struct Node* prev, * next;
	Node(int id) : id(id), prev(nullptr), next(nullptr) {}
};

Node* nodes[MAX_N] = {};

void connect(Node* s, Node* e) {
	if (nullptr != s)
		s->next = e;
	if (nullptr != e)
		e->prev = s;
}

void swapSubarray(Node* a, Node* b, Node* c, Node* d) {
	Node* after_prevA = c->prev;
	Node* after_nextB = d->next;

	Node* after_prevC = a->prev;
	Node* after_nextD = b->next;

	if (b->next == c) {
		after_prevA = d;
		after_nextD = a;
	}

	if (d->next == a) {
		after_nextB = c;
		after_prevC = b;
	}

	connect(after_prevA, a);
	connect(b, after_nextB);
	connect(after_prevC, c);
	connect(d, after_nextD);
}

int main() {
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++)
		nodes[i] = new Node(i);

	for (int i = 1; i < n; i++)
		connect(nodes[i], nodes[i + 1]);

	int q;
	cin >> q;

	for (int i = 0; i < q; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;

		swapSubarray(nodes[a], nodes[b], nodes[c], nodes[d]);
	}

	Node* cur = nodes[1];

	while (nullptr != cur->prev)
		cur = cur->prev;

	while (nullptr != cur) {
		cout << cur->id << ' ';
		cur = cur->next;
	}
}