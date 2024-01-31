#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 5000

int n;
int A[MAX_N];
int B[MAX_N];
int C[MAX_N];
int D[MAX_N];
unordered_map<int, int> mid_sum;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) cin >> A[i];
	for (int i = 0; i < n; i++) cin >> B[i];
	for (int i = 0; i < n; i++) cin >> C[i];
	for (int i = 0; i < n; i++) cin >> D[i];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mid_sum[A[i] + B[j]]++;
		}
	}

	int ans = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans += mid_sum[-(C[i] + D[j])];
		}
	}
	
	cout << ans << "\n";
}