#include <iostream>
#include <unordered_set>
using namespace std;

#define MAX_N 100000

int n, m;
int arr1[MAX_N];
int arr2[MAX_N];
unordered_set<int> s1;
unordered_set<int> s2;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr1[i];
	for (int i = 0; i < n; i++)
		s1.insert(arr1[i]);

	cin >> m;
	for (int i = 0; i < m; i++)
		cin >> arr2[i];
	for(int i = 0; i < m; i++)
		s2.insert(arr2[i]);

	for (int i = 0; i < m; i++) {
		if (s1.find(arr2[i]) == s1.end())
			cout << 0 << " ";
		else
			cout << 1 << " ";
	}
}