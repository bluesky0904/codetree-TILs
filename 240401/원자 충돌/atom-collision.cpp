#include <iostream>
#include <vector>
#include <iomanip>
#include <tuple>
using namespace std;

#define MAX_N 50
#define DIR_NUM 8

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,1,1,1,0,-1,-1,-1};

// n : 격자의 크기, m : 원자 수, k : tlrks
// 격자의 모든 행과 열은 끝이 연결되어 있음
// 각 원자는 질량, 방향, 속력, 초기 위치

struct Atom {
	int mass, dis, dir;
};

int n, m, k;
vector<Atom> grid[MAX_N][MAX_N];
vector<Atom> next_grid[MAX_N][MAX_N];

int GetMassSum() {
	int sum = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				sum += grid[x][y][i].mass;
			}
		}
	}

	return sum;
}

// 1. 모든 원자는 1초마다 자신의 방향으로 자신의 속력만큼 이동
// 2. 하나의 칸에 2개 이상의 원자가 있는 경우 합성
// 2-1 각각의 질량과 속력을 모두 합한 하나의 원자로 합쳐짐
// 2-2 합쳐진 원자는 4개의 원자로 나눠짐
// 2-3 나눠진 원자들은 모두 해당 칸에 위치
// 질량은 합쳐진 원자의 질량에 5를 나눈 값
// 속력은 합쳐진 원자의 속력에 합쳐진 원자의 개수를 나눈 값
// 방향은 합쳐지는 원자의 방향이 모두 상하좌우 중 하나 또는 대각선 중에 하나 -> 각각 상하좌우
// 아니면 대각선 네 방향의 값
// 2-4 질량이 0인 원소는 소멸
// 3. 이동 과정 중에 원자가 만나는 경우는 합성으로 고려하지 않는다

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> GetNextPos(int x, int y, Atom atom) {
	int nx = x, ny = y;
	int dis, dir;
	dis = atom.dis;
	dir = atom.dir;
	for (int cnt = 0; cnt < dis; cnt++) {
		nx += dx[dir];
		if (!(0 <= nx && nx < n)) nx = (nx + n) % n;
		ny += dy[dir];
		if (!(0 <= ny && ny < n)) ny = (ny + n) % n;
	}
	return make_pair(nx, ny);
}

void MoveAllAtom() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y].clear();
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				int nx, ny;
				tie(nx, ny) = GetNextPos(x, y, grid[x][y][i]);
				next_grid[nx][ny].push_back(grid[x][y][i]);
			}
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void CombineAtom() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y].clear();
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if ((int)grid[x][y].size() >= 2) {
				int mass_sum = 0, dis_sum = 0;
				int type = grid[x][y][0].dir % 2;
				bool is_same = true;
				for (int i = 1; i < (int)grid[x][y].size(); i++) {
					if (grid[x][y][i].dir % 2 != type) {
						is_same = false;
						break;
					}
				}
				for (int i = 0; i < (int)grid[x][y].size(); i++) {
					mass_sum += grid[x][y][i].mass;
					dis_sum += grid[x][y][i].dis;
				}
				mass_sum /= 5;
				dis_sum /= (int)grid[x][y].size();
				if (mass_sum != 0) {
					if (is_same) {
						for (int i = 0; i < DIR_NUM; i += 2) {
							/*
							int nx = x + dx[i], ny = y + dy[i];
							if (!(0 <= nx && nx < n)) nx = (nx + n) % n;
							if (!(0 <= ny && ny < n)) ny = (ny + n) % n;
							*/
							next_grid[x][y].push_back({ mass_sum, dis_sum, i });
						}
					}
					else {
						for (int i = 1; i < DIR_NUM; i += 2) {
							/*
							int nx = x + dx[i], ny = y + dy[i];
							if (!(0 <= nx && nx < n)) nx = (nx + n) % n;
							if (!(0 <= ny && ny < n)) ny = (ny + n) % n;
							*/
							next_grid[x][y].push_back({ mass_sum, dis_sum, i});
						}
					}
				}
			}
			else {
				for (int i = 0; i < (int)grid[x][y].size(); i++) {
					next_grid[x][y].push_back(grid[x][y][i]);
				}
			}
		}
	}


	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void Print() {
	int width = 3;
    for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cout << right << setw(width) << grid[x][y].size() << " ";
		}
		cout << "\n";
	}
	cout << "----------------------------\n";
}

void Simulate() {
	MoveAllAtom();
	//Print();
	CombineAtom();
	//Print();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;

	for (int i = 0; i < m; i++) {
		int x, y, mass, dis, dir;
		cin >> x >> y >> mass >> dis >> dir;
		grid[x - 1][y - 1].push_back({mass, dis, dir});
	}

	while (k--) {
		Simulate();
	}

	cout << GetMassSum() << "\n";
	return 0;
}