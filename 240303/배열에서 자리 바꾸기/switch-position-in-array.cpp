#include <iostream>
#include <unordered_map>
using namespace std;

int n, q;

struct Node {
	int id;
	Node* prev, * next;
	Node(int id) : id(id), prev(nullptr), next(nullptr) {};
};

void Connect(Node* s, Node* e) {
	if (nullptr != s) s->next = e;
	if (nullptr != e) e->prev = s;
}

void SwapSubarray(Node* a, Node* b, Node* c, Node* d) {
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

	Connect(a_prev, a);
	Connect(b, b_next);
	Connect(c_prev, c);
	Connect(d, d_next);
}

unordered_map<int, Node*> nodes;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) nodes[i] = new Node(i);
	for (int i = 1; i < n; i++) Connect(nodes[i], nodes[i + 1]);

	while (q--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		SwapSubarray(nodes[a], nodes[b], nodes[c], nodes[d]);
	}

	Node* cur = nodes[1];

	while (nullptr != cur->prev) cur = cur->prev;
	while (nullptr != cur) {
		cout << cur->id << " ";
		cur = cur->next;
	}
	cout << "\n";
	return 0;
}