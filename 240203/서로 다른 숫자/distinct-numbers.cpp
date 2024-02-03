#include <iostream>
#include <unordered_set>
using namespace std;

int n;
unordered_set<int> s;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num; cin >> num;
		s.insert(num);
	}
	cout << s.size() << "\n";
}