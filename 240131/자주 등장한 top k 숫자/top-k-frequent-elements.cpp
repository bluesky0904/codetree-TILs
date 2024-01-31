#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int n, k;
int arr[MAX_N];
unordered_map<int, int> freq;
vector<pair<int, int>> v;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		freq[arr[i]]++;
	}

	for (auto it = freq.begin(); it != freq.end(); it++) {
		v.push_back({it->second, it->first});
	}

	sort(v.begin(), v.end());

	for (int i = v.size() - 1; k > 0; i--, k--) {
		cout << v[i].second << " ";
	}
}