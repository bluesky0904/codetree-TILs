#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 50
#define DIR_NUM 8

struct Atom {
	int mass, dis, dir;
};

int n, m, k;
vector<Atom> grid[MAX_N][MAX_N];
vector<Atom> next_grid[MAX_N][MAX_N];

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,1,1,1,0,-1,-1,-1};

pair<int, int> GetNextPos(int x, int y, Atom atom) {
	int dis = atom.dis, dir = atom.dir;

	int nx = x + dis * dx[dir];
	while (nx < 0) {
		nx += n;
	}
	if(nx >= n) nx %= n;

	int ny = y + dis * dy[dir];
	while (ny < 0) {
		ny += n;
	}
	if(ny >= n) ny %= n;

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
			if ((int)grid[x][y].size() >= 2) {
				int total_mass = 0, total_dis = 0, total_dir = 0, cnt = (int)grid[x][y].size();
				for (int i = 0; i < (int)grid[x][y].size(); i++) {
					total_mass += grid[x][y][i].mass;
					total_dis += grid[x][y][i].dis;
					if (i != cnt - 1 && grid[x][y][i].dir % 2 != grid[x][y][i + 1].dir % 2) {
						total_dir = 1;
					}
				}
				grid[x][y].clear();
				if (total_mass / 5 == 0) continue;
				for (int i = total_dir; i < DIR_NUM; i += 2) {
					grid[x][y].push_back({ total_mass / 5, total_dis / cnt, i });
				}
			}
		}
	}
}

int GetTotalMass() {
	int ans = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int i = 0; i < (int)grid[x][y].size(); i++) {
				ans += grid[x][y][i].mass;
			}
		}
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int x, y, mass, dis, dir;
		cin >> x >> y >> mass >> dis >> dir;
		grid[x-1][y-1].push_back({ mass, dis, dir });
	}

	for (int turn = 0; turn < k; turn++) {
		MoveAllAtom();
		CombineAtom();
	}

	cout << GetTotalMass() << '\n';
	return 0;
}