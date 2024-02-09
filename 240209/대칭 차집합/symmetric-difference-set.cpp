#include <iostream>
#include <unordered_set>
using namespace std;

#define MAX_N 200000

int a_size, b_size;
int cnt;
int arrA[MAX_N];
int arrB[MAX_N];
unordered_set<int> set1;
unordered_set<int> set2;



int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> a_size >> b_size;
	for (int i = 0; i < a_size; i++) {
		cin >> arrA[i];
		set1.insert(arrA[i]);
	}
	for (int i = 0; i < b_size; i++) {
		cin >> arrB[i];
		set2.insert(arrB[i]);
	}

	int cnt = 0;
	for (int i = 0; i < a_size; i++) {
		if (set2.find(arrA[i]) != set2.end()) cnt++;
	}


	cout << a_size + b_size - 2*cnt << "\n";
}