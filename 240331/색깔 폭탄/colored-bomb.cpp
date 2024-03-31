/*
1. 폭탄 묶음 : 2개 이상의 폭탄으로 이루어져 있어야 && 상하좌우로 인접해야함
모두 같은 색깔의 폭탄으로만 이루어져 있다 || 빨간색 폭탄을 포함하여 정확히 2개의 색깔로만 이루어져 있어야 함
- 예외 : 빨간색 폭탄으로만 이루어져 있는 경우는 올바른 폭탄 묶음이 아님
- 크기가 가장 큰 폭탄 묶음 : 가장 많은 수의 폭탄들로 이루어진 폭탄 묶음. 여러개라면 다음의 우선순위를 지님
빨간색 폭탄이 가장 적게 포함된 것
각 폭탄 묶음의 기준점 중 가장 행이 큰 폭탄 묶음. 기준점 = 빨간색이 아니면서 행이 가장 크고 열이 가장 작은 폭탄
2. 선택된 폭탄 묶음에 해당되는 폭탄들을 전부 제거. 이후 폭탄은 떨어짐 <-> 돌은 떨어지지 않음
3. 반시계 방향으로 90도 격자 회전
4. 폭탄은 떨어짐 <-> 돌은 떨어지지 않음

아래의 과정을 폭탄 묶음이 존재하지 않을 때까지 반복
한 round마다 폭탄 묶음을 이루고 있는 폭탄의 개수를 C라 했을 때, C * C 만큼의 점수를 얻게 됨
*/
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>
using namespace std;

#define MAX_N 20
#define MAX_M 5
#define DIR_NUM 4

int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

// 격자의 크기 n, 폭탄의 종류 수 m
int n, m;
// 폭탄이 터져서 얻는 점수
int score = 0;

struct Bundle {
	int cnt;
	int red_cnt;
	int x, y;
};

// 폭탄 묶음 리스트
vector<Bundle> bomb_bundle;

// 폭탄 관리 배열
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

bool cmp(Bundle a, Bundle b) {
	if(a.cnt != b.cnt) return a.cnt > b.cnt;
	if(a.red_cnt != b.red_cnt) return a.red_cnt < b.red_cnt;
	if(a.x != b.x) return a.x > b.x;
	return a.y < b.y;
}

void ChooseBFS(int x, int y) {
	int red_cnt = 0;
	int mx = x, my = y;

	int color = grid[x][y];
	queue<pair<int, int>> q;
	q.push({x, y});
	visited[x][y] = true;

	int cnt = 1;
	while (!q.empty()) {
		int cx, cy;
		tie(cx, cy) = q.front();
		q.pop();

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == color || grid[nx][ny] == 0)) {
				if (grid[nx][ny] == 0) red_cnt++;
				else {
					if (mx < nx || (mx == nx && my > ny)) {
						mx = nx;
						my = ny;
					}
				}
				cnt++;
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}

	if (cnt >= 2) {
		Bundle bundle;
		bundle.cnt = cnt;
		bundle.red_cnt = red_cnt;
		bundle.x = mx;
		bundle.y = my;
		bomb_bundle.push_back(bundle);
	}
}

void RemoveBFS(int x, int y) {
	int color = grid[x][y];
	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = true;

	int cnt = 1;
	while (!q.empty()) {
		int cx, cy;
		tie(cx, cy) = q.front();
		grid[cx][cy] = -2;
		q.pop();

		for (int dir = 0; dir < DIR_NUM; dir++) {
			int nx = cx + dx[dir], ny = cy + dy[dir];
			if (InRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == color || grid[nx][ny] == 0)) {
				cnt++;
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}

	score += (cnt * cnt);
}

void InitVisited() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			visited[x][y] = false;
		}
	}
}

bool Explode(){
	bomb_bundle.clear();
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			InitVisited();
			if (grid[x][y] >= 1) ChooseBFS(x, y);
		}
	}

	if ((int)bomb_bundle.size() == 0) return false;

	sort(bomb_bundle.begin(), bomb_bundle.end(), cmp);
	InitVisited();
	RemoveBFS(bomb_bundle[0].x, bomb_bundle[0].y);
	return true;
}

void Drop() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y] = -2;
		}
	}

	for (int y = 0; y < n; y++) {
		int idx = n - 1;
		for (int x = n - 1; x >= 0; x--) {
			if (grid[x][y] == -1) {
				idx = x - 1;
				next_grid[x][y] = -1;
			}
			else if (grid[x][y] == -2) continue;
			else{
				next_grid[idx][y] = grid[x][y];
				idx--;
			}
		}
	}
	
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

void Rotate() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y] = -2;
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			next_grid[x][y] = grid[y][n - x - 1];
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			grid[x][y] = next_grid[x][y];
		}
	}
}

int width = 3;

void Print() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cout << right << setw(width) << grid[x][y] << " ";
		}
		cout << "\n";
	}
	cout << "Score : " << score << '\n';
	cout << "-------------------------\n";
}

bool Simulate() {
	if(!Explode()) return false;
	Print();

	Drop();
	Print();

	Rotate();
	Print();

	Drop();
	Print();
	return true;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cin >> grid[x][y];
		}
	}

	while (true) {
		if(!Simulate()) break;
	}

	cout << score << '\n';
	return 0;
}