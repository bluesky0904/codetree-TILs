#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

#define MAX_N 50
#define DIR_NUM 4
#define ASCII_NUM 128

typedef tuple<int, int, int> Marble;

vector<Marble> marbles;

int t, n, m;
int mapper[ASCII_NUM];
int marble_cnt[MAX_N + 1][MAX_N + 1];
int dx[DIR_NUM] = {-1,0,0,1};
int dy[DIR_NUM] = {0,1,-1,0};

bool InRange(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

Marble Move(Marble marble) {
	int x, y, dir; tie(x, y, dir) = marble;
	int nx = x + dx[dir], ny = y + dy[dir];
	if (InRange(nx, ny)) return make_tuple(nx, ny, dir);
	else return make_tuple(x, y, 3-dir);
}

void MoveAll() {
	for (int i = 0; i < (int)marbles.size(); i++) marbles[i] = Move(marbles[i]);
}

bool DuplicateMarbleExist(int target_idx) {
	int target_x, target_y;
	tie(target_x, target_y, ignore) = marbles[target_idx];
	return marble_cnt[target_x][target_y] >= 2;
}

void RemoveDuplicateMarbles() {

	vector<Marble> temp_vector;

	for (int i = 0; i < (int)marbles.size(); i++) {
		int x, y;
		tie(x, y, ignore) = marbles[i];
		marble_cnt[x][y]++;
	}

	for (int i = 0; i < (int)marbles.size(); i++)
		if (!DuplicateMarbleExist(i)) temp_vector.push_back(marbles[i]);


	for (int i = 0; i < (int)marbles.size(); i++) {
		int x, y;
		tie(x, y, ignore) = marbles[i];
		marble_cnt[x][y]--;
	}

	marbles = temp_vector;
}

void Simulate() {
	MoveAll();
	RemoveDuplicateMarbles();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	mapper['U'] = 0;
	mapper['R'] = 1;
	mapper['L'] = 2;
	mapper['D'] = 3;

	cin >> t;
	while (t--) {

		marbles.clear();

		cin >> n >> m;

		for (int i = 0; i < m; i++) {
			int x, y; char dir; cin >> x >> y >> dir;
			marbles.push_back(make_tuple(x, y, mapper[dir]));
		}

		for (int i = 1; i <= 2 * n; i++) Simulate();
		cout << (int) marbles.size() << "\n";
	}
	return 0;
}