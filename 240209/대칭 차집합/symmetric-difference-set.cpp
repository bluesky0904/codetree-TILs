#include <iostream>
#include <unordered_set>
using namespace std;

#define MAX_N 200000

int n, m;
int A[MAX_N];
int B[MAX_N];
int ans;

unordered_set<int> s;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		s.insert(A[i]);
	}
	for (int i = 0; i < m; i++) {
		cin >> B[i];
	}

	ans = n + m;

	for (int i = 0; i < m; i++) {
		if (s.find(B[i]) != s.end()) ans -= 2;
	}

	cout << ans << "\n";
}