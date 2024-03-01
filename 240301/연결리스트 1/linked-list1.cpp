#include <iostream>
using namespace std;

string s;
int n;

struct Node {
	string data;

	Node* prev, * next;

	Node(string data) : data(data), prev(nullptr), next(nullptr) {};
};

void InsertPrev(Node* cur, Node* new_node) {
	new_node->prev = cur->prev;
	new_node->next = cur;

	if (nullptr != new_node->prev) new_node->prev->next = new_node;
	if (nullptr != new_node->next) new_node->next->prev = new_node;
}

void InsertNext(Node* cur, Node* new_node) {
	new_node->prev = cur;
	new_node->next = cur->next;

	if (nullptr != new_node->prev) new_node->prev->next = new_node;
	if (nullptr != new_node->next) new_node->next->prev = new_node;
}

void PrintNode(Node* cur) {
	if (nullptr != cur->prev) cout << cur->prev->data << " ";
	else cout << "(Null)" << " ";

	cout << cur->data << " ";

	if (nullptr != cur->next) cout << cur->next->data << " ";
	else cout << "(Null)" << " ";
	
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> s;
	Node* cur = new Node(s);
	cin >> n;
	while (n--) {
		int x;
		cin >> x;
		if (x == 1) {
			cin >> s;
			Node* new_node = new Node(s);
			InsertPrev(cur, new_node);
		}
		else if (x == 2) {
			cin >> s;
			Node* new_node = new Node(s);
			InsertNext(cur, new_node);
		}
		else if (x == 3) {
			if (nullptr != cur->prev) cur = cur->prev;
		}
		else {
			if (nullptr != cur->next) cur = cur->next;
		}

		PrintNode(cur);
	}
	return 0;
}