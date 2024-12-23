#include <iostream>
#include <unordered_set>
using namespace std;

int n;
unordered_set<int> my_set;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		int x; cin >> x;
		if (s == "add") 
			my_set.insert(x);
		else if (s == "remove")
			my_set.erase(x);
		else {
			if (my_set.find(x) == my_set.end())
				cout << "false" << "\n";
			else
				cout << "true" << "\n";
		}
	}
}