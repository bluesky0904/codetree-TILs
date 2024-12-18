#include <iostream>
using namespace std;

#define MAX_N 250000

int n, q;

typedef struct Node {
	int data;
	struct Node* prev, * next;
	Node(int data) : data(data), prev(nullptr), next(nullptr) {}
};

Node* nodes[MAX_N + 1] = {};

void connect(Node* u, Node* v) {
	if (u != nullptr)
		u->next = v;
	if (v != nullptr)
		v->prev = u;
}

// [] a b c d [] 
// c d a b 
void Swap(Node* a, Node* b, Node* c, Node* d) {
	Node* a_prev = c->prev;
	Node* b_next = d->next;
	Node* c_prev = a->prev;
	Node* d_next = b->next;

	if (b->next == c) {
		d_next = a;
		a_prev = d;
	}

	if (d->next == a) {
		b_next = c;
		c_prev = b;
	}

	connect(a_prev, a);
	connect(b, b_next);
	connect(c_prev, c);
	connect(d, d_next);
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		nodes[i] = new Node(i);

	for (int i = 1; i < n; i++)
		connect(nodes[i], nodes[i + 1]);

	cin >> q;
	while (q--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		Swap(nodes[a], nodes[b], nodes[c], nodes[d]);
	}

	Node* cur = nodes[1];
	while (cur->prev != nullptr)
		cur = cur->prev;

	while (cur != nullptr) {
		cout << cur->data << " ";
		cur = cur->next;
	}
}