#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
	int num;

	Node* prev, * next;

	Node(int num) : num(num), prev(nullptr), next(nullptr) {};
};

int q;
int idx;

unordered_map<int, Node*> nodes;

void connect(Node* s, Node* e) {
	if (s) s->next = e;
	if (e) e->prev = s;
}

void insert_next(int a, int b) {
	Node* a_next = nodes[a]->next;
	Node* prev = nullptr;
	for (int i = 1; i <= b; i++) {
		Node* target = new Node(idx);
		nodes[idx] = target;
		idx++;
		if (i == 1) connect(nodes[a], target);
		else connect(prev, target);

		if (i == b) connect(target, a_next);
		
		prev = target;
	}
}

void insert_prev(int a, int b) {
	Node* a_prev = nodes[a]->prev;
	Node* prev = nullptr;
	for (int i = 1; i <= b; i++) {
		Node* target = new Node(idx);
		nodes[idx] = target;
		idx++;
		if (i == 1) connect(a_prev, target);
		else connect(prev, target);

		if (i == b) connect(target, nodes[a]);

		prev = target;
	}
}

void find_neighbor(int a) {
	Node* node = nodes[a];
	if (nullptr == node->prev || nullptr == node->next) cout << -1 << "\n";
	else cout << node->prev->num << " " << node->next->num << "\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> q;
	nodes[1] = new Node(1);
	idx = 2;
	while (q--) {
		int command, a, b;
		cin >> command;
		if (command == 1) {
			cin >> a >> b;
			insert_next(a, b);
		}
		else if (command == 2) {
			cin >> a >> b;
			insert_prev(a, b);
		}
		else if (command == 3) {
			cin >> a;
			find_neighbor(a);
		}
	}

	return 0;
}