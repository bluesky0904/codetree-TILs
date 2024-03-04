#include <iostream>
using namespace std;

int n, q;

struct Node {
	string name;
	Node* prev, * next;

	Node(string name) : name(name), prev(nullptr), next(nullptr) {};
};

void connect(Node* u, Node* v) {
	if (nullptr != u) u->next = v;
	if (nullptr != v) v->prev = u;
}

void push_next(Node* pinset, Node* node) {
	connect(node, pinset->next);
	connect(pinset, node);
}

void remove(Node* node) {
	connect(node->prev, node->next);
	node->prev = node->next = nullptr;
}

void print_node(Node* cur) {
	if (cur->prev == nullptr || cur->next == nullptr || (cur->prev->name == cur->next->name)) {
		cout << -1 << "\n";
		return;
	}
	cout << cur->prev->name << " " << cur->next->name << "\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	Node* cur = nullptr;
	Node* prev = nullptr;

	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		Node* target = new Node(s);

		if (i == 1) cur = target;
		else connect(prev, target);

		if (i == n) connect(target, cur);

		prev = target;
	}

	while (q--) {
		int command;
		cin >> command;

		if (command == 1) {
			if (cur->next) cur = cur->next;
		}
		else if (command == 2) {
			if (cur->prev) cur = cur->prev;
		}
		else if (command == 3) {
			remove(cur->next);
		}
		else if (command == 4) {
			string s;
			cin >> s;
			push_next(cur, new Node(s));
		}

		print_node(cur);
	}

	return 0;
}