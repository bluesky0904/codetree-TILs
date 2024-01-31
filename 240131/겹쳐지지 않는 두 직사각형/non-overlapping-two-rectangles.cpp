#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX_N 5

int n, m;
int grid[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

bool Overlapped() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j] > 1) return true;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}
	int ans = -INT_MAX;
	for (int s1x = 0; s1x < n; s1x++) {
		for (int s1y = 0; s1y < m; s1y++) {
			for (int e1x = s1x; e1x < n; e1x++) {
				for (int e1y = s1y; e1y < m; e1y++) {
					for (int s2x = 0; s2x < n; s2x++) {
						for (int s2y = 0; s2y < m; s2y++) {
							for (int e2x = s2x; e2x < n; e2x++) {
								for (int e2y = s2y; e2y < m; e2y++) {

									for (int i = 0; i < MAX_N; i++) {
										std::fill(visited[i], visited[i] + MAX_N, 0);
									}

									int sum1 = 0;
									for (int i = s1x; i <= e1x; i++) {
										for (int j = s1y; j <= e1y; j++) {
											visited[i][j]++;
											sum1 += grid[i][j];
										}
									}
									int sum2 = 0;
									for (int i = s2x; i <= e2x; i++) {
										for (int j = s2y; j <= e2y; j++) {
											visited[i][j]++;
											sum2 += grid[i][j];
										}
									}
									if (!Overlapped()) ans = max(ans, sum1 + sum2);
								}
							}
						}
					}
				}
			}
		}
	}
	cout << ans << "\n";
}