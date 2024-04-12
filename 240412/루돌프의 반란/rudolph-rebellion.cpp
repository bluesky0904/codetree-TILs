#include <iostream>
#include <tuple>
using namespace std;

#define MAX_N 50
#define MAX_P 30

int n, m, p, c, d;
pair<int, int> rudolf; // 루돌프 위치
pair<int, int> pos[MAX_P + 1]; // 산타 위치
int stun[MAX_P + 1]; // 산타 기절
bool is_live[MAX_P + 1]; // 산타 탈락 여부
int points[MAX_P + 1]; // 산타 점수

int grid[MAX_N][MAX_N]; // 시뮬레이션용 배열

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

int main() {
	cin >> n >> m >> p >> c >> d;
	cin >> rudolf.first >> rudolf.second;
	rudolf.first--; rudolf.second--;
	grid[rudolf.first][rudolf.second] = -1;

	for (int i = 1; i <= p; i++) {
		int id;
		cin >> id;
		cin >> pos[id].first >> pos[id].second;
		pos[id].first--; pos[id].second--;
		grid[pos[id].first][pos[id].second] = id;
		is_live[id] = true;
	}

	for (int t = 1; t <= m; t++) {
		int closest_x = 10000, closest_y = 10000, closest_idx = 0;

		for (int i = 1; i <= p; i++) {
			if (!is_live[i]) continue;

			tuple<int, int, int> current_best = make_tuple((closest_x - rudolf.first) * (closest_x - rudolf.first) + (closest_y - rudolf.second) * (closest_y - rudolf.second), -closest_x, -closest_y);
			tuple<int, int, int> current_value = make_tuple((pos[i].first - rudolf.first) * (pos[i].first - rudolf.first) + (pos[i].second - rudolf.second) * (pos[i].second - rudolf.second), -pos[i].first, -pos[i].second);

			if (current_value < current_best) {
				closest_x = pos[i].first;
				closest_y = pos[i].second;
				closest_idx = i;
			}
		}

		if (closest_idx) {
			pair<int, int> prev_rudolf = rudolf;
			int move_x = 0;
			if (closest_x > rudolf.first) move_x = 1;
			else if (closest_x < rudolf.first) move_x = -1;

			int move_y = 0;
			if (closest_y > rudolf.second) move_y = 1;
			else if (closest_y < rudolf.second) move_y = -1;

			rudolf.first += move_x;
			rudolf.second += move_y;
			grid[prev_rudolf.first][prev_rudolf.second] = 0;

			if (rudolf.first == closest_x && rudolf.second == closest_y) {
				int first_x = closest_x + move_x * c;
				int first_y = closest_y + move_y * c;
				int last_x = first_x;
				int last_y = first_y;

				stun[closest_idx] = t + 1;

				while (InRange(last_x, last_y) && grid[last_x][last_y] > 0) {
					last_x += move_x;
					last_y += move_y;
				}

				while (!(last_x == first_x && last_y == first_y)) {
					int before_x = last_x - move_x;
					int before_y = last_y - move_y;

					if (!InRange(before_x, before_y)) break;
					int idx = grid[before_x][before_y];
					if (!InRange(last_x, last_y)) is_live[idx] = false;
					else {
						grid[last_x][last_y] = grid[before_x][before_y];
						pos[idx] = { last_x, last_y };
					}

					last_x = before_x;
					last_y = before_y;
				}

				points[closest_idx] += c;
				pos[closest_idx] = { first_x, first_y };
				if (InRange(first_x, first_y)) grid[first_x][first_y] = closest_idx;
				else is_live[closest_idx] = false;
			}
		}

		grid[rudolf.first][rudolf.second] = -1;

		for (int i = 1; i <= p; i++) {
			if (!is_live[i] || stun[i] >= t) continue;
			int min_dist = (pos[i].first - rudolf.first) * (pos[i].first - rudolf.first) + (pos[i].second - rudolf.second) * (pos[i].second - rudolf.second);
			int move_dir = -1;

			int dx[4] = {-1,0,1,0};
			int dy[4] = {0,1,0,-1};
			for (int dir = 0; dir < 4; dir++) {
				int nx = pos[i].first + dx[dir], ny = pos[i].second + dy[dir];
				if (!InRange(nx, ny) || grid[nx][ny] > 0) continue;

				int dist = (nx - rudolf.first) * (nx - rudolf.first) + (ny - rudolf.second) * (ny - rudolf.second);
				if (dist < min_dist) {
					min_dist = dist;
					move_dir = dir;
				}
			}

			if (move_dir != -1) {
				int nx = pos[i].first + dx[move_dir];
				int ny = pos[i].second + dy[move_dir];

				if (nx == rudolf.first && ny == rudolf.second) {
					stun[i] = t + 1;
					int move_x = -dx[move_dir];
					int move_y = -dy[move_dir];

					int first_x = nx + move_x * d;
					int first_y = ny + move_y * d;
					int last_x = first_x;
					int last_y = first_y;

					if (d == 1) points[i] += d;
					else {
						while (InRange(last_x, last_y) && grid[last_x][last_y] > 0) {
							last_x += move_x;
							last_y += move_y;
						}

						while (!(last_x == first_x && last_y == first_y)) {
							int before_x = last_x - move_x;
							int before_y = last_y - move_y;
							
							if (!InRange(before_x, before_y)) break;

							int idx = grid[before_x][before_y];

							if (!InRange(last_x, last_y)) is_live[idx] = false;
							else {
								grid[last_x][last_y] = grid[before_x][before_y];
								pos[idx] = { last_x, last_y};
							}

							last_x = before_x;
							last_y = before_y;
						}

						points[i] += d;
						grid[pos[i].first][pos[i].second] = 0;
						pos[i] = { first_x, first_y };
						if (InRange(first_x, first_y)) grid[first_x][first_y] = i;
						else is_live[i] = false;
					}
				}
				else {
					grid[pos[i].first][pos[i].second] = 0;
					pos[i] = { nx, ny };
					grid[nx][ny] = i;
				}
			}
		}
		for (int i = 1; i <= p; i++) if (is_live[i]) points[i]++;
	}

	for (int i = 1; i <= p; i++) cout << points[i] << " ";
}