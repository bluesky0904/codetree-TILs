#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX_N 20

int n, m = 3;
int ans = INT_MAX;
char grid[MAX_N][MAX_N];

vector<pair<int, int>> coin_pos;
vector<pair<int, int>> selected;
pair<int, int> start_point;
pair<int, int> end_point;

int Dist(pair<int, int> a, pair<int, int> b) {
	int ax, ay;
	tie(ax, ay) = a;

	int bx, by;
	tie(bx, by) = b;

	return abs(ax - bx) + abs(ay - by);
}

int Calc() {
	int move_num = Dist(start_point, selected[0]);
	for (int i = 0; i < m - 1; i++) {
		move_num += Dist(selected[i], selected[i + 1]);
	}
	move_num += Dist(selected[m - 1], end_point);
	return move_num;
}

void FindMinMoves(int cnt, int curr_idx) {
	if (cnt == m) {
		ans = min(ans, Calc());
		return;
	}
	
	if (curr_idx == (int)coin_pos.size()) return;

	FindMinMoves(cnt, curr_idx + 1);

	selected.push_back(coin_pos[curr_idx]);
	FindMinMoves(cnt + 1, curr_idx + 1);
	selected.pop_back();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 'S') start_point = { i, j };
			if (grid[i][j] == 'E') end_point = { i, j };
		}
		cin.ignore();
	}

	for (int num = 1; num <= 9; num++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (grid[i][j] == num + '0') {
					coin_pos.push_back(make_pair(i, j));
				}
			}
		}
	}

	FindMinMoves(0, 0);

	if (ans == INT_MAX) cout << -1 << "\n";
	else cout << ans << "\n";
	return 0;
}