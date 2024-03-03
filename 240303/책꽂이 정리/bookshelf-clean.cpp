#include <iostream>
using namespace std;

#define MAX_N 250000
#define MAX_K 100

int n, k, q;

struct Node {
	int data;

	Node* prev, * next;

	Node(int data) : data(data), prev(nullptr), next(nullptr) {};
};

Node* nodes[MAX_N + 1];
Node* heads[MAX_K + 1], * tails[MAX_K + 1];

bool empty(int i) {
	return nullptr == heads[i];
}

void connect(Node* u, Node* v) {
	if (nullptr != u) u->next = v;
	if (nullptr != v) v->prev = u;
}

Node* pop_front(int i) {
	Node* ret = heads[i];

	if (nullptr != ret) {
		heads[i] = ret->next;
		ret->next = nullptr;
		if (nullptr != heads[i]) heads[i]->prev = nullptr;
		else tails[i] = nullptr;
	}

	return ret;
}

Node* pop_back(int i) {
	Node* ret = tails[i];

	if (nullptr != ret) {
		tails[i] = ret->prev;
		ret->prev = nullptr;
		if (nullptr != tails[i]) tails[i]->next = nullptr;
		else heads[i] = nullptr;
	}

	return ret;
}

void push_front(int i, Node* node) {
	if (nullptr == heads[i]) heads[i] = tails[i] = node;
	else {
		connect(node, heads[i]);
		heads[i] = node;
	}
}

void push_back(int i, Node* node) {
	if (nullptr == tails[i]) heads[i] = tails[i] = node;
	else {
		connect(tails[i], node);
		tails[i] = node;
	}
}

void move_all_front(int i, int j) {
	if (i == j || empty(i)) return;
	if (empty(j)) {
		heads[j] = heads[i];
		tails[j] = tails[i];
	}
	else {
		connect(tails[i], heads[j]);
		heads[j] = heads[i];
	}

	heads[i] = tails[i] = nullptr;
}

void move_all_back(int i, int j) {
	if (i == j || empty(i)) return;
	if (empty(j)) {
		heads[j] = heads[i];
		tails[j] = tails[i];
	}
	else {
		connect(tails[j], heads[i]);
		tails[j] = tails[i];
	}

	heads[i] = tails[i] = nullptr;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k >> q;
	for (int i = 1; i <= n; i++) nodes[i] = new Node(i);
	for (int i = 1; i < n; i++) connect(nodes[i], nodes[i + 1]);
	for (int i = 1; i <= k; i++) heads[i] = tails[i] = nullptr;

	while (q--) {
		int command, i, j;
		cin >> command >> i >> j;
		if (command == 1) {
			Node* node = pop_front(i);
			if (nullptr != node) push_back(j, node);
		}
		else if (command == 2) {
			Node* node = pop_back(i);
			if (nullptr != node) push_front(j, node);
		}
		else if (command == 3) {
			move_all_front(i, j);
		}
		else if (command == 4) {
			move_all_back(i, j);
		}
	}

	for (int i = 1; i <= k; i++) {
		int cnt = 0;

		Node* cur = heads[i];
		while (nullptr != cur) {
			cnt++;
			cur = cur->next;
		}
		cout << cnt << " ";

		cur = heads[i];
		while (nullptr != cur) {
			cout << cur->data << " ";
			cur = cur->next;
		}

		cout << "\n";
	}

	for (int i = 1; i <= n; i++) {
		delete nodes[i];
		nodes[i] = nullptr;
	}

	return 0;
}