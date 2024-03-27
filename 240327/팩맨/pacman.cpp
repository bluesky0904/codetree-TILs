#include <iostream>
#include <vector>
using namespace std;

#define GRID_SIZE 4
#define DIR_NUM 8

int m, t;
int r, c;
pair<int, int> pacman;
vector<int> monster[GRID_SIZE][GRID_SIZE];
vector<int> next_monster[GRID_SIZE][GRID_SIZE];
int ghost[GRID_SIZE][GRID_SIZE];
vector<int> egg[GRID_SIZE][GRID_SIZE];

int max_cnt;
vector<int> pacman_dir;
vector<int> temp_pacman_dir;

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,-1,-1,-1,0,1,1,1};

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

bool InRange(int x, int y) {
	return 0 <= x && x < GRID_SIZE && 0 <= y && y < GRID_SIZE;
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
				if (!InRange(nx, ny) || make_pair(nx, ny) == pacman || ghost[nx][ny] != 0) {
					bool moved = false;
					for (int cnt = 1; cnt <= 7; cnt++) {
						int next_dir = (move_dir + cnt) % 8;
						nx = x + dx[next_dir];
						ny = y + dy[next_dir];
						if (InRange(nx, ny) && make_pair(nx, ny) != pacman && ghost[nx][ny] == 0) {
							next_monster[nx][ny].push_back(next_dir);
							moved = true;
							break;
						}
					}
					if(!moved) next_monster[x][y].push_back(move_dir);
				}
				else next_monster[nx][ny].push_back(move_dir);
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
	bool visited[GRID_SIZE][GRID_SIZE] = {false,};
	int cnt = 0;
	int cx = pacman.first, cy = pacman.second;
	for (int dir = 0; dir < (int)temp_pacman_dir.size(); dir++) {
		cx += dx[temp_pacman_dir[dir]];
		cy += dy[temp_pacman_dir[dir]];
		if (!InRange(cx, cy)) return -1;
		if (visited[cx][cy]) continue;
		else {
			visited[cx][cy] = true;
			if (monster[cx][cy].size() > 0) cnt += monster[cx][cy].size();
		}
	}
	return cnt;
}

void FindMaxRoute(int idx) {
	if (idx == 3) {
		int tmp = CountMonster();
		if (max_cnt < CountMonster()) {
			max_cnt = CountMonster();
			pacman_dir = temp_pacman_dir;
		}
		return;
	}

	for (int dir = 0; dir < DIR_NUM; dir += 2) {
		temp_pacman_dir.push_back(dir);
		FindMaxRoute(idx + 1);
		temp_pacman_dir.pop_back();
	}
}

void MovePacman() {
	int cx = pacman.first, cy = pacman.second;
	max_cnt = -1;
	FindMaxRoute(0);
	for (int dir = 0; dir < (int)pacman_dir.size(); dir++) {
		cx += dx[pacman_dir[dir]];
		cy += dy[pacman_dir[dir]];
		if ((int)monster[cx][cy].size() > 0) {
			monster[cx][cy].clear();
			ghost[cx][cy] = 3;
		}
	}
	pacman = {cx, cy};
}

void RemoveGhost() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if (ghost[x][y] > 0) ghost[x][y]--;
		}
	}
}

void CompleteReplicate() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			for (int i = 0; i < (int)egg[x][y].size(); i++) {
				monster[x][y].push_back(egg[x][y][i]);
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
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> m >> t;
	cin >> r >> c;
	pacman = {r - 1, c - 1};
	for (int i = 0; i < m; i++) {
		int r, c, d;
		cin >> r >> c >> d;
		monster[r - 1][c - 1].push_back(d - 1);
	}

	while (t--) Simulate();

	int ans = 0;
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if(monster[x][y].size() > 0) ans += monster[x][y].size();
		}
	}
	cout << ans << "\n";
	return 0;
}