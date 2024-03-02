#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

int n, q;

struct Node {
	int data;
	
	Node* prev, * next;

	Node(int data): data(data), prev(nullptr), next(nullptr) {};
};

unordered_map<int, Node*> nodes;

void RemoveNode(int i) {
	Node* node = nodes[i];
	if (nullptr != node->prev) node->prev->next = node->next;
	if (nullptr != node->next) node->next->prev = node->prev;
	node->prev = node->next = nullptr;
}

void InsertPrev(int i, int j) {
	Node* cur_node = nodes[i];
	Node* new_node = nodes[j];

	new_node->prev = cur_node->prev;
	new_node->next = cur_node;

	if (nullptr != new_node->prev) new_node->prev->next = new_node;
	if (nullptr != new_node->next) new_node->next->prev = new_node;
}

void InsertNext(int i, int j) {
	Node* cur_node = nodes[i];
	Node* new_node = nodes[j];

	new_node->prev = cur_node;
	new_node->next = cur_node->next;

	if (nullptr != new_node->prev) new_node->prev->next = new_node;
	if (nullptr != new_node->next) new_node->next->prev = new_node;
}

void PrintNode(int i) {
	Node* node = nodes[i];
	if (nullptr != node->prev) cout << node->prev->data << " ";
	else cout << 0 << " ";

	if (nullptr != node->next) cout << node->next->data << " ";
	else cout << 0 << " ";
	
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		Node* new_node = new Node(i);
		nodes[i] = new_node;
	}

	while (q--) {
		int command;
		int i, j;
		cin >> command;
		if (command == 1) {
			cin >> i;
			RemoveNode(i);
		}
		else if (command == 2) {
			cin >> i >> j;
			InsertPrev(i, j);
		}
		else if (command == 3) {
			cin >> i >> j;
			InsertNext(i, j);
		}
		else {
			cin >> i;
			PrintNode(i);
		}
	}

	for (int i = 1; i <= n; i++) {
		Node* cur_node = nodes[i];
		if (nullptr != cur_node->next) cout << cur_node->next->data << " ";
		else cout << 0 << " ";
	}
	cout << "\n";

	return 0;
}