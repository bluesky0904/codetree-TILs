/*
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

#define MAX_G 250000
int n, g;
vector<int> group[MAX_G];
unordered_set<int> get_ticket;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> g;
	get_ticket.insert(1);
	for (int i = 0; i < g; i++) {
		int group_size; cin >> group_size;
		for (int j = 0; j < group_size; j++) {
			int num; cin >> num;
			group[i].push_back(num);
		}
	}

	for (int i = 0; i < g; i++) {
		int cnt = 0;
		for (int j = 0; j < group[i].size(); j++) {
			if (get_ticket.find(group[i][j]) != get_ticket.end()) cnt++;
		}
		if (cnt + 1 == group[i].size()) {
			for (int j = 0; j < group[i].size(); j++) {
				if (get_ticket.find(group[i][j]) == get_ticket.end()) {
					get_ticket.insert(group[i][j]);
					break;
				}
			}
		}
	}

	cout << get_ticket.size() << "\n";
}
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n, g; cin >> n >> g;
	vector<unordered_set<int>> groups(g);
	for (int i = 0; i < g; i++) {
		int group_size; cin >> group_size;
		for (int j = 0; j < group_size; j++) {
			int num; cin >> num;
			groups[i].insert(num);
		}
	}

	bool updated = true;
	unordered_set<int> invited{ 1 };
	while (updated) {
		updated = false;
		for (auto& group : groups) {
			int cnt = 0;
			int lastperson;
			for (int num : group) {
				if (invited.find(num) == invited.end()) {
					cnt++;
					lastperson = num;
				}
			}
			if (cnt == 1) {
				if(invited.insert(lastperson).second) updated = true;
			}
		}
	}
	cout << invited.size() << "\n";
}