#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

#define DIR_NUM 4
#define MAX 50

int n, m;
int car_x, car_y, car_d;
int rslt = 1;
int map[MAX][MAX];
bool visited[MAX][MAX];

int dx[DIR_NUM] = {-1, 0, 1, 0};
int dy[DIR_NUM] = {0, 1, 0, -1};

bool InRange(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

void Simulate() {
	while (1) {
		//cout << car_x << ' ' << car_y << ' ' << car_d << '\n';
		int nx, ny, nd;
		bool flag = false;
		for (int i = 0; i < DIR_NUM; i++) {
			nd = (car_d + 3 - i) % 4;
			nx = car_x + dx[nd];
			ny = car_y + dy[nd];

			if (InRange(nx, ny) && map[nx][ny] == 0 && !visited[nx][ny]) {
				visited[nx][ny] = true;
				car_x = nx;
				car_y = ny;
				car_d = nd;
				flag = true;
				rslt++;
				break;
			}
		}

		if (!flag) {
			nx = car_x - dx[car_d];
			ny = car_y - dy[car_d];
			if (InRange(nx, ny) && map[nx][ny] == 0) {
				car_x -= dx[car_d];
				car_y -= dy[car_d];
			}
			else {
				return;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m;
	cin >> car_x >> car_y >> car_d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	Simulate();

	if(rslt == 1) cout << 1 << '\n';
	else cout << rslt - 1 << '\n';

	return 0;
}