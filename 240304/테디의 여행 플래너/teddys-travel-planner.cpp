#include <iostream>
using namespace std;

#define MAX_N 100000

int n, q;
string s;

struct Node {
	string name;
	Node* prev, * next;

	Node(string name) : name(name), prev(nullptr), next(nullptr) {};
};

Node* nodes[MAX_N];

void connect(Node* u, Node* v) {
	if (nullptr != u) u->next = v;
	if (nullptr != v) v->prev = u;
}

void push_next(Node* pinset, Node* node) {
	node->prev = pinset;
	node->next = pinset->next;

	if (nullptr != node->prev) node->prev->next = node;
	if (nullptr != node->next) node->next->prev = node;
}

void print_node(Node* pinset) {
	if (pinset->prev == nullptr || pinset->next == nullptr || (pinset->prev->name == pinset->next->name)) {
		cout << -1 << "\n";
		return;
	}
	cout << pinset->prev->name << " " << pinset->next->name << "\n";
}

void remove(Node* pinset) {
	Node* node = pinset->next;
	if (nullptr != node->prev) node->prev->next = node->next;
	if (nullptr != node->next) node->next->prev = node->prev;

	node->prev = node->next = nullptr;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;

	for (int i = 0; i < n; i++) {
		cin >> s;
		nodes[i] = new Node(s);
	}

	Node* pinset = nodes[0];

	for (int i = 0; i < n; i++) connect(nodes[i], nodes[i + 1]);
	connect(nodes[n - 1], nodes[0]);

	while (q--) {
		int command;
		cin >> command;
		if (command == 1) {
			if (nullptr != pinset->next) pinset = pinset->next;
		}
		else if (command == 2) {
			if (nullptr != pinset->prev) pinset = pinset->prev;
		}
		else if (command == 3) {
			remove(pinset);
		}
		else if (command == 4) {
			cin >> s;
			Node* node = new Node(s);
			push_next(pinset, node);
		}

		print_node(pinset);
	}

	return 0;
}