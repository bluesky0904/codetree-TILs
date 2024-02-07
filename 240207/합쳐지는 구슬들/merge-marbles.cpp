#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 50
#define ASCII_NUM 128
#define DIR_NUM 4
#define BLANK -1

typedef tuple<int, int, int, int, int> Marble;

int n, m, t;

vector<Marble> marbles;
vector<Marble> next_marbles;
int next_marble_index[MAX_N][MAX_N];

int mapper[ASCII_NUM];
int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

Marble Move(Marble marble) {
	int x, y, weight, dir, num;
	tie(x, y, weight, dir, num) = marble;
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	if (!InRange(nx, ny)) {
		dir = (dir + 2) % 4;
		return make_tuple(x, y, weight, dir, num);
	}
	return make_tuple(nx, ny, weight, dir, num);
}

int FindDuplicateMarble(Marble marble) {
	int x, y;
	tie(x, y, ignore, ignore, ignore) = marble;
	return next_marble_index[x][y];
}

Marble Merge(Marble marble1, Marble marble2) {
	int x, y, weight1, dir1, num1;
	tie(x, y, weight1, dir1, num1) = marble1;
	int weight2, dir2, num2;
	tie(ignore, ignore, weight2, dir2, num2) = marble2;
	if (num1 > num2) return make_tuple(x, y, weight1 + weight2, dir1, num1);
	else return make_tuple(x, y, weight1 + weight2, dir2, num2);
}

void PushNextMarble(Marble marble) {
	int index = FindDuplicateMarble(marble);

	if (index == BLANK) {
		next_marbles.push_back(marble);
		int x, y;
		tie(x, y, ignore, ignore, ignore) = marble;
		next_marble_index[x][y] = next_marbles.size() - 1;
	}
	else {
		next_marbles[index] = Merge(next_marbles[index], marble);
	}
}

void Simulate() {
	for (int i = 0; i < marbles.size(); i++) {
		Marble next_marble = Move(marbles[i]);
		PushNextMarble(next_marble);
	}
	
	marbles = next_marbles;

	for (int i = 0; i < next_marbles.size(); i++) {
		int x, y;
		tie(x, y, ignore, ignore, ignore) = next_marbles[i];
		next_marble_index[x][y] = BLANK;
	}
	next_marbles.clear();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	mapper['U'] = 0;
	mapper['R'] = 1;
	mapper['D'] = 2;
	mapper['L'] = 3;

	marbles.clear();

	cin >> n >> m >> t;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			next_marble_index[i][j] = BLANK;
		}
	}

	for (int i = 1; i <= m; i++) {
		int r, c, w; char d;
		cin >> r >> c >> d >> w;
		marbles.push_back(make_tuple(r - 1, c - 1, w, mapper[d], i));
	}

	while (t--) Simulate();

	int max_weight = -1;
	for (int i = 0; i < marbles.size(); i++) max_weight = max(max_weight, get<2>(marbles[i]));
	cout << marbles.size() << " " << max_weight << "\n";
}