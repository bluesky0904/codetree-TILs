#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

typedef tuple<int, int, int, int, int> Marble;

#define ASCII_NUM 128
#define DIR_NUM 4
#define OFFSET 2000
#define COORD_SIZE 4000
#define BLANK -1

int t, n;
int last_collision_time;
int curr_time;

vector<Marble> marbles;
vector<Marble> next_marbles;
int next_marble_index[COORD_SIZE+1][COORD_SIZE+1];

int mapper[ASCII_NUM];
int dx[DIR_NUM] = {-1,0,1,0};
int dy[DIR_NUM] = {0,1,0,-1};

Marble Move(Marble marble) {
	int x, y, w, num, dir;
	tie(x, y, w, num, dir) = marble;

	int nx = x + dx[dir], ny = y + dy[dir];
	return make_tuple(nx, ny, w, num, dir);
}

bool OutOfCoordinate(Marble marble) {
	int x, y;
	tie(x, y, ignore, ignore, ignore) = marble;
	return x < 0 || x > COORD_SIZE || y < 0 || y > COORD_SIZE;
}

int FindDuplicateIndex(Marble marble) {
	int x, y;
	tie(x, y, ignore, ignore, ignore) = marble;
	return next_marble_index[x][y];
}

Marble Collide(Marble marble1, Marble marble2) {
	int weight1, num1;
	tie(ignore, ignore, weight1, num1, ignore) = marble1;

	int weight2, num2;
	tie(ignore, ignore, weight2, num2, ignore) = marble2;

	if (weight1 > weight2 || (weight1 == weight2 && num1 > num2)) return marble1;
	else return marble2;
}

void PushNextMarble(Marble marble) {
	if (OutOfCoordinate(marble)) return;

	int index = FindDuplicateIndex(marble);

	if (index == BLANK) {
		next_marbles.push_back(marble);
		int x, y;
		tie(x, y, ignore, ignore, ignore) = marble;
		next_marble_index[x][y] = (int)next_marbles.size() - 1;
	}
	else {
		next_marbles[index] = Collide(next_marbles[index], marble);
		last_collision_time = curr_time;
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
	mapper['L'] = 0;
	mapper['U'] = 1;
	mapper['R'] = 2;
	mapper['D'] = 3;

	for (int i = 0; i <= COORD_SIZE; i++) {
		for (int j = 0; j <= COORD_SIZE; j++) {
			next_marble_index[i][j] = BLANK;
		}
	}

	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		marbles.clear();
		last_collision_time = -1;

		cin >> n;
		for (int i = 1; i <= n; i++) {
			int x, y, w; char d;
			cin >> x >> y >> w >> d;
			x *= 2; y *= 2;
			x += OFFSET; y += OFFSET;
			marbles.push_back(make_tuple(x, y, w, i, mapper[d]));
		}

		for (int i = 1; i <= COORD_SIZE; i++) {
			curr_time = i;
			Simulate();
		}

		cout << last_collision_time << "\n";
	}
}