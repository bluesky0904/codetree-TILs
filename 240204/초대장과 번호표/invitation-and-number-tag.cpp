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
			int person; cin >> person;
			groups[i].insert(person);
		}
	}

	bool updated = true;
	unordered_set<int> invited{ 1 };
	while (updated) {
		updated = false;
		for (auto& group : groups) {
			int cnt = 0;
			int lastperson;
			for (int person : group) {
				if (invited.find(person) == invited.end()) {
					cnt++;
					lastperson = person;
				}
			}
			if (cnt == 1) {
				if (invited.insert(lastperson).second) updated = true;
			}
		}
	}
	cout << invited.size() << "\n";
}