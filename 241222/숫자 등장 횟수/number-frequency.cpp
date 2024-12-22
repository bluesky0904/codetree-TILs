#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

int n, m;
int arr[MAX_N];
unordered_map<int, int> cnt;

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		cnt[arr[i]]++;
	}

	for (int i = 0; i < m; i++) {
		int num; cin >> num;
		if (cnt.find(num) != cnt.end())
			cout << cnt[num] << " ";
		else
			cout << 0 << " ";
	}

	return 0;
}