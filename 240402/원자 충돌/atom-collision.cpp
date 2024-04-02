#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 50
#define DIR_NUM 8

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,1,1,1,0,-1,-1,-1};

// n : 격자의 크기, m : 원자의 개수, k : 턴 수

struct Atom {
	int mass, dis, dir;
};

int n, m, k;
vector<Atom> grid[MAX_N][MAX_N];
vector<Atom> next_grid[MAX_N][MAX_N];

pair<int, int> GetNextPos(int x, int y, Atom atom) {
	int dis = atom.dis, dir = atom.dir;
	int nx = x, ny = y;
	for (int cnt = 0; cnt < dis; cnt++) {
		nx += dx[dir];
		if (!(0 <= nx && nx < n)) nx = (nx + n) % n;
		ny += dy[dir];
		if(!(0 <= ny && ny < n)) ny = (ny + n) % n;
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
				int mass_sum = 0;
				int dis_sum = 0;
				int type = grid[x][y][0].dir % 2;
				bool is_same_type = true;
				for (int i = 0; i < (int)grid[x][y].size(); i++) {
					if (grid[x][y][i].dir % 2 != type) {
						is_same_type = false;
						break;
					}
				}
				for (int i = 0; i < (int)grid[x][y].size(); i++) {
					mass_sum += grid[x][y][i].mass;
					dis_sum += grid[x][y][i].dis;
				}
				mass_sum /= 5;
				dis_sum /= (int)grid[x][y].size();

				if (mass_sum > 0) {
					if (is_same_type) {
						for (int dir = 0; dir < DIR_NUM; dir += 2) {
							next_grid[x][y].push_back({ mass_sum, dis_sum, dir });
						}
					}
					else {
						for (int dir = 1; dir < DIR_NUM; dir += 2) {
							next_grid[x][y].push_back({ mass_sum, dis_sum, dir });
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

void Simulate() {
	MoveAllAtom();
	CombineAtom();
}

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

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int x, y, mass, dis, dir;
		cin >> x >> y >> mass >> dis >> dir;
		grid[x- 1][y - 1].push_back({mass, dis, dir});
	}

	while (k--) Simulate();

	cout << GetMassSum() << "\n";
	return 0;
}