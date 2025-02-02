/*
나선형 미로 : n x n int grid[][]
몬스터 : 1번, 2번, 3번 vector<int> monsters, vector<int> next_monsters
플레이어 : 격자의 중심에 위치
점수 score

1. 플레이어는 상하좌우 방향 중 주어진 공격 칸 수만큼 몬스터를 공격하여 없앨 수 있음

2. 비어있는 공간만큼 몬스터는 앞으로 이동하여 빈 공간을 채움

3. 이때 몬스터의 종류가 4번 이상 반복하여 나오면 해당 몬스터 또한 삭제됨
해당 몬스터들은 동시에 사라짐
삭제된 이후에는 몬스터들을 앞으로 당겨주고, 4번 이상 나오는 몬스터가 있을 경우 또 삭제를 해줌
4번 이상 나오는 몬스터가 없을 때까지 반복


4. 삭제가 끝난 다음에는 몬스터를 차례대로 나열했을 때 같은 숫자끼리 짝을 지어줌
이후 각각의 짝을 (총 개수, 숫자의 개수)로 바꾸어서 다시 미로 속에 집어넣음
만약 새로 생긴 배열이 원래 격자의 범위를 넘는다면 나머지 배열은 무시

해당 과정이 끝나면 한 라운드가 끝남
1과 3 과정에서 삭제되는 몬스터의 번호는 점수에 합쳐짐
score += (몬스터의 번호 x 삭제된 수)

각 라운드별로 공격 방향과 공격하는 칸 수가 주어질 때 모든 라운드가 끝난 후 플레이어가 얻게되는 점수는 몇 점인지 출력
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 25
#define DIR_NUM 4
#define MONSTER_NUM 3

int n, m;
int grid[MAX_N + 1][MAX_N + 1];
vector<int> monsters;
vector<int> next_monsters;
int score;
int counter_clock_dir[MAX_N + 1][MAX_N + 1];

int dx[DIR_NUM] = {0,1,0,-1};
int dy[DIR_NUM] = {1,0,-1,0};

void setCounterClock() {
	int cx = (n + 1) / 2, cy = ((n + 1) / 2), cd = 2;
	int stride = 1;
	while (!(cx == 1 && cy == 1)) {
		for (int cnt = 1; cnt <= 2; cnt++) {
			for (int dist = 1; dist <= stride; dist++) {
				counter_clock_dir[cx][cy] = cd;
				cx += dx[cd], cy += dy[cd];
				if (cx == 1 && cy == 1) return;
			}
			cd = (cd + 3) % DIR_NUM;
		}
		stride++;
	}
}

bool inRange(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

void attackMonster(int d, int p) {
	int tmp[MONSTER_NUM + 1] = { 0, };

	int cx = (n + 1) / 2, cy = (n + 1) / 2, cd = d;
	for (int dist = 1; dist <= p; dist++) {
		int nx = cx + dx[cd] * dist, ny = cy + dy[cd] * dist;
		if (inRange(nx, ny) && grid[nx][ny] > 0) {
			tmp[grid[nx][ny]]++;
			grid[nx][ny] = 0;
		}
	}

	for (int i = 1; i <= MONSTER_NUM; i++) {
		score += (i * tmp[i]);
	}
}

void gridToVec() {
	monsters.clear();

	int cx = (n + 1) / 2, cy = ((n + 1) / 2) - 1, cd = counter_clock_dir[cx][cy];
	while (!(cx == 1 && cy == 1)) {
		if(grid[cx][cy] > 0) monsters.push_back(grid[cx][cy]);
		cd = counter_clock_dir[cx][cy];
		cx += dx[cd], cy += dy[cd];

		if (cx == 1 && cy == 1) break;
	}
}

void remove() {
	int tmp[MONSTER_NUM + 1] = { 0, };
	
	while(1){
		int cnt = 1;
		int size = (int)monsters.size();
		bool is_over = true;

		for (int i = 0; i < size - 1; i++) {
			if (monsters[i] == monsters[i + 1]) {
				cnt++;
				if (i == size - 2 && cnt >= 4) {
					is_over = false;
					tmp[monsters[i]] += cnt;
					for (int j = 0; j < cnt; j++) {
						monsters[i + 1 - j] = 0;
					}
				}
			}
			else {
				if (cnt >= 4) {
					is_over = false;
					tmp[monsters[i]] += cnt;
					for (int j = 0; j < cnt; j++) {
						monsters[i - j] = 0;
					}
				}
				cnt = 1;
			}
		}

		if (is_over) break;
		next_monsters.clear();
		for (int i = 0; i < (int)monsters.size(); i++) {
			if(monsters[i] > 0) next_monsters.push_back(monsters[i]);
		}
		monsters.clear();
		for (int i = 0; i < (int)next_monsters.size(); i++) {
			monsters.push_back(next_monsters[i]);
		}
	}

	for (int i = 1; i <= MONSTER_NUM; i++) {
		score += (i * tmp[i]);
	}
}

void rearrange() {
	next_monsters.clear();

	int cnt = 1;
	int size = (int)monsters.size();
	for (int i = 0; i < size - 1; i++) {
		if (monsters[i] == monsters[i + 1]) {
			cnt++;
			if (i == size - 2) {
				next_monsters.push_back(cnt);
				if ((int)next_monsters.size() == ((n * n) - 1)) break;
				next_monsters.push_back(monsters[i]);
				if ((int)next_monsters.size() == ((n * n) - 1)) break;
			}
		}
		else {
			next_monsters.push_back(cnt);
			if ((int)next_monsters.size() == ((n * n) - 1)) break;
			next_monsters.push_back(monsters[i]);
			if ((int)next_monsters.size() == ((n * n) - 1)) break;

			if (i == size - 2) {
				next_monsters.push_back(1);
				if ((int)next_monsters.size() == ((n * n) - 1)) break;
				next_monsters.push_back(monsters[i + 1]);
				if ((int)next_monsters.size() == ((n * n) - 1)) break;
			}
			cnt = 1;
		}
	}

	monsters.clear();
	for (int i = 0; i < (int)next_monsters.size(); i++) {
		monsters.push_back(next_monsters[i]);
	}
}

void vecToGrid() {
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {
			grid[x][y] = 0;
		}
	}

	int cx = (n + 1) / 2, cy = ((n + 1) / 2) - 1, cd = counter_clock_dir[cx][cy];
	for(int i = 0; i < (int)monsters.size(); i++) {
		grid[cx][cy] = monsters[i];
		cd = counter_clock_dir[cx][cy];
		cx += dx[cd], cy += dy[cd];

		if (cx == 1 && cy == 1) {
			if(i + 1 < monsters.size() )grid[cx][cy] = monsters[i + 1];
			break;
		}
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
	freopen("input.txt", "r", stdin);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}

	score = 0;
	setCounterClock();

	for (int i = 1; i <= m; i++) {
		int d, p; cin >> d >> p;

		attackMonster(d, p);
		//print();

		gridToVec();
		//print();

		remove();
		//print();

		rearrange();
		//print();

		vecToGrid();
		//print();
	}
    cout << score << "\n";
    return 0;
}