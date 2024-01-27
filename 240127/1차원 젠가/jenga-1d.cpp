#include <iostream>
#include <vector>
using namespace std;

int n;

void Simulate(vector<int>& genga, int s, int e) {
	for (int i = s; i <= e; i++) genga[i] = 0;
	vector<int> tmp;
	for (int i = 0; i < genga.size(); i++) {
		if (genga[i] != 0) tmp.push_back(genga[i]);
	}
	genga = tmp;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	vector<int> genga;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		genga.push_back(x);
	}
	int s, e;
	cin >> s >> e;
	Simulate(genga, s-1, e-1);
	cin >> s >> e;
	Simulate(genga, s-1, e-1);

	cout << genga.size() << "\n";
	for (int i = 0; i < genga.size(); i++) cout << genga[i] << "\n";
}