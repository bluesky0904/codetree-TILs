/*
체스판 : L * L, 각 칸은 빈칸0, 함정1, 벽2
왕실의 기사 : 좌측 상단 (r, c) 높이 넓이 h, w 체력 k -> 5개의 요소로 구성
(1) 기사 이동
체스판에 있는 기사일 경우(k[] > 0)
끝에 벽이 있다면 -> 이동 x
끝에 벽이 없다면 -> 연쇄적으로 이동
(2) 대결 대미지
밀려난 각 기사들은 모두 밀린 후 해당 기사가 이동한 곳에서 w * h 직사각형 내에 놓여 있는 함정의 수만큼만 피해를 입음 but 현재 체력 이상의 대미지를 받을 경우 기사는 체스판에서 사라짐
*/

#include <iostream>
#include <queue>
using namespace std;

#define MAX_L 40
#define MAX_N 30
#define DIR_NUM 4

int L, N, Q;

int grid[MAX_L + 1][MAX_L + 1];
int r[MAX_N + 1], c[MAX_N + 1];
int nr[MAX_N + 1], nc[MAX_N + 1];
int h[MAX_N + 1], w[MAX_N + 1];
int bef_k[MAX_N + 1], k[MAX_N + 1], dmg[MAX_N + 1];
bool visited[MAX_N + 1];

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool MovePossible(int id, int dir) {
	for (int i = 1; i <= N; i++) {
		nr[i] = r[i];
		nc[i] = c[i];
		dmg[i] = 0;
		visited[i] = false;
	}

	queue<int> q;
	q.push(id);
	visited[id] = true;

	while (!q.empty()) {
		int x = q.front(); q.pop();

		nr[x] += dx[dir], nc[x] += dy[dir];

		if (nr[x] < 1 || nr[x] + h[x] - 1 > L || nc[x] < 1 || nc[x] + w[x] - 1 > L) return false;

		for (int i = nr[x]; i <= nr[x] + h[x] - 1; i++) {
			for (int j = nc[x]; j <= nc[x] + w[x] - 1; j++) {
				if (grid[i][j] == 1) dmg[x]++;
				if (grid[i][j] == 2) return false;
			}
		}

		for (int i = 1; i <= N; i++) {
			if (k[i] <= 0 || visited[i]) continue;
			if (r[i] + h[i] - 1 < nr[x] || nr[x] + h[x] - 1 < r[i] || nc[x] + w[x] - 1 < c[i] || c[i] + w[i] - 1 < nc[x]) continue;
			q.push(i);
			visited[i] = true;
		}
	}

	dmg[id] = 0;
	return true;
}

void MoveKnight(int id, int dir) {
	if (k[id] <= 0) return;
	if (MovePossible(id, dir)) {
		for (int i = 1; i <= N; i++) {
			r[i] = nr[i];
			c[i] = nc[i];
			k[i] -= dmg[i];
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> L >> N >> Q;
	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= N; i++) {
		cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
		bef_k[i] = k[i];
	}

	while (Q--) {
		int id, dir;
		cin >> id >> dir;
		MoveKnight(id, dir);
	}

	int ans = 0;
	for (int i = 1; i <= N; i++) {
		if(k[i] > 0) ans += (bef_k[i] - k[i]);
	}
	cout << ans << "\n";
	return 0;
}