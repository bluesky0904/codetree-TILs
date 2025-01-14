/*
체스판 : L x L
		 왼쪽 상단 (1, 1) 시작
		 각 칸은 빈칸, 함정, 벽
		 체스판 밖도 벽으로 간주
기사 :   초기 위치 (r, c) 좌측 상단
		 h (높이) x w (너비) 크기의 직사각형 형태
		 체력 k -> 살아있는지 여부 판단
		 초기 체력

1. 기사 이동
왕에게 명령을 받은 기사는 상하좌우 중 하나로 한 칸 이동
만약 이동하려는 위치에 다른 기사가 있다면 그 기사도 함께 연쇄적으로 한 칸 밀려남
만약 기사가 이동하려는 방향의 끝에 벽이 있다면 모든 기사는 이동 불가능
체스판에서 사라진 기사에게 명령을 내리면 아무런 반응이 없음

2. 대결 대미지
명령을 받은 기사가 다른 기사를 밀치게 되면, 밀려난 기사들은 피해를 입음.
이때 각 기사들은 해당 기사가 이동한 곳에서 w x h 직사각형 내에 놓여 있는 함정의 수만큼만 피해를 입게 됨
각 기사마다 피해를 받은 만큼 체력이 깎이게 되며, 현재 체력 이상의 대미지를 받을 경우 체스판에서 사라짐

단, 명령을 받은 기사는 피해를 입지 않으며, 기사들은 모두 밀린 이후에 대미지를 입게 됨
밀렸더라도 밀쳐진 위치에 함정이 전혀 없다면 그 기사는 피해를 전혀 입지 않게 됨

Q번에 걸쳐 왕의 명령이 주어졌을 때, Q번의 대결이 모두 끝난 후 생존한 기사들이 총 받은 대미지의 합 출력
*/
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAX_L 40
#define MAX_N 30
#define DIR_NUM 4

int l, n, q;
int grid[MAX_L + 1][MAX_L + 1];
bool visited[MAX_N + 1];
bool participate[MAX_N + 1];

int nr[MAX_N + 1], nc[MAX_N + 1];
int r[MAX_N + 1], c[MAX_N + 1];
int h[MAX_N + 1], w[MAX_N + 1];
int k[MAX_N + 1], ori_k[MAX_N + 1];

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };

bool IsIntersect(int idx1, int idx2) {
	if (nr[idx1] <= nr[idx2] && nr[idx2] <= nr[idx1] + h[idx1] - 1) return true;
	if (nr[idx1] <= nr[idx2] + h[idx2] - 1 && nr[idx2] + h[idx2] - 1 <= nr[idx1] + h[idx1] - 1) return true;
	if (nc[idx1] <= nc[idx2] && nc[idx2] <= nc[idx1] + w[idx1] - 1) return true;
	if (nc[idx1] <= nc[idx2] + w[idx2] -1 && nc[idx2] + w[idx2] - 1 <= nc[idx1] + w[idx1] - 1) return true;
	return false;
}

bool MovePossible(int idx, int d) {
	if (nr[idx] + dx[d] < 1 || nr[idx] + dx[d] > n || nc[idx] + dy[d] < 1 || nc[idx] + dy[d] > n) return false;

	for (int i = nr[idx]; i < nr[idx] + h[idx]; i++) {
		for (int j = nc[idx]; j < nc[idx] + w[idx]; j++) {
			if (grid[i][j] == 2) return false;
		}
	}

	return true;
}

void GetDamage(int idx) {
	int cnt = 0;
	for (int i = r[idx]; i < r[idx] + h[idx]; i++) {
		for (int j = c[idx]; j < c[idx] + w[idx]; j++) {
			if (grid[i][j] == 1) cnt++;
		}
	}
	k[idx] -= cnt;
	if (k[idx] < 0) k[idx] = 0;
}

void MoveKnight(int idx, int d) {
	memset(visited, false, sizeof(visited));
	memset(participate, false, sizeof(participate));

	queue<int> q;

	for (int i = 1; i <= n; i++) {
		nr[i] = r[i];
		nc[i] = c[i];
	}

	if (!MovePossible(idx, d)) return;
	nr[idx] += dx[d], nc[idx] += dy[d];

	q.push(idx);
	visited[idx] = true;
	while (!q.empty()) {
		int cx = q.front(); q.pop();

		for (int i = 1; i <= n; i++) {
			if (i == idx) continue;
			if (!visited[i] && IsIntersect(cx, i)) {
				participate[i] = true;

				if (!MovePossible(i, d)) return;
				nr[i] += dx[d], nc[i] += dy[d];

				q.push(i);
				visited[i] = true;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		r[i] = nr[i];
		c[i] = nc[i];
	}

	r[idx] = nr[idx];
	c[idx] = nc[idx];

	for (int i = 1; i <= n; i++) {
		if (!participate[i]) continue;
		GetDamage(i);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> l >> n >> q;

	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= l; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
		ori_k[i] = k[i];
	}

	while (q--) {
		int idx, d; cin >> idx >> d;
		if (k[idx] == 0) continue;
		MoveKnight(idx, d);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (k[i] == 0) continue;
		ans += (ori_k[i] - k[i]);
	}

	cout << ans << "\n";
	return 0;
}