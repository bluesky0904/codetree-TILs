#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX_N 30
#define INF (int)1e9
#define DIR_NUM 4

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

char grid[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

int N, A, B;

bool InRange(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

void dijkstra(int x, int y) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = INF;
		}
	}

	dist[x][y] = 0;

	pq.push(make_tuple(0, x, y));

	while (!pq.empty()) {
		int min_dist, min_x, min_y;
		tie(min_dist, min_x, min_y) = pq.top();
		pq.pop();

		if (dist[min_x][min_y] != min_dist) continue;

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = min_x + dx[dir], ny = min_y + dy[dir];
			int next_dist = 0;
			if (!InRange(nx, ny)) continue;
			
			if (grid[min_x][min_y] == grid[nx][ny]) next_dist = A;
			else next_dist = B;

			int new_dist = min_dist + next_dist;
			if (dist[nx][ny] > new_dist) {
				dist[nx][ny] = new_dist;
				pq.push(make_tuple(new_dist, nx, ny));
			}
		}
	}
}

int FindMaxDist() {
	int max_dist = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			max_dist = max(max_dist, dist[i][j]);
		}
	}

	return max_dist;
}

int main() {
	cin >> N >> A >> B;
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		for (int j = 0; j < N; j++) {
			grid[i][j] = s[j];
		}
	}

	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dijkstra(i, j);
			ans = max(ans, FindMaxDist());
		}
	}

	cout << ans << "\n";
	return 0;
}