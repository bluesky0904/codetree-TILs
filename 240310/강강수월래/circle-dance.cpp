#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int n, m, q;

struct Node {
	int id;
	Node* prev, * next;

	Node(int id) : id(id), prev(nullptr), next(nullptr) {}
};

Node* nodes[MAX_N + 1];
unordered_map<int, int> student_id;

void connect(Node* s, Node* e) {
	if (s) s->next = e;
	if (e) e->prev = s;
}

void connect_circle(Node* u, Node* v) {
	Node* u_next = u->next;
	Node* v_prev = v->prev;

	connect(u, v);
	connect(v_prev, u_next);
}

void split_circle(Node* u, Node* v) {
	Node* u_prev = u->prev;
	Node* v_prev = v->prev;

	connect(v_prev, u);
	connect(u_prev, v);
}

void PrintLine(Node* target) {
	int min_num = target->id;
	Node* cur = target;
	while (true) {
		cur = cur->next;
		if (cur != nullptr) min_num = min(min_num, cur->id);
		if (cur == target) break;
	}

	Node* init = nodes[student_id[min_num]];
	cur = nodes[student_id[min_num]];
	while (true) {
		cout << cur->id << ' ';
		cur = cur->prev;
		if (cur->id == init->id) break;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> q;
	
	int node_cnt = 1;
	for (int i = 1; i <= m; i++) {
		int student_num;
		cin >> student_num;
		Node* start = nullptr;
		Node* tail = nullptr;
		for (int j = 0; j < student_num; j++) {
			int num;
			cin >> num;
			student_id[num] = node_cnt;
			nodes[node_cnt] = new Node(num);
			if (j == 0) {
				start = nodes[node_cnt];
				tail = nodes[node_cnt];
			}
			else {
				connect(tail, nodes[node_cnt]);
				tail = nodes[node_cnt];
				if (j == student_num - 1) connect(tail, start);
			}
			node_cnt++;
		}
	}

	while (q--) {
		int command;
		cin >> command;

		if (command == 1) {
			int a, b;
			cin >> a >> b;
			connect_circle(nodes[student_id[a]], nodes[student_id[b]]);
		}
		else if (command == 2) {
			int a, b;
			cin >> a >> b;
			split_circle(nodes[student_id[a]], nodes[student_id[b]]);
		}
		else if (command == 3) {
			int a;
			cin >> a;
			PrintLine(nodes[student_id[a]]);
		}
	}

	return 0;
}