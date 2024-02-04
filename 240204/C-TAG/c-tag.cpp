#include <iostream>
#include <unordered_set>
using namespace std;

#define MAX_N 500
#define MAX_M 50

int n, m;
char arrA[MAX_N][MAX_N];
char arrB[MAX_N][MAX_N];

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arrA[i][j];
		}
		cin.ignore();
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arrB[i][j];
		}
		cin.ignore();
	}

	int ans = 0;
	for (int col1 = 0; col1 < m-2; col1++) {
		for (int col2 = col1 + 1; col2 < m - 1; col2++) {
			for (int col3 = col2 + 1; col3 < m; col3++) {
				int is_possible = true;
				string arrsetA[MAX_N];
				unordered_set<string> set1;
				unordered_set<string> set2;
				for (int row = 0; row < n; row++) {
					string s = string(1, arrA[row][col1]) + string(1, arrA[row][col2]) + string(1, arrA[row][col3]);
					set1.insert(s);
					arrsetA[row] = s;
					s = string(1, arrB[row][col1]) + string(1, arrB[row][col2]) + string(1, arrB[row][col3]);
					set2.insert(s);
				}
				for (int i = 0; i < n; i++) {
					if (set2.find(arrsetA[i]) != set2.end()) {
						is_possible = false;
						break;
					}
				}
				if(is_possible) ans++;
			}
		}
	}
	
	cout << ans << "\n";
}