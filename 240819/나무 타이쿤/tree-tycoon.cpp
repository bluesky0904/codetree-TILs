#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 15
#define DIR_NUM 8

int n, m;
int grid[MAX_N][MAX_N];
vector <pair<int, int>> nutrients;
vector <pair<int, int>> next_nutrients;

int dx[DIR_NUM] = { 0, -1, -1, -1, 0, 1, 1, 1};
int dy[DIR_NUM] = { 1, 1, 0, -1, -1, -1, 0, 1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void MoveNutrient(int d, int p) {
	next_nutrients.clear();
	for (int i = 0; i < (int)nutrients.size(); i++) {
		int nx = nutrients[i].first + dx[d] * p;
		int ny = nutrients[i].second + dy[d] * p;
		while (nx < 0) {
			nx += n;
		}
		while (ny < 0) {
			ny += n;
		}
		nx %= n;
		ny %= n;
		next_nutrients.push_back({ nx, ny });
	}
	nutrients = next_nutrients;
	next_nutrients.clear();
}

void InsertNutrient() {
	for (int i = 0; i < (int)nutrients.size(); i++) {
		int x = nutrients[i].first;
		int y = nutrients[i].second;
		grid[x][y]++;
	}
}

void SurplusGrowth() {
	for (int i = 0; i < (int)nutrients.size(); i++) {
		int x = nutrients[i].first;
		int y = nutrients[i].second;
		int cnt = 0;
		for (int dir = 1; dir < DIR_NUM; dir += 2) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (InRange(nx, ny) && grid[nx][ny] >= 1) {
				cnt++;
			}
		}
		grid[x][y] += cnt;
	}
}

bool NutrientPosition(int x, int y) {
	for (int i = 0; i < (int)nutrients.size(); i++) {
		if (nutrients[i].first == x && nutrients[i].second == y) {
			return true;
		}
	}
	return false;
}

void BuyNutrient() {
	next_nutrients.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!NutrientPosition(i, j) && grid[i][j] >= 2) {
				grid[i][j] -= 2;
				next_nutrients.push_back({ i, j });
			}
		}
	}
	nutrients = next_nutrients;
	next_nutrients.clear();
}

void Simulate(int d, int p) {
	MoveNutrient(d, p);
	InsertNutrient();
	SurplusGrowth();
	BuyNutrient();
}

int GetHeightSum() {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += grid[i][j];
		}
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	nutrients.push_back({ n - 2, 0 });
	nutrients.push_back({ n - 2, 1 });
	nutrients.push_back({ n - 1, 0 });
	nutrients.push_back({ n - 1, 1 });

	for (int i = 0; i < m; i++) {
		int d, p;
		cin >> d >> p;
		d--;
		Simulate(d, p);
	}

	cout << GetHeightSum() << "\n";
	return 0;
}