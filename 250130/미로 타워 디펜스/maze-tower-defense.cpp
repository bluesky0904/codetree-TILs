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
					if (cnt >= 4) {
						tmp[monsters[i]] += cnt;
						for (int j = 0; j < cnt; j++) {
							monsters[i - j] = 0;
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

		attack(d, p);
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