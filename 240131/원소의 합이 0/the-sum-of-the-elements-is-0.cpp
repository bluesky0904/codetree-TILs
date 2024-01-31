#include <iostream>
using namespace std;

#define MAX_N 5000

int n;
int arr[4][MAX_N];

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	int ans = 0;
	for (int num1 = 0; num1 < n; num1++) {
		for (int num2 = 0; num2 < n; num2++) {
			for (int num3 = 0; num3 < n; num3++) {
				for (int num4 = 0; num4 < n; num4++) {
					if (arr[0][num1] + arr[1][num2] + arr[2][num3] + arr[3][num4] == 0) ans++;
				}
			}
		}
	}
	cout << ans << "\n";
}