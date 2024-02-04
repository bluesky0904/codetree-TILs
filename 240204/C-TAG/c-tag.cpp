#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

#define MAX_N 500

int n, m;
string A[MAX_N];
string B[MAX_N];
unordered_set<string> s;

bool IsPossible(int x, int y, int z) {
	s.clear();
	for (int i = 0; i < n; i++) {
		s.insert(A[i].substr(x, 1) + A[i].substr(y, 1) + A[i].substr(z, 1));
	}
	for (int i = 0; i < n; i++) {
		if (s.find(B[i].substr(x, 1) + B[i].substr(y, 1) + B[i].substr(z, 1)) != s.end()) return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;

	for (int i = 0; i < n; i++) cin >> A[i];
	for (int i = 0; i < n; i++) cin >> B[i];

	int ans = 0;
	for (int i = 0; i < m - 2; i++) {
		for (int j = i + 1; j < m - 1; j++) {
			for (int k = j + 1; k < m; k++) {
				if (IsPossible(i, j, k)) ans++;
			}
		}
	}
	cout << ans << "\n";
}