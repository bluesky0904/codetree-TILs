#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

#define MAX_N 100
#define DIR_NUM 8

int n;
pair<int, int> start_pos;
pair<int, int> end_pos;

queue<tuple<int, int, int>> q;
bool visited[MAX_N][MAX_N];

int dx[DIR_NUM] = {-2,-1,1,2,2,1,-1,-2};
int dy[DIR_NUM] = {1,2,2,1,-1,-2,-2,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int BFS() {
	int x, y;
	tie(x, y) = start_pos;
	q.push(make_tuple(x, y, 0));
	visited[x][y] = true;
	while (!q.empty()) {
		int cx, cy, cnt;
		tie(cx, cy, cnt) = q.front();
		q.pop();

		if (make_pair(cx, cy) == end_pos) return cnt;

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny]) {
				q.push(make_tuple(nx, ny, cnt + 1));
				visited[nx][ny] = true;
			}
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	int r, c;
	cin >> r >> c;
	start_pos = make_pair(r - 1, c - 1);
	cin >> r >> c;
	end_pos = make_pair(r - 1, c - 1);

	cout << BFS() << "\n";
	return 0;
}