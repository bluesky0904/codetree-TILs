#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define GRID_SIZE 4
#define DIR_NUM 8

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,-1,-1,-1,0,1,1,1};

int m, t;
pair<int, int> pacman;
vector<int> monster[GRID_SIZE][GRID_SIZE];
vector<int> next_monster[GRID_SIZE][GRID_SIZE];
vector<int> egg[GRID_SIZE][GRID_SIZE];
int ghost[GRID_SIZE][GRID_SIZE];

int max_cnt = -1;
vector<int> temp_pac_dir;
vector<int> pac_dir;

bool InRange(int x, int y) {
	return 0 <= x && x < GRID_SIZE && 0 <= y && y < GRID_SIZE;
}

void InitEgg() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			egg[x][y].clear();
		}
	}
}

void TryReplicate() {
	InitEgg();
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			for (int i = 0; i < (int)monster[x][y].size(); i++) {
				egg[x][y].push_back(monster[x][y][i]);
			}
		}
	}
}

void MoveAllMonster() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			next_monster[x][y].clear();
		}
	}

	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			for (int i = 0; i < (int)monster[x][y].size(); i++) {
				int move_dir = monster[x][y][i];
				int nx = x + dx[move_dir];
				int ny = y + dy[move_dir];
				if (!InRange(nx, ny) || make_pair(nx, ny) == pacman || ghost[nx][ny] > 0) {
					bool moved = false;
					for (int cnt = 1; cnt <= 7; cnt++) {
						move_dir = (move_dir + cnt) % 8;
						nx = x + dx[move_dir];
						ny = y + dy[move_dir];
						if (InRange(nx, ny) && make_pair(nx, ny) != pacman && ghost[nx][ny] == 0) {
							next_monster[nx][ny].push_back(move_dir);
							moved = true;
							break;
						}
					}
					if(!moved) next_monster[x][y].push_back(monster[x][y][i]);
				}
				else {
					next_monster[nx][ny].push_back(monster[x][y][i]);
				}			
			}
		}
	}

	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			monster[x][y] = next_monster[x][y];
		}
	}
}

int CountMonster() {
	int cnt = 0;
	int cx = pacman.first, cy = pacman.second;
	for (int dir = 0; dir < (int)temp_pac_dir.size(); dir++) {
		cx += dx[temp_pac_dir[dir]];
		cy += dy[temp_pac_dir[dir]];
		if (!InRange(cx, cy)) return -1;
		cnt += (int)monster[cx][cy].size();
	}
	return cnt;
}

void FindMaxRoute(int idx) {
	if (idx == 3) {
		if (max_cnt < CountMonster()) {
			max_cnt = CountMonster();
			pac_dir = temp_pac_dir;
		}
		return;
	}

	for (int dir = 0; dir < DIR_NUM; dir += 2) {
		temp_pac_dir.push_back(dir);
		FindMaxRoute(idx + 1);
		temp_pac_dir.pop_back();
	}
}

void MovePacman() {
	pac_dir.clear();
	FindMaxRoute(0);
	int cx = pacman.first, cy = pacman.second;
	for (int dir = 0; dir < (int)pac_dir.size(); dir++) {
		cx += dx[pac_dir[dir]];
		cy += dy[pac_dir[dir]];
		if ((int)monster[cx][cy].size() > 0) {
			monster[cx][cy].clear();
			ghost[cx][cy] = 2;
		}
	}
	pacman = make_pair(cx, cy);
}

void RemoveGhost() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if(ghost[x][y] > 0) ghost[x][y]--;
		}
	}
}

void CompleteReplicate() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			for (int i = 0; i < (int)egg[x][y].size(); i++) {
				if(ghost[x][y] == 0) monster[x][y].push_back(egg[x][y][i]);
			}
		}
	}
}

void Simulate() {
	TryReplicate();
	MoveAllMonster();
	MovePacman();
	RemoveGhost();
	CompleteReplicate();
}

int main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> m >> t;
	cin >> pacman.first >> pacman.second;
	for (int i = 0; i < m; i++) {
		int r, c, d;
		cin >> r >> c >> d;
		monster[r - 1][c - 1].push_back(d - 1);
	}

	while (t--) Simulate();

	int ans = 0;
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			ans += (int)monster[x][y].size();
		}
	}
	cout << ans << "\n";
	return 0;
}