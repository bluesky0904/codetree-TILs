/*
나선형 미로 : n x n, 1-based
몬스터 : 1번, 2번, 3번
플레이어 : 격자 속 가운데 탑에서 몬스터를 제거하려고 함
점수

1. 플레이어는 상하좌우 방향 중 주어진 공격 칸 수만큼 몬스터를 공격하여 없앨 수 있음
공격방향 / 공격칸수

2. 비어있는 공간만큼 몬스터는 앞으로 이동하여 빈 공간을 채움

3. 이때 몬스터의 종류가 4번 이상 반복하여 나오면 해당 몬스터 또한 삭제
해당 몬스터들은 동시에 사라짐

삭제된 이후에는 몬스터들을 앞으로 당겨주고, 4번 이상 나오는 몬스터가 있을 경우 또 삭제를 해줌. 
4번 이상 나오는 몬스터가 없을 때까지 반복

4. 삭제가 끝난 다음에는 몬스터를 차례대로 나열했을 때 같은 숫자끼리 짝을 지어줌.
이후 각각의 짝을 (총 개수, 숫자의 크기)로 바꾸어서 다시 미로 속에 집어넣음

만약 새로 생긴 배열이 원래 격자의 범위를 넘는다면 나머지 배열은 무시

해당 과정이 끝나면 한 라운드가 끝
1과 3 과정에서 삭제되는 몬스터의 번호는 점수에 합쳐짐
(삭제되는 몬스터의 번호 x 삭제되는 몬스터의 숫자)의 합

각 라운드별로 공격 방향과 공격 칸수가 주어질 때 모든 라운드가 끝난 후 플레이어가 얻게되는 점수?
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 25
#define MONSTER_TYPE 3
#define DIR_NUM 4

int n, m;
int grid[MAX_N + 1][MAX_N + 1];
vector<int> monsters;
vector<int> next_monsters;
int counter_clock_dir[MAX_N + 1][MAX_N + 1];
int score = 0;

int dx[DIR_NUM] = {0,1,0,-1};
int dy[DIR_NUM] = {1,0,-1,0};

/*
0 : 우
1 : 하
2 : 좌
3 : 상
증가하면 시계방향 d = (d + 1) % DIR_NUM
감소하면 반시계 방향 d = (d + 3) % DIR_NUM

x 2 2 2 2 2 2
1 2 2 2 2 2 3
1 1 2 2 2 3 3
1 1 1 x 3 3 3
1 1 0 0 3 3 3
1 0 0 0 0 3 3
0 0 0 0 0 0 3

1 2 3 3 3 3 2 3 1 2 1 1 1 1 1 2 2 2 3 1
*/

void setCounterClockDir() {
	int cx = (n + 1) / 2, cy = (n + 1) / 2;
	int c_dir = 2, c_dist = 1;

	while (!(cx == 1 && cy == 1)) {
		for (int cnt = 1; cnt <= 2; cnt++) {
			for (int i = 1; i <= c_dist; i++) {
				counter_clock_dir[cx][cy] = c_dir;
				cx += dx[c_dir], cy += dy[c_dir];

				if (cx == 1 && cy == 1) return;
			}
			c_dir = (c_dir + 3) % DIR_NUM;
		}
		c_dist++;
	}
}

bool inRange(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

void attack(int d, int p) {
	int tmp[MONSTER_TYPE + 1] = { 0, };

	int cx = (n + 1) / 2, cy = (n + 1) / 2;
	for (int dist = 1; dist <= p; dist++) {
		int nx = cx + dx[d] * dist, ny = cy + dy[d] * dist;
		if (inRange(nx, ny) && grid[nx][ny] > 0) {
			tmp[grid[nx][ny]]++;
			grid[nx][ny] = 0;
		}
	}

	for (int i = 1; i <= MONSTER_TYPE; i++) {
		score += (i * tmp[i]);
	}
}

void gridToVec() {
	monsters.clear();
	
	int cx = (n + 1) / 2, cy = ((n + 1) / 2) - 1;
	while (true) {
		if(grid[cx][cy] > 0) monsters.push_back(grid[cx][cy]);
		int cd = counter_clock_dir[cx][cy];
		cx += dx[cd], cy += dy[cd];
		if (cx == 1 && cy == 1) {
			if (grid[cx][cy] > 0) monsters.push_back(grid[cx][cy]);
			return;
		}
	}
}

/*
3. 이때 몬스터의 종류가 4번 이상 반복하여 나오면 해당 몬스터 또한 삭제
해당 몬스터들은 동시에 사라짐

삭제된 이후에는 몬스터들을 앞으로 당겨주고, 4번 이상 나오는 몬스터가 있을 경우 또 삭제를 해줌.
4번 이상 나오는 몬스터가 없을 때까지 반복

idx   : 0 1 2 3 4 5 6 7 8 9 
value : 1 2 3 3 3 3 2 3 1 2 1 1 1 1 1 2 2 2 3 1
*/
void remove() {
	int tmp[MONSTER_TYPE + 1] = { 0, };

	while (1) {
		int size = (int)monsters.size();
		bool is_over = true;
		int cnt = 1;

		for (int i = 0; i < size - 1; i++) {
			// is_over 변수 업데이트
			if (monsters[i] == monsters[i + 1]) {
				if(i != size - 2) cnt++;
				else {
					cnt++;
					if (cnt >= 4) {
						tmp[monsters[i]] += cnt;
						for (int j = 0; j < cnt; j++) {
							monsters[i + 1- j] = 0;
						}
						is_over = false;
						cnt = 1;
					}
				}
			}
			else {
				if (cnt >= 4) {
					tmp[monsters[i]] += cnt;
					for (int j = 0; j < cnt; j++) {
						monsters[i - j] = 0;
					}
					is_over = false;
					cnt = 1;
				}
				else cnt = 1;
			}
		}

		if (is_over) break;
		else {
			next_monsters.clear();

			for (int i = 0; i < (int)monsters.size(); i++) {
				if (monsters[i] > 0) next_monsters.push_back(monsters[i]);
			}

			monsters.clear();
			for (int i = 0; i < (int)next_monsters.size(); i++) {
				monsters.push_back(next_monsters[i]);
			}
		}
	}

	for (int i = 1; i <= MONSTER_TYPE; i++) {
		score += (i * tmp[i]);
	}
}

// 이 부분 다시 파기!!!!!!!!!!!!!!!
void rearrange() {
	next_monsters.clear();
	int cnt = 1;
	int size = (int)monsters.size();

	for (int i = 0; i < size - 1; i++) {
		if (monsters[i] == monsters[i + 1]) {
			if (i != size - 2) cnt++;
			else {
				cnt++;
				next_monsters.push_back(cnt);
				next_monsters.push_back(monsters[i]);
			}
		}
		else {
			if (i != size - 2) {
				next_monsters.push_back(cnt);
				next_monsters.push_back(monsters[i]);
				cnt = 1;
			}
			else {
				next_monsters.push_back(cnt);
				next_monsters.push_back(monsters[i]);

				next_monsters.push_back(1);
				next_monsters.push_back(monsters[i + 1]);
			}
		}
	}

	monsters.clear();
	for (int i = 0; i < (int)next_monsters.size(); i++) {
		monsters.push_back(next_monsters[i]);
	}
}

void vecToGrid() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = 0;
		}
	}

	int cx = (n + 1) / 2, cy = ((n + 1) / 2) - 1, cd = 1;

	for (int i = 0; i < (int)monsters.size(); i++) {
		grid[cx][cy] = monsters[i];
		cd = counter_clock_dir[cx][cy];
		cx += dx[cd], cy += dy[cd];
	}
}

void print() {
	cout << "GRID" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "MONSTERS" << "\n";
	for (int i = 0; i < (int)monsters.size(); i++) {
		cout << monsters[i] << " ";
	}
	cout << "\n";

	cout << "SCORE : " << score << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}

	setCounterClockDir();
	//cout << "COUNTER CLOCK DIR" << "\n";
	

	for (int i = 1; i <= m; i++) {
		//cout << "TURN : " << i << "\n";
		int d, p;
		cin >> d >> p;

		//cout << "ATTACK" << "\n";
		attack(d, p);
		//print();

		//cout << "GRID TO VEC" << "\n";
		gridToVec();
		//print();

		//cout << "REMOVE" << "\n";
		remove();
		//print();

		//cout << "REARRANGE" << "\n";
		rearrange();
		//print();

		//cout << "VEC TO GRID" << "\n";
		vecToGrid();
		//print();
	}

	cout << score << "\n";
	return 0;
}