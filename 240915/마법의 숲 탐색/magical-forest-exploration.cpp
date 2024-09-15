#include <iostream>
#include <queue>
using namespace std;

#define MAX_L 70

int R, C, K;
int A[MAX_L + 3][MAX_L];
int dy[4] = {-1,0,1,0}, dx[4] = {0,1,0,-1};
bool IsExit[MAX_L + 3][MAX_L];
int ans = 0;

bool InRange(int y, int x) {
	return 3 <= y && y < R + 3 && 0 <= x && x < C;
}

void ResetMap() {
	for (int i = 0; i < R + 3; i++) {
		for (int j = 0; j < C; j++) {
			A[i][j] = 0;
			IsExit[i][j] = false;
		}
	}
}

bool CanGo(int y, int x) {
	bool flag = 0 <= x - 1 && x + 1 < C && y + 1 < R + 3;
	flag = flag && (A[y-1][x-1] == 0);
	flag = flag && (A[y - 1][x] == 0);
	flag = flag && (A[y - 1][x+1] == 0);
	flag = flag && (A[y][x-1] == 0);
	flag = flag && (A[y][x] == 0);
	flag = flag && (A[y][x+1] == 0);
	flag = flag && (A[y+1][x] == 0);
	return flag;
}

int BFS(int y, int x) {
	int rslt = y;
	queue<pair<int, int>> q;
	bool visited[MAX_L + 3][MAX_L] = {false};
	
	q.push({ y,x });
	visited[y][x] = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		for (int k = 0; k < 4; k++) {
			int ny = cur.first + dy[k], nx = cur.second + dx[k];
			if (InRange(ny, nx) && !visited[ny][nx] && (A[ny][nx] == A[cur.first][cur.second] || (A[ny][nx] != 0 && IsExit[cur.first][cur.second]))) {
				q.push({ ny,nx });
				visited[ny][nx] = true;
				rslt = max(rslt, ny);
			}
		}
	}
	return rslt;
}

void Down(int y, int x, int d, int id) {
	if (CanGo(y + 1, x)) Down(y + 1, x, d, id);
	else if (CanGo(y + 1, x - 1)) Down(y + 1, x - 1, (d + 3) % 4, id);
	else if (CanGo(y + 1, x + 1)) Down(y + 1, x + 1, (d + 1) % 4, id);
	else {
		if (!InRange(y - 1, x - 1) || !InRange(y + 1, x + 1)) ResetMap();
		else {
			A[y][x] = id;
			for (int k = 0; k < 4; k++)
				A[y + dy[k]][x + dx[k]] = id;
			IsExit[y + dy[d]][x + dx[d]] = true;
			ans += BFS(y, x) - 3 + 1;
		}
	}
}

int main() {
	ios::sync_with_stdio (0); cin.tie (0); cout.tie (0);
	cin >> R >> C >> K;

	for (int id = 1; id <= K; id++) {
		int x, d;
		cin >> x >> d;
		x--;
		Down(0, x, d, id);
	}
	cout << ans << "\n";
	return 0;
}