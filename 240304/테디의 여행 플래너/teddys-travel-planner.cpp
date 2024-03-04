#include <iostream>
using namespace std;

int n, q;

struct Node {
	string name;

	Node* prev, * next;

	Node(string name) : name(name), prev(nullptr), next(nullptr) {};
};

void connect(Node* s, Node* e) {
	if (s) s->next = e;
	if (e) e->prev = s;
}

void remove_next(Node* node) {
	connect(node->prev, node->next);
	node->prev = node->next = nullptr;
}

void insert_next(Node* cur, Node* new_node) {
	connect(new_node, cur->next);
	connect(cur, new_node);
}

void print_node(Node* cur) {
	if (nullptr == cur->prev || nullptr == cur->next || (cur->prev->name == cur->next->name)) {
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
			remove_next(cur->next);
		}
		else if (command == 4) {
			string s;
			cin >> s;
			insert_next(cur, new Node(s));
		}

		print_node(cur);
	}
}