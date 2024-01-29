#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

int n, m;
int arr[MAX_N];
unordered_map<int, int> num_count;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		num_count[arr[i]]++;
	}
	for (int i = 0; i < m; i++) {
		int x; cin >> x;
		cout << num_count[x] << " ";
	}
	return 0;
}