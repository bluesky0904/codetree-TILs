#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define GRID_SIZE 4
#define DIR_NUM 8

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,-1,-1,-1,0,1,1,1};

int m, t;
int r, c;
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

// 몬스터 복제
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

// 몬스터 이동
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
					for (int cnt = 1; cnt <= 7 && !moved; cnt++) {
						int next_dir = (move_dir + cnt) % 8;
						nx = x + dx[next_dir];
						ny = y + dy[next_dir];
						if (InRange(nx, ny) && (make_pair(nx, ny) != pacman) && ghost[nx][ny] == 0) {
							next_monster[nx][ny].push_back(next_dir);
							moved = true;
							break;
						}
					}
					if(!moved) next_monster[x][y].push_back(move_dir);
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

// 팩맨이 이동할 때, 각 방향으로 이동했을 때, 몬스터의 수를 세어서 최대값을 찾는다.
int CountMonster() {
	bool visited[GRID_SIZE][GRID_SIZE] = {false,};
	int cnt = 0;
	int cx = pacman.first, cy = pacman.second;
	for (int dir = 0; dir < (int)temp_pac_dir.size(); dir++) {
		cx += dx[temp_pac_dir[dir]];
		cy += dy[temp_pac_dir[dir]];
		if (!InRange(cx, cy)) return -1;
		if (visited[cx][cy]) continue;
		else {
			visited[cx][cy] = true;
			cnt += (int)monster[cx][cy].size();
		}
	}
	return cnt;
}

// 팩맨이 이동할 수 있는 모든 경우의 수를 찾는다.
void FindMaxRoute(int idx) {
	if (idx == 3) {
		int tmp = CountMonster();
		if (max_cnt < tmp) {
			max_cnt = tmp;
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

// 팩맨 이동
void MovePacman() {
	pac_dir.clear();
	max_cnt = -1;
	FindMaxRoute(0);
	int cx = pacman.first, cy = pacman.second;
	for (int dir = 0; dir < (int)pac_dir.size(); dir++) {
		cx += dx[pac_dir[dir]];
		cy += dy[pac_dir[dir]];
		if ((int)monster[cx][cy].size() > 0) {
			monster[cx][cy].clear();
			ghost[cx][cy] = 3;
		}
	}
	pacman = make_pair(cx, cy);
}

// 시체 제거
void RemoveGhost() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if(ghost[x][y] > 0) ghost[x][y]--;
		}
	}
}

// 알 부화
void CompleteReplicate() {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			for (int i = 0; i < (int)egg[x][y].size(); i++) {
				monster[x][y].push_back(egg[x][y][i]);
			}
		}
	}
}

// 디버깅용 출력
void Print() {
	cout << "Pacman: " << pacman.first << " " << pacman.second << "\n";
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if ((int)monster[x][y].size()) {
				cout << "Monster: " << x << " " << y << "\n";
				for (int i = 0; i < (int)monster[x][y].size(); i++) {
					cout << monster[x][y][i] << " ";
				}

				cout << "\n";
			}
		}
	}
	cout << "Ghost\n";
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			cout << ghost[x][y] << " ";
		}
		cout << "\n";
	}
	cout << "Egg\n";
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if ((int)egg[x][y].size()) {
				cout << "Egg: " << x << " " << y << "\n";
				for (int i = 0; i < (int)egg[x][y].size(); i++) {
					cout << egg[x][y][i] << " ";
				}
			}
		}
		cout << "\n";
	}
	cout << "--------------------\n";
}

void Simulate() {
	// 복제 시도
	TryReplicate();
	// 몬스터 이동
	MoveAllMonster();
	// 팩맨 이동
	MovePacman();
	// 시체 제거
	RemoveGhost();
	// 알 부화
	CompleteReplicate();

}

int main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> m >> t;
	cin >> r >> c;
	pacman = make_pair(r - 1, c - 1);
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