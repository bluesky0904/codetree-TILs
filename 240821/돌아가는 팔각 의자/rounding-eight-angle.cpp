#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
using namespace std;

int chair[4][8];
int k;
bool visited[4];
int dir[4];

void RotateCheck(int n, int d) {
	visited[n] = true;
	dir[n] = d;

	if(n-1 >=0 && !visited[n-1] && chair[n-1][2] != chair[n][6]) RotateCheck(n - 1, -d);
	if(n+1 < 4 && !visited[n + 1] && chair[n][2] != chair[n+1][6]) RotateCheck(n + 1, -d);
}

void Rotate() {
	for (int i = 0; i < 4; i++) {
		if (dir[i] == 0) continue;
		else if (dir[i] == 1) {
			int tmp = chair[i][7];
			for (int j = 7; j > 0; j--) {
				chair[i][j] = chair[i][j - 1];
			}
			chair[i][0] = tmp;
		}
		else {
			int tmp = chair[i][0];
			for (int j = 0; j < 7; j++) {
				chair[i][j] = chair[i][j + 1];
			}
			chair[i][7] = tmp;
		}
	}
}

int SouthCheck() {
	int rslt = 0;
	for (int i = 0; i < 4; i++) {
		if (chair[i][0] == 1) {
			rslt += pow(2, i);
		}
	}
	return rslt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			char c;
			cin >> c;
			chair[i][j] = c - '0'; // 0은 북쪽, 1은 남쪽
		}
	}

	cin >> k;
	for (int i = 0; i < k; i++) {
		int n, d;
		cin >> n >> d; // 1은 시계방향, -1은 반시계방향
		n -= 1; // 0부터 시작하므로

		fill(visited, visited + 4, false);
		fill(dir, dir + 4, 0);
		RotateCheck(n, d);
		Rotate();
	}

	cout << SouthCheck() << "\n";
	return 0;
}