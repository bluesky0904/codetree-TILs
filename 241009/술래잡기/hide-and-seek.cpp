/*
격자 : n * n
술래 : 초기 위치 정중앙
	속성 : 위치, 바라보는 방향
도망자 : m명, 시작 위치가 정중앙은 아님
	좌우로만 움직이는 유형 : 오른쪽을 보고 시작
	상하로만 움직이는 유형 : 아래쪽을 보고 시작
	속성 : 위치(격자의 인덱스), 바라보는 방향(격자 안의 값 : 0,1,2,3), 생존 여부(벡터이기 때문에 없으면 죽은거임)
나무 : h개, 도망자와 초기에 겹쳐져 주어질 수 있음

k번 반복
1. m명의 도망자 이동
if(술래와의 거리 <= 3) 이동, 이동 거리는 |x1 - x2| + |y1 - y2|로 정의
if(InRange(nx, ny)) 
	if(nx, ny == 술래) 이동x
	else 이동 o, 나무가 있어도 괜찮음 
else 방향을 반대로 틀고 
	if(nx, ny == 술래) 이동x
	else 이동 o, 나무가 있어도 괜찮음

2. 술래 이동
1) 이동
처음 위 방향으로 시작하여 달팽이 모양으로 움직임.
끝애 도달하게 되면 다시 거꾸로 중심으로 이동.
즉 시계방향으로 도는 것을 k턴에 걸쳐 반복
1턴에 1칸만 이동. 이동 후의 위치가 만약 이동방향이 틀어지는 지점이라면, 방향을 바로 틀어줌. (1행, 1열), 정중앙 역시 마찬가지
2) 도망자 잡기
현재 바라보고 있는 방향을 기준으로 현재 칸을 포함하여 3칸.
나무가 놓여 있는 칸이라면 도망자는 잡히지 않음
3) 점수 획득
현재 턴을 t라 했을 때, ans += t * 현재 턴에서 잡힌 도망자의 수

=> k번 턴동안 술래가 얻게된 총 점수 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 99
#define DIR_NUM 4

int n, m, h, k;

int catcher_x, catcher_y, catcher_dir; // catcher가 이동해야할 방향들을 하나의 배열에 모두 저장시켜두기
bool is_clock = true;
int clock_dir[MAX_N + 1][MAX_N + 1];
int counterclock_dir[MAX_N + 1][MAX_N + 1];

vector<int> runner[MAX_N + 1][MAX_N + 1];
vector<int> next_runner[MAX_N + 1][MAX_N + 1];

bool tree[MAX_N + 1][MAX_N + 1];

int ans = 0;

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool InRange(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

void FillClockDir() {
	int x = n / 2 + 1;
	int y = n / 2 + 1;
	int dir = 0;
	int dist = 1;
	
	while (true) {
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= dist; j++) {
				clock_dir[x][y] = dir;
				x += dx[dir], y += dy[dir];
				if (x == 1 && y == 1) return;
			}
			dir = (dir + 1) % 4;
		}
		dist++;
	}
}

void FillCounterClockDir() {
	for (int i = 1; i < n; i++) {
		counterclock_dir[i][1] = 2;
	}
	
	int x = n;
	int y = 1;
	int dir = 1;
	int dist = 4;

	while (true) {
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= dist; j++) {
				counterclock_dir[x][y] = dir;
				x += dx[dir], y += dy[dir];
				if (x == n/2 + 1 && y == n/2 + 1) return;
			}
			dir = (dir + 3) % 4;
		}
		dist--;
	}
}

void MoveRunner() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			next_runner[i][j].clear();
		}
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			if (runner[x][y].empty()) continue;
			if (abs(catcher_x - x) + abs(catcher_y - y) > 3) {
				for(int i = 0; i < (int)runner[x][y].size(); i++)
					next_runner[x][y].push_back(runner[x][y][i]);
			}
			else {
				for (int i = 0; i < (int)runner[x][y].size(); i++) {
					int dir = runner[x][y][i];
					//cout << dir << "\n";
					int nx = x + dx[dir], ny = y + dy[dir];
					if (InRange(nx, ny)) {
						if (nx == catcher_x && ny == catcher_y) next_runner[x][y].push_back(dir);
						else next_runner[nx][ny].push_back(dir);
					}
					else {
						dir = (dir + 2) % 4;
						nx = x + dx[dir], ny = y + dy[dir];
						if (nx == catcher_x && ny == catcher_y) next_runner[x][y].push_back(dir);
						else next_runner[nx][ny].push_back(dir);
					}
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			runner[i][j] = next_runner[i][j];
		}
	}
}

void MoveCatcher() {
	if (is_clock) {
		catcher_x += dx[catcher_dir], catcher_y += dy[catcher_dir];
		if (catcher_x == 1 && catcher_y == 1) {
			is_clock = false;
			catcher_dir = counterclock_dir[catcher_x][catcher_y];
		}
		else catcher_dir = clock_dir[catcher_x][catcher_y];
	}
	else {
		catcher_x += dx[catcher_dir], catcher_y += dy[catcher_dir];
		if (catcher_x == n / 2 + 1 && catcher_y == n / 2 + 1) {
			is_clock = true;
			catcher_dir = clock_dir[catcher_x][catcher_y];
		}
		else catcher_dir = counterclock_dir[catcher_x][catcher_y];
	}
}

void CatchScore(int turn) {
	int cnt = 0;
	vector<pair<int, int>> seek_pos;
	for (int dist = 0; dist <= 2; dist++) {
		int x = catcher_x + dx[catcher_dir] * dist, y = catcher_y + dy[catcher_dir] * dist;
		if(InRange(x, y)) seek_pos.push_back({ x, y });
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			if (runner[x][y].empty()) continue;
			for (int num = 0; num < (int)seek_pos.size(); num++) {
				if (seek_pos[num] == make_pair(x, y)) {
					if (tree[x][y]) continue;
					cnt += (int)runner[x][y].size();
					runner[x][y].clear();
					break;
				}
			}
		}
	}

	ans += (turn * cnt);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m >> h >> k;
	for (int i = 1; i <= m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		if (d == 1) runner[x][y].push_back(1);
		else if (d == 2) runner[x][y].push_back(2);
	}

	for (int i = 1; i <= h; i++) {
		int x, y;
		cin >> x >> y;
		tree[x][y] = true;
	}

	FillClockDir();
	FillCounterClockDir();
	catcher_x = n / 2 + 1, catcher_y = n / 2 + 1, catcher_dir = 0;

	

	for (int turn = 1; turn <= k; turn++) {
		//cout << "/////////////////turn " << turn << " ////////////////\n";
		MoveRunner();
		
		MoveCatcher();
		//cout << "Catcher :" << catcher_x << " " << catcher_y << "\n";
		CatchScore(turn);
		//cout << turn << " : " << ans << "\n";
	}

	cout << ans << "\n";
	return 0;
}