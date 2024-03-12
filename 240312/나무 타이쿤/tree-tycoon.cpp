#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 15
#define DIR_NUM 8

int n, m;

int grid[MAX_N + 1][MAX_N + 1];
bool ribros[MAX_N + 1][MAX_N + 1];
vector<pair<int, int>> nutrients;

int dx[DIR_NUM] = {0,-1,-1,-1,0,1,1,1};
int dy[DIR_NUM] = {1,1,0,-1,-1,-1,0,1};

int dx_g[DIR_NUM] = {-1, -1, 1, 1};
int dy_g[DIR_NUM] = {-1, 1, 1, -1};

bool InRange(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

void RibrosClear() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ribros[i][j] = false;
		}
	}
}

pair<int, int> GetNextPos(pair<int, int> nutrient, int d, int p) {
	int x, y;
	tie(x, y) = nutrient;
	while (p--) {
		x += dx[d], y += dy[d];
		if (x > n) x = x % n;
		else if (x < 1) x = x + n;

		if (y > n) y = y % n;
		else if (y < 1) y = y + n;
	}

	ribros[x][y] = true;

	return make_pair(x, y);
}

void InsertNutrients() {
	for (int i = 0; i < (int)nutrients.size(); i++) {
		int x, y;
		tie(x, y) = nutrients[i];
		if (grid[x][y] == 0) grid[x][y] = 1;
		else grid[x][y]++;
	}
}

void PlusGrowth() {
	while (!nutrients.empty()) {
		int x, y, cnt = 0;
		tie(x, y) = nutrients.back();
		nutrients.pop_back();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx_g[i], ny = y + dy_g[i];
			if (InRange(nx, ny) && grid[nx][ny] >= 1) cnt++;
		}
		grid[x][y] += cnt;
	}
}

void PlantRibros() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!ribros[i][j] && grid[i][j] >= 2) {
				grid[i][j] -= 2;
				nutrients.push_back(make_pair(i, j));
			}
		}
	}
}

void Print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "---------------------\n";
}

void Simulate(int d, int p) {

	RibrosClear();

	for (int i = 0; i < (int)nutrients.size(); i++)
		nutrients[i] = GetNextPos(nutrients[i], d, p);

	InsertNutrients();

	PlusGrowth();

	PlantRibros();
}

int CountRibrosSum() {
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			sum += grid[i][j];
		}
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}

	nutrients.push_back(make_pair(n - 1, 1));
	nutrients.push_back(make_pair(n - 1, 2));
	nutrients.push_back(make_pair(n, 1));
	nutrients.push_back(make_pair(n, 2));

	while (m--) {
		int d, p;
		cin >> d >> p;
		Simulate(d-1, p);
	}

	cout << CountRibrosSum() << "\n";
	return 0;
}