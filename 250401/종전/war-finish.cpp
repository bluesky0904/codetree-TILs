/*
격자 : n x n
격자의 숫자들 = 지역별 인구수
다섯 개의 부족

기울어진 직사각형 : 격자내에 있는 한 지점으로부터 체스의 비숍처럼 대각선으로 움직이며 반시계 순회를 했을 때
지나왔던 지점들의 집합
이때 반드시 아래에서 시작해서 1, 2, 3, 4번 방향순으로 순회해야하며 각 방향으로 최소 1번은 움직여야 함
또한 이동하는 도중 격자 밖으로 넘어가서는 안됨

1번 부족은 기울어진 직사각형의 경계와 그 안에 있는 지역을 가짐
기울어진 직사각형의 꼭짓점은 상하좌우로 4가지가 존재하고, 이루는 경계선 또한 4가지가 존재
이러한 꼭짓점과 선을 기준으로 나머지 부족이 갖는 지역이 결정
(상세 서술 확인)

각 부족장이 관리하는 인구 수의 최댓값과 최솟값의 차이가 가장 최소가 되는 것으로 경계를 정하고자 함
각 부족장이 관리하는 인구 수의 최댓값과 최솟값의 차이가 가장 작을 때의 값을 계산
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 20;
const int FIVE = 5;
const int INF = 1e9;

int n;
int grid[MAXN + 10][MAXN + 10];
int boarder[MAXN + 10][MAXN + 10];
int population[FIVE + 10];
int total_population;
int ans;

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

bool inRange(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < n);
}

bool isPossible(int x, int y, int k, int l) {
	return (inRange(x - k, y + k) && inRange(x - k - l, y + k - l) && inRange(x - l, y - l));
}

void makeBoarder(int x, int y, int k, int l) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			boarder[i][j] = 0;
		}
	}
	
	int dx[4] = { -1,-1,1,1 };
	int dy[4] = { 1,-1,-1,1 };

	boarder[x][y] = 1;
	for (int i = 0; i < k; i++) {
		x += dx[0];
		y += dy[0];
		boarder[x][y] = 1;
	}
	for (int i = 0; i < l; i++) {
		x += dx[1];
		y += dy[1];
		boarder[x][y] = 1;
	}
	for (int i = 0; i < k; i++) {
		x += dx[2];
		y += dy[2];
		boarder[x][y] = 1;
	}
	for (int i = 0; i < l; i++) {
		x += dx[3];
		y += dy[3];
		boarder[x][y] = 1;
	}

	/*
	cout << "boarder" << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << boarder[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	*/
}

int getScore(int x, int y, int k, int l) {
	for (int i = 1; i <= 5; i++) {
		population[i] = 0;
	}
	makeBoarder(x, y, k, l);

	for (int i = 0; i < x - l; i++) {
		for (int j = 0; j <= y + k - l && boarder[i][j] == 0; j++) {
			population[2] += grid[i][j];
		}
	}

	for (int i = 0; i <= x - k; i++) {
		for (int j = n - 1; j > y + k - l && boarder[i][j] == 0; j--) {
			population[3] += grid[i][j];
		}
	}

	for (int i = x - l; i < n; i++) {
		for (int j = 0; j < y && boarder[i][j] == 0; j++) {
			population[4] += grid[i][j];
		}
	}

	for (int i = x - k + 1; i < n; i++) {
		for (int j = n - 1; j >= y && boarder[i][j] == 0; j--) {
			population[5] += grid[i][j];
		}
	}

	population[1] = total_population;
	for (int i = 2; i <= 5; i++) {
		population[1] -= population[i];
	}

	int max_p = -1;
	int min_p = INF;
	for (int i = 1; i <= 5; i++) {
		max_p = max(max_p, population[i]);
		min_p = min(min_p, population[i]);
	}

	return (max_p - min_p);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> n;
	total_population = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			total_population += grid[i][j];
		}
	}
	
	ans = INF;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int k = 1; k <= n; k++) {
				for (int l = 1; l <= n; l++) {
					if (isPossible(x, y, k, l)) {
						ans = min(ans, getScore(x, y, k, l));
					}
				}
			}
		}
	}

	cout << ans << "\n";
	return 0;
}