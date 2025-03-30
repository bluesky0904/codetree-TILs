#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 29;
const int MAXID = 1000;

int n;
int grid[MAXN + 10][MAXN + 10];
int next_grid[MAXN + 10][MAXN + 10];
int r_grid[MAXN + 10][MAXN + 10];
int cluster_grid[MAXN + 10][MAXN + 10];
bool visited[MAXN + 10][MAXN + 10];

int ans;
int id;
int component_num[MAXID + 10];
int component_cnt[MAXID + 10];
pair<int, int> start_pos[MAXID + 10];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void print() {
	cout << "grid" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void rotateGrid(int rot) {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			r_grid[x][y] = grid[x][y];
		}
	}

	while (rot--) {
		// 가로 중앙선
		for (int j = 0; j < n; j++) {
			next_grid[n - j - 1][n / 2] = r_grid[n / 2][j];
		}

		// 세로 중앙선
		for (int i = 0; i < n; i++) {
			next_grid[n / 2][i] = r_grid[i][n / 2];
		}

		// 좌측 상단
		for (int x = 0; x < n / 2; x++) {
			for (int y = 0; y < n / 2; y++) {
				next_grid[y][n / 2 - x - 1] = r_grid[x][y];
			}
		}

		// 우측 상단
		for (int x = 0; x < n / 2; x++) {
			for (int y = n / 2 + 1; y < n; y++) {
				int ox = x;
				int oy = y - (n / 2 + 1);
				int rx = oy;
				int ry = n / 2 - ox - 1;
				next_grid[rx][ry + (n / 2 + 1)] = r_grid[x][y];
			}
		}

		// 좌측 하단
		for (int x = n / 2 + 1; x < n; x++) {
			for (int y = 0; y < n / 2; y++) {
				int ox = x - (n / 2 + 1);
				int oy = y;
				int rx = oy;
				int ry = n / 2 - ox - 1;
				next_grid[rx + (n / 2 + 1)][ry] = r_grid[x][y];
			}
		}

		// 우측 하단
		for (int x = n / 2 + 1; x < n; x++) {
			for (int y = n / 2 + 1; y < n; y++) {
				int ox = x - (n / 2 + 1);
				int oy = y - (n / 2 + 1);
				int rx = oy;
				int ry = n / 2 - ox - 1;
				next_grid[rx + (n / 2 + 1)][ry + (n / 2 + 1)] = r_grid[x][y]; // 격자의 시작점이 (0, 0)아닌 경우 완벽 정리
			}
		}

		// r_grid로 복사
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				r_grid[x][y] = next_grid[x][y];
			}
		}
	}

    /*
	cout << "r_grid" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cout << r_grid[x][y] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
    */
}

bool inRange(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < n);
}

void getCluster() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			visited[x][y] = false;
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (!visited[x][y]) {
				int num = r_grid[x][y];

				id++;
				component_num[id] = num;
				component_cnt[id] = 0;
				start_pos[id] = { x, y };
				
				queue<pair<int, int>> q;
				q.push({ x, y });
				visited[x][y] = true;
				cluster_grid[x][y] = id;
				component_cnt[id]++;

				while (!q.empty()) {
					int cx = q.front().first;
					int cy = q.front().second;
					q.pop();

					for (int dir = 0; dir < 4; dir++) {
						int nx = cx + dx[dir];
						int ny = cy + dy[dir];

						if (inRange(nx, ny) && !visited[nx][ny] && r_grid[nx][ny] == num) {
							q.push({ nx, ny });
							visited[nx][ny] = true;
							cluster_grid[nx][ny] = id;
							component_cnt[id]++;
						}
					}
				}

			}
		}
	}

    /*
	cout << "cluster_grid" << "\n";
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cout << cluster_grid[x][y] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "cluster info" << "\n";
	for (int i = 1; i <= id; i++) {
		cout << "id " << i << " : " << component_num[i] << " " << component_cnt[i] << "\n";
	}
	cout << "\n";
    */
}

int getLine(int id1, int id2) {
	int cnt = 0;

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			visited[x][y] = false;
		}
	}
	queue<pair<int, int>> q;

	q.push(start_pos[id1]);
	visited[start_pos[id1].first][start_pos[id1].second] = true; // 여기 id1 자리에 왜 id2 들어가 있냐?
	while (!q.empty()) {
		int cx = q.front().first; 
		int cy = q.front().second;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];

			if (inRange(nx, ny) && cluster_grid[nx][ny] == id2) cnt++;

			if (inRange(nx, ny) && !visited[nx][ny] && cluster_grid[nx][ny] == id1) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
			}
		}
	}

	//cout << "line :" << cnt << "\n";
	return cnt;
}

int getScore(int rot) {
	int score = 0;
	rotateGrid(rot);

	id = 0;
	getCluster();
	for (int i = 1; i < id; i++) {
		for (int j = i + 1; j <= id; j++) {
			score += (component_cnt[i] + component_cnt[j]) * component_num[i] * component_num[j] * (getLine(i, j));
		}
	}

	//cout << "score : " << score << "\n";
	return score;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	ans = 0;
	for (int rot = 0; rot < 4; rot++) {
		//cout << "rot : " << rot << "\n";
		ans += getScore(rot);
	}
	cout << ans << "\n";
}