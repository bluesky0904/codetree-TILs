/*
격자 : n x m
곰팜이 : 크기(빨간색 숫자), 속력(파란색 숫자), 방향

곰팡이 채취
1. 승용이는 첫번째 열부터 탐색을 시작
2. 해당 열의 위에서 아래로 내려가며 탐색할 때 제일 빨리 발견한 곰팡이를 채취
곰팡이를 채취하고 나면 해당 칸은 빈칸이 되며, 해당 열에서 채취할 수 있는 곰팡이가 없는 경우도 있을 수 있음에 유의
3. 해당 열에서 채취시도가 끝나고 나면 곰팡이는 이동을 시작
4. 입력으로 주어진 방향과 속력으로 이동하며 격자판의 벽에 도달하면 반대로 방향을 바꾸고 속력을 유지한 채로 이동함
방향을 바꿀 때는 시간이 걸리지 않음
5. 모든 곰팡이가 이동을 끝낸 후에 한 칸에 곰팡이가 두마리 이상일 때는 크기가 큰 곰팡이가 다른 곰팡이를 모두 잡아먹음
6. 이 모든 과정은 1초가 걸리며 이후 승용이는 오른쪽 열로 이동해서 위의 과정을 반복

초기에 한 칸에 둘 이상의 곰팡이가 주어지는 경우는 없으며, 주어지는 곰팡이의 크기는 전부 다름

승용이가 해당 격자판에 있는 모든 열을 검사했을 때, 채취한 곰팡이 크기의 총합을 구하기
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tuple>
using namespace std;

const int GRIDSIZE = 100;
const int MAXK = 10000;

int n, m, k;
int ans;

int grid[GRIDSIZE + 10][GRIDSIZE + 10];
int next_grid[GRIDSIZE + 10][GRIDSIZE + 10];
int bac_s[MAXK + 10];
int bac_d[MAXK + 10];

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

void print() {
	cout << "grid" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "ans : " << ans << "\n";
}

void catchBac(int col) {
	for (int row = 0; row < n; row++) {
		if (grid[row][col] != 0) {
			ans += grid[row][col];
			grid[row][col] = 0;
			return;
		}
	}
}

/*
3. 해당 열에서 채취시도가 끝나고 나면 곰팡이는 이동을 시작
4. 입력으로 주어진 방향과 속력으로 이동하며 격자판의 벽에 도달하면 반대로 방향을 바꾸고 속력을 유지한 채로 이동함
방향을 바꿀 때는 시간이 걸리지 않음
5. 모든 곰팡이가 이동을 끝낸 후에 한 칸에 곰팡이가 두마리 이상일 때는 크기가 큰 곰팡이가 다른 곰팡이를 모두 잡아먹음
6. 이 모든 과정은 1초가 걸리며 이후 승용이는 오른쪽 열로 이동해서 위의 과정을 반복

초기에 한 칸에 둘 이상의 곰팡이가 주어지는 경우는 없으며, 주어지는 곰팡이의 크기는 전부 다름

승용이가 해당 격자판에 있는 모든 열을 검사했을 때, 채취한 곰팡이 크기의 총합을 구하기
*/

bool inRange(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < m);
}

tuple<int, int, int> getNextPos(int x, int y, int s, int d) {
	int cx = x;
	int cy = y;
	int cd = d;
	for (int dist = 1; dist <= s; dist++) {
		int nx = cx + dx[cd];
		int ny = cy+ dy[cd]; // 여기 왜 cx 사용중?

		if (!inRange(nx, ny)) {
			cd = (cd + 2) % 4;
			nx = cx + dx[cd];
			ny = cy + dy[cd];
		}

		cx = nx;
		cy = ny;
	}

	return { cx, cy, cd };
}

void moveBac() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			next_grid[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 0) continue;
			int nx, ny, nd;
			tie(nx, ny, nd) = getNextPos(i, j, bac_s[grid[i][j]], bac_d[grid[i][j]]);

			// 다음 격자로 위치. 다른 박테리아가 있으면 크기가 큰 곰팡이만 살아남음
			if (next_grid[nx][ny] == 0) {
				next_grid[nx][ny] = grid[i][j];
				bac_d[grid[i][j]] = nd;
			}
			else {
				if (next_grid[nx][ny] < grid[i][j]) {
					next_grid[nx][ny] = grid[i][j];
					bac_d[grid[i][j]] = nd;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			grid[i][j] = next_grid[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> n >> m >> k;

	for (int i = 1; i <= k; i++) {
		int x, y, s, d, b; cin >> x >> y >> s >> d >> b;
		x--; y--;
		if (d == 1) d = 3;
		else if (d == 2) d = 1;
		else if (d == 3) d = 0;
		else if (d == 4) d = 2; // == 2는 모임?
		grid[x][y] = b;
		bac_s[b] = s;
		bac_d[b] = d;
	}

	//print();
	ans = 0;
	for (int col = 0; col < m; col++) {
		//cout << "col : " << col << "\n";

		//cout << "catchBac" << "\n";
		catchBac(col);
		//print();

		//cout << "moveBac" << "\n";
		moveBac();
		//print();
	}
	cout << ans << "\n";
	return 0;
}