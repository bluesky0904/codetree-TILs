#include <iostream>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

#define MAX_N 1000000

int n;
int min_cnt = INT_MAX;

queue<pair<int, int>> q;
bool visited[2 * MAX_N];

bool InRange(int x) {
	return 1 <= x && x <= 2 * n - 1;
}

int BFS() {
	q.push(make_pair(n, 0));
	visited[n] = true;
	while (!q.empty()) {
		int cx, cnt;
		tie(cx, cnt) = q.front();
		q.pop();

		if (cx == 1) min_cnt = min(min_cnt, cnt);
		
		if (InRange(cx - 1) && !visited[cx - 1]) {
			q.push(make_pair(cx - 1, cnt + 1));
			visited[cx - 1] = true;
		}

		if (InRange(cx + 1) && !visited[cx + 1]) {
			q.push(make_pair(cx + 1, cnt + 1));
			visited[cx + 1] = true;
		}

		if (cx % 2 == 0 && InRange(cx / 2) && !visited[cx / 2]) {
			q.push(make_pair(cx/2, cnt + 1));
			visited[cx / 2] = true;
		}

		if (cx % 3 == 0 && InRange(cx / 3) && !visited[cx / 3]) {
			q.push(make_pair(cx / 3, cnt + 1));
			visited[cx / 3] = true;
		}
	}
	return min_cnt;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	cout << BFS() << "\n";
}