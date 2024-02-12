#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define MAX_N 50
#define DIR_NUM 4
#define ASCII_NUM 128

typedef tuple<int, int, int> Marble;
int t, n, m;

int dx[DIR_NUM] = { -1,0,1,0 };
int dy[DIR_NUM] = { 0,1,0,-1 };
int mapper[ASCII_NUM];
vector<Marble> marbles;
vector<Marble> next_marbles;
int marble_cnt[MAX_N][MAX_N];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

Marble GetNextPos(int x, int y, int dir) {
	int nx = x + dx[dir], ny = y + dy[dir];
	if (!InRange(nx, ny)) return make_tuple(x, y, (dir + 2) % 4);
	return make_tuple(nx, ny, dir);
}

Marble Move(Marble marble) {
	int x, y, dir;
	tie(x, y, dir) = marble;
	int nx, ny, ndir;
	tie(nx, ny, ndir) = GetNextPos(x, y, dir);
	return make_tuple(nx, ny, ndir);
}

void MoveAll() {
	for (int i = 0; i < marbles.size(); i++) {
		marbles[i] = Move(marbles[i]);
	}
}

bool DuplicateMarbleExist(int x, int y) {
	return marble_cnt[x][y] >= 2;
}

void RemoveDuplicateMarbles() {
	next_marbles.clear();

	for (int i = 0; i < marbles.size(); i++) {
		int x, y;
		tie(x, y, ignore) = marbles[i];
		marble_cnt[x][y]++;
	}

	for (int i = 0; i < marbles.size(); i++) {
		int x, y;
		tie(x, y, ignore) = marbles[i];
		if (!DuplicateMarbleExist(x, y)) next_marbles.push_back(marbles[i]);
	}

	for (int i = 0; i < marbles.size(); i++) {
		int x, y;
		tie(x, y, ignore) = marbles[i];
		marble_cnt[x][y]--;
	}

	marbles = next_marbles;
}

void Simulate() {
	MoveAll();
	RemoveDuplicateMarbles();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> t;
	mapper['U'] = 0;
	mapper['R'] = 1;
	mapper['D'] = 2;
	mapper['L'] = 3;
	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;
		marbles.clear();
		for (int i = 0; i < m; i++) {
			int x, y; char d;
			cin >> x >> y >> d;
			marbles.push_back(make_tuple(x - 1, y - 1, mapper[d]));
		}
		for (int i = 0; i < 2 * n; i++) Simulate();
		cout << marbles.size() << "\n";
	}
	return 0;
}