#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

int n, m;

struct Node {
	int data;

	Node* prev, * next;

	Node(int data) : data(data), prev(nullptr), next(nullptr) {};
};

unordered_map<int, Node*> nodes;

void connect(Node* s, Node* e) {
	if (s) s->next = e;
	if (e) e->prev = s;
}

void pop(Node* node) {
	connect(node->prev, node->next);
	node->prev = node->next = nullptr;
}

void print_node(Node* node) {
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

		if (i == n) connect(target, cur);

		prev = target;
	}

	while (m--) {
		int num;
		cin >> num;
		print_node(nodes[num]);
		pop(nodes[num]);
	}

	return 0;
}