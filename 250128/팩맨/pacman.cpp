/*
격자 : 4 x 4. 한 격자에 여러 객체가 존재할 수 있음
몬스터 : m개. 위치, 방향
		 각각의 몬스터는 상하좌우, 대각선 방향 중 하나를 가짐
알 : 부화. 위치. 방향
몬스터 시체

팩맨 : 위치

팩맨 게임은 턴 단위로 진행
1. 몬스터 복제 시도
몬스터는 현재의 위치에서 자신과 같은 방향을 가진 몬스터를 복제
이때 복제된 몬스터는 아직은 부화되지 않은 상태로 움직이지 못함

2. 몬스터 이동
몬스터는 현재 자신이 가진 방향대로 한 칸 이동
이때 움직이려는 칸에 몬스터 시체가 있음 || 팩맨이 있음 || 격자를 벗어남 -> 반시계 방향으로 45도 회전
가능할 때까지 반시계 방향으로 45도씩 회전하며 해당 방향으로 갈 수 있는지를 확인 
모두 움직일 수 없다면 해당 몬스터는 움직이지 않음

3. 팩맨 이동
팩맨의 이동은 총 3칸을 이동하게 되는데, 각 이동마다 상하좌우의 선택지를 가짐
총 4가지의 방향을 3칸 이동하기 때문에 총 64개의 이동 방법이 존재
이 중 몬스터를 가장 많이 먹을 수 있는 방향으로 이동
가장 많이 먹을 수 있는 방향이 여러개라면 상-좌-하-우 의 우선순위를 가짐
(상상상-상상좌-상상하-상상우-상좌상...)
이동하는 과정에 격자 바깥을 나가는 경우는 고려하지 않음

이동할 때 이동하는 칸에 있는 몬스터는 모두 먹어치운 뒤, 그 자리에 몬스터의 시체를 남김

팩맨은 알은 먹지 않으며, 움직이기 전에 함께 있었던 몬스터도 먹지 않음
즉 이동하는 과정에 있는 몬스터만 먹음

4. 몬스터 시체 소멸
몬스터의 시체는 총 2턴 동안만 유지.
즉 시체가 생기고 나면 시체가 소멸되기 까지는 총 두 턴을 필요로 함

5. 몬스터 복제 완성
알 형태였던 몬스터가 부화
처음 복제가 된 몬스터의 방향을 지닌 채로 깨어남

모든 턴이 진행되고 난 뒤 살아 남은 몬스터의 마리 수를 출력
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define GRID_SIZE 4
#define TURN_CNT 2
#define DIR_NUM 8

int m, t;
int pac_x, pac_y;

vector<int> grid[GRID_SIZE + 1][GRID_SIZE + 1];
vector<int> next_grid[GRID_SIZE + 1][GRID_SIZE + 1];
vector<int> egg[GRID_SIZE + 1][GRID_SIZE + 1];
int ghost[GRID_SIZE + 1][GRID_SIZE + 1];

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,-1,-1,-1,0,1,1,1};

void print() {
	int cnt = 0;
	cout << "PAC_POS : " << pac_x << " " << pac_y << "\n";
	cout << "GRID" << "\n";
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			cnt += grid[x][y].size();
			cout << " { ";
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				cout << grid[x][y][i] << " ";
			}
			cout << "} ";
		}
		cout << "\n";
	}
	cout << "EGG" << "\n";
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			cout << " { ";
			for (int i = 0; i < (int)egg[x][y].size(); i++) {
				cout << egg[x][y][i] << " ";
			}
			cout << "} ";
		}
		cout << "\n";
	}
	cout << "GHOST" << "\n";
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			cout << ghost[x][y] << " ";
		}
		cout << "\n";
	}
	cout << "MONSTER_CNT : " << cnt << "\n";
}

/*
1. 몬스터 복제 시도
몬스터는 현재의 위치에서 자신과 같은 방향을 가진 몬스터를 복제
이때 복제된 몬스터는 아직은 부화되지 않은 상태로 움직이지 못함
*/
void putEgg() {
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				egg[x][y].push_back(grid[x][y][i]);
			}
		}
	}
}

/*
2. 몬스터 이동
몬스터는 현재 자신이 가진 방향대로 한 칸 이동
이때 움직이려는 칸에 몬스터 시체가 있음 || 팩맨이 있음 || 격자를 벗어남 -> 반시계 방향으로 45도 회전
가능할 때까지 반시계 방향으로 45도씩 회전하며 해당 방향으로 갈 수 있는지를 확인
모두 움직일 수 없다면 해당 몬스터는 움직이지 않음
*/

bool inRange(int x, int y) {
	return (1 <= x && x <= GRID_SIZE && 1 <= y && y <= GRID_SIZE);
}

tuple<int, int, int> getNextPos(int x, int y, int d, int turn) {
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nd = (d + dir) % DIR_NUM;
		int nx = x + dx[nd], ny = y + dy[nd];
		if (inRange(nx, ny) && ghost[nx][ny] == 0 && !(nx == pac_x && ny == pac_y)) {
			return make_tuple(nx, ny, nd);
		}
	}
	return make_tuple(x, y, d);
}

void moveAllMonsters(int turn) {
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			next_grid[x][y].clear();
		}
	}

	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			if (grid[x][y].empty()) continue;

			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				int nx, ny, nd;
				tie(nx, ny, nd) = getNextPos(x, y, grid[x][y][i], turn);
				next_grid[nx][ny].push_back(nd);
			}
		}
	}

	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			grid[x][y].clear();
		}
	}

	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			for (int i = 0; i < (int)next_grid[x][y].size(); i++) {
				grid[x][y].push_back(next_grid[x][y][i]);
			}
		}
	}
}
/*
3. 팩맨 이동
팩맨의 이동은 총 3칸을 이동하게 되는데, 각 이동마다 상하좌우의 선택지를 가짐
총 4가지의 방향을 3칸 이동하기 때문에 총 64개의 이동 방법이 존재
이 중 몬스터를 가장 많이 먹을 수 있는 방향으로 이동
가장 많이 먹을 수 있는 방향이 여러개라면 상 - 좌 - 하 - 우 의 우선순위를 가짐
(상상상 - 상상좌 - 상상하 - 상상우 - 상좌상...)
이동하는 과정에 격자 바깥을 나가는 경우는 고려하지 않음

이동할 때 이동하는 칸에 있는 몬스터는 모두 먹어치운 뒤, 그 자리에 몬스터의 시체를 남김

팩맨은 알은 먹지 않으며, 움직이기 전에 함께 있었던 몬스터도 먹지 않음
즉 이동하는 과정에 있는 몬스터만 먹음
*/

int max_cnt;
vector<int> dir_v;
vector<int> max_v;
bool visited[GRID_SIZE + 1][GRID_SIZE + 1];

void findMaxRoute(int monster_cnt, int cx, int cy) {
	if ((int)dir_v.size() == 3) {
		if (monster_cnt > max_cnt ||
			(monster_cnt == max_cnt && dir_v < max_v)) { // 우선순위 비교
			max_cnt = monster_cnt;
			max_v = dir_v;
		}
		return;
	}

	for (int dir = 0; dir < DIR_NUM; dir += 2) { // 상좌하우만 고려
		int nx = cx + dx[dir];
		int ny = cy + dy[dir];

		if (inRange(nx, ny)) {
			bool visited_before = visited[nx][ny];
			dir_v.push_back(dir);

			if (!visited_before) {
				visited[nx][ny] = true;
				findMaxRoute(monster_cnt + grid[nx][ny].size(), nx, ny);
				visited[nx][ny] = false;
			}
			else {
				findMaxRoute(monster_cnt, nx, ny);
			}

			dir_v.pop_back();
		}
	}
}


void movePacman(int turn) {

	dir_v.clear();
	max_cnt = -1;
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			visited[x][y] = false;
		}
	}
	findMaxRoute(0, pac_x, pac_y);
	//cout << "MAX_V : " << max_v[0] << " " << max_v[1] << " " << max_v[2] << "\n";

	for (int dir = 0; dir < (int)max_v.size(); dir++) {
		pac_x += dx[max_v[dir]], pac_y += dy[max_v[dir]];
		if (!grid[pac_x][pac_y].empty()) {
			grid[pac_x][pac_y].clear();
			ghost[pac_x][pac_y] = TURN_CNT + 1;
		}
	}
}

void decayMonsters() {
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			if(ghost[x][y] > 0 ) ghost[x][y]--;
		}
	}
}

void reproduceMonsters() {
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			for (int i = 0; i < (int)egg[x][y].size(); i++) {
				grid[x][y].push_back(egg[x][y][i]);
			}
			egg[x][y].clear();
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> m >> t;
	cin >> pac_x >> pac_y;

	for (int i = 1; i <= m; i++) {
		int r, c, d; cin >> r >> c >> d;
		grid[r][c].push_back(d - 1);
	}
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			ghost[x][y] = 0;
		}
	}

	//print();
	for (int turn = 1; turn <= t; turn++) {
		//cout << "TURN " << turn << "\n";

		//cout << "PUTEGG" << "\n";
		putEgg();
		//print();

		//cout << "MOVEALLMONSTERS" << "\n";
		moveAllMonsters(turn);
		//print();

		//cout << "MOVEPACMAN" << "\n";
		movePacman(turn);
		//print();

		//cout << "DECAY" << "\n";
		decayMonsters();
		//print();

		//cout << "REPRODUCEMONSTERS" << "\n";
		reproduceMonsters();
		//print();
	}

	// 남은 몬스터 수 출력
	//모든 턴이 진행되고 난 뒤 살아 남은 몬스터의 마리 수를 출력

	int ans = 0;
	for (int x = 1; x <= GRID_SIZE; x++) {
		for (int y = 1; y <= GRID_SIZE; y++) {
			if (!grid[x][y].empty()) ans += (int)grid[x][y].size();
		}
	}

	cout << ans << "\n";
	return 0;
}