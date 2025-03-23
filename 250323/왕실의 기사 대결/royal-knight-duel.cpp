/*
체스판 : L x L
왼쪽 상단은 (1, 1)로 시작하며, 각 칸은 빈칸, 함정, 벽
체스판 밖도 벽으로 간주

각 기사의 초기 위치 (r, c)
(r, c)를 좌측 상단으로 하며 h(높이) x w(너비) 크기의 직사각형 형태
각 기사의 체력은 k

(1) 기사 이동
기사는 상하좌우 중 하나로 한 칸 이동
이동하려는 위치에 다른 기사가 있다면 그 기사도 함께 연쇄적으로 밀려남
그 옆에 또 기사가 있다면 연쇄적으로 한 칸씩 밀리게 됨
기사가 이동하려는 방향의 끝에 벽이 있다면 모든 기사는 이동할 수 없게 됨
체스판에서 사라진 기사에게 명령을 내리면 아무런 반응이 없다.

(2) 대결 데미지
명령을 받은 기사가 다른 기사를 밀치게 되면, 밀려난 기사들은 피해를 입음
각 기사들은 해당 기사가 이동한 곳에서 w x h 직사각형 내에 놓여 있는 함정의 수만큼만 피해를 입게 됨
각 기사마다 피해를 받은 만큼 체력이 깎이게 되며, 현재 체력 이상의 대미지를 받을 경우 기사는 체스판에서 사라짐
명령을 받은 기사는 피해를 입지 않음
기사들은 모두 밀린 이후에 대미지를 입게 됨
밀렸더라도 밀쳐진 위치에 함정이 전혀 없다면 그 기사는 피해를 전혀 입지 않게 됨에 유의

Q번에 걸쳐 왕의 명령이 주어졌을 때, Q번의 대결이 모두 끝난 후 생존한 기사들이 총 받은 대미지의 합
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAXL = 40;
const int MAXN = 30;

int L, N, Q;

// 체스판 관련 자료구조
int grid[MAXL + 10][MAXL + 10];

// 기사 관련 자료구조
int r[MAXN + 10];
int nr[MAXN + 10];
int c[MAXN + 10];
int nc[MAXN + 10];
int h[MAXN + 10];
int w[MAXN + 10];
int ori_k[MAXN + 10];
int cur_k[MAXN + 10];
bool visited[MAXN + 10]; // 베열의 크기를 MAXN으로 잡는 실수...

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

bool movePossible(int id) {
	if (nr[id] < 0 || nr[id] + h[id] - 1 >= L || nc[id] < 0 || nc[id] + w[id] - 1 >= L) return false;

	for(int i = nr[id]; i < nr[id] + h[id]; i++){
		for (int j = nc[id]; j < nc[id] + w[id]; j++) {
			if (grid[i][j] == 2) return false;
		}
	}

	return true;
}

bool isOverlapped(int id1, int id2) {
	if (nr[id1] + h[id1] - 1 < nr[id2] || nr[id2] + h[id2] - 1 < nr[id1] || nc[id1] + w[id1] - 1 < nc[id2] || nc[id2] + w[id2] - 1 < nc[id1]) return false;
	return true;
}

bool isPossible(int id, int dir) {
	for (int i = 1; i <= N; i++) {
		nr[i] = r[i];
		nc[i] = c[i];
	}
	
	nr[id] += dx[dir];
	nc[id] += dy[dir];
	if (!movePossible(id)) return false;

	memset(visited, 0, sizeof(visited));
	queue<int> q;

	q.push(id);
	visited[id] = true;

	while (!q.empty()) {
		int cur = q.front(); q.pop();

		for (int i = 1; i <= N; i++) {
			if (i == cur) continue; // id가 아니라 cur을 기준으로 해야지!!!!! ㅅㅂ
			if (cur_k[i] == 0) continue;
			if (visited[i]) continue;
			if (isOverlapped(cur, i)) { // 마찬가지로 id가 아니라 cur을 기준으로 해야지 ㅅㅂ
				nr[i] += dx[dir];
				nc[i] += dy[dir];

				if (!movePossible(i)) return false;
				
				q.push(i);
				visited[i] = true;
			}
		}
	}

	return true;
}

void moveKnight(int id, int dir) {
	for (int i = 1; i <= N; i++) {
		r[i] = nr[i];
		c[i] = nc[i];
	}

	for (int i = 1; i <= N; i++) {
		if (i == id) continue;
		if (cur_k[i] == 0) continue;
		if (!visited[i]) continue;

		int cnt = 0;
		for (int x = r[i]; x < r[i] + h[i]; x++) {
			for (int y = c[i]; y < c[i] + w[i]; y++) {
				if (grid[x][y] == 1) cnt++;
			}
		}

		//cout << "cnt : " << cnt << "\n";
		cur_k[i] -= cnt;
		if (cur_k[i] < 0) cur_k[i] = 0;
	}
}

void print() {
	cout << "grid" << "\n";
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "knight info" << "\n";
	for (int i = 1; i <= N; i++) {
		cout << r[i] << " " << c[i] << " " << h[i] << " " << w[i] << " " << cur_k[i] << "\n";
	}
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> L >> N >> Q;
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= N; i++) {
		int x, y, height, width, k; cin >> x >> y >> height >> width >> k;
		x--; y--;
		r[i] = x;
		c[i] = y;
		h[i] = height;
		w[i] = width;
		ori_k[i] = cur_k[i] = k;
	}

	for (int turn = 1; turn <= Q; turn++) {
		//cout << "turn : " << turn << "\n";
		int id, dir; cin >> id >> dir;
		if (cur_k[id] == 0) continue;
		if (isPossible(id, dir)) {
			moveKnight(id, dir);
			//print();
		}
	}

	int ans = 0;
	for (int i = 1; i <= N; i++) {
		if (cur_k[i] == 0) continue;
		ans += (ori_k[i] - cur_k[i]);
	}

	cout << ans << "\n";
	return 0;
}