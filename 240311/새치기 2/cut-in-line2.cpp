#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 100000
#define MAX_M 10
int n, m, q, x;

struct Node {
	string id;
	Node* prev, * next;

	Node(string id) : id(id), prev(nullptr), next(nullptr) {}
};

Node* nodes[MAX_N + 1];
Node* heads[MAX_M + 1], * tails[MAX_M + 1];
unordered_map<string, int> people_id;
int line_num[MAX_N + 1];

void connect(Node* s, Node* e) {
	if (s) s->next = e;
	if (e) e->prev = s;
}

void pop(Node* a) {
	int a_line = line_num[people_id[a->id]];
	if (heads[a_line] == a) heads[a_line] = a->next;
	if (tails[a_line] == a) tails[a_line] = a->prev;

	connect(a->prev, a->next);
	line_num[people_id[a->id]] = 0;
}

void insert_prev(Node* a, Node* b) {
	int b_line = line_num[people_id[b->id]];
	pop(a);
	if (heads[b_line] == b) {
		connect(a, b);
		heads[b_line] = a;
	}
	else {
		connect(b->prev, a);
		connect(a, b);
	}
	line_num[people_id[a->id]] = b_line;
}


void pop_range_insert_prev(Node* a, Node* b, Node* c) {
	int a_line = line_num[people_id[a->id]];
	int c_line = line_num[people_id[c->id]];

	if (heads[a_line] == a) heads[a_line] = b->next;
	if (tails[a_line] == b) tails[a_line] = a->prev;
	connect(a->prev, b->next);

	if (heads[c_line] == c) {
		connect(b, c);
		heads[c_line] = a;
	}
	else {
		connect(c->prev, a);
		connect(b, c);
	}

	Node* cur = a;
	while (cur != b) {
		line_num[people_id[cur->id]] = c_line;
		cur = cur->next;
	}
	line_num[people_id[cur->id]] = c_line;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> q;
	x = n / m;

	int node_id = 1;
	for (int i = 1; i <= m; i++) heads[i] = tails[i] = nullptr;
	for(int i = 1; i <= m; i++){
		Node* prev = nullptr;
		for (int j = 1; j <= x; j++) {
			string name;
			cin >> name;
			people_id[name] = node_id;
			Node* target = new Node(name);
			nodes[node_id] = target;
			line_num[node_id] = i;
			if (j == 1) heads[i] = target;
			else connect(prev, target);

			if (j == x) tails[i] = target;
			
			prev = target;
			node_id++;
		}
	}

	while (q--) {
		int command;
		cin >> command;

		if (command == 1) {
			string a, b;
			cin >> a;
			cin.ignore();
			cin >> b;
			cin.ignore();
			insert_prev(nodes[people_id[a]], nodes[people_id[b]]);
		}
		else if (command == 2) {
			string a;
			cin >> a;
			cin.ignore();
			pop(nodes[people_id[a]]);
		}
		else if (command == 3) {
			string a, b, c;
			cin >> a;
			cin.ignore();
			cin >> b;
			cin.ignore();
			cin >> c;
			cin.ignore();
			pop_range_insert_prev(nodes[people_id[a]], nodes[people_id[b]], nodes[people_id[c]]);
		}
	}

	for (int i = 1; i <= m; i++) {
		Node* cur = heads[i];
		if (nullptr == cur) cout << -1 << "\n";
		else{
			while(cur) {
				cout << cur->id << " ";
				cur = cur->next;
			}
			cout << "\n";
		}
	}

	return 0;
}