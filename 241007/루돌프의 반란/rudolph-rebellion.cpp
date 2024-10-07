#include <iostream>
#include <climits>
using namespace std;

struct Santa {
	int idx;
	int dist;
	int row;
	int col;
};

bool Cmp(Santa a, Santa b) {
	if (a.dist != b.dist) return a.dist < b.dist;
	if (a.row != b.row) return a.row > b.row;
	return a.col > b.col;
}

#define GRID_SIZE 51
#define SANTA_NUM 31
#define GAME_OVER make_pair(-1, -1)
#define DIR_NUM 8

int N, M, P, C, D;
pair<int, int> santa_pos[SANTA_NUM]; // 산타의 위치
int stunned[SANTA_NUM]; // 산타의 기절 여부
int score[SANTA_NUM] = { 0, }; // 산타의 점수

pair<int, int> rudolf;

int dx[DIR_NUM] = {-1,-1,0,1,1,1,0,-1};
int dy[DIR_NUM] = {0,1,1,1,0,-1,-1,-1};

bool InRange(int x, int y) {
	return 1 <= x && x <= N && 1 <= y && y <= N;
}
bool StopTest() {
	for (int i = 1; i <= P; i++) {
		if (santa_pos[i] != GAME_OVER) return false;
	}
	return true;
}

int GetDist(int r1, int c1, int r2, int c2) {
	return (r1 - r2) * (r1 - r2) + (c1 - c2) * (c1 - c2);
}

void Interaction(int idx, int dir) {
	bool visited[SANTA_NUM] = { false, };
	visited[idx] = true;
	int move_num = idx;
	while (true) {
		bool santa_exist = false;
		for (int i = 1; i <= P; i++) {
			if (visited[i]) continue;
			if (santa_pos[i] == GAME_OVER) continue;
			if (!(santa_pos[move_num].first == santa_pos[i].first && santa_pos[move_num].second == santa_pos[i].second)) continue;
			visited[i] = true;
			santa_pos[i].first += dx[dir], santa_pos[i].second += dy[dir];
			santa_exist = true;
			if (!InRange(santa_pos[i].first, santa_pos[i].second)) {
				santa_pos[i] = GAME_OVER;
				return;
			}
			else move_num = i;
			break;
		}
		if (!santa_exist) return;
	}
}

void RudolfMove(int turn) {
	int choose_idx;
	Santa choose_santa;
	choose_santa.idx = -1;
	choose_santa.dist = 1e9;
	choose_santa.row = -1;
	choose_santa.col = -1;

	for (int i = 1; i <= P; i++) {
		if (santa_pos[i] == GAME_OVER) continue;
		Santa santa;
		santa.idx = i;
		santa.dist = GetDist(rudolf.first, rudolf.second, santa_pos[i].first, santa_pos[i].second);
		santa.row = santa_pos[i].first;
		santa.col = santa_pos[i].second;
		if(Cmp(santa, choose_santa)) choose_santa = santa;
	}

	choose_idx = choose_santa.idx;
	int min_dir = -1, min_dist = 1e9;
	for (int dir = 0; dir < DIR_NUM; dir++) {
		int nx = rudolf.first + dx[dir], ny = rudolf.second + dy[dir];
		if (InRange(nx, ny) && min_dist > GetDist(nx, ny, santa_pos[choose_idx].first, santa_pos[choose_idx].second)) {
			min_dir = dir;
			min_dist = GetDist(nx, ny, santa_pos[choose_idx].first, santa_pos[choose_idx].second);
		}
	}
	rudolf.first += dx[min_dir], rudolf.second += dy[min_dir];

	for (int i = 1; i <= P; i++) {
		if (santa_pos[i] == GAME_OVER) continue;
		if (!(rudolf.first == santa_pos[i].first && rudolf.second == santa_pos[i].second)) continue;
		score[i] += C;
		santa_pos[i].first += (dx[min_dir] * C), santa_pos[i].second += (dy[min_dir] * C);
		if (!InRange(santa_pos[i].first, santa_pos[i].second)) santa_pos[i] = GAME_OVER;
		else Interaction(i, min_dir);
		stunned[i] = turn + 2;
		break;
	}
}

bool Exist(int idx, int x, int y) {
	for (int i = 1; i <= P; i++) {
		if (i == idx) continue;
		if (x == santa_pos[i].first && y == santa_pos[i].second) return true;
	}
	return false;
}

void SantaMove(int turn) {
	for (int i = 1; i <= P; i++) {
		if (stunned[i] > turn) continue;
		if (santa_pos[i] == GAME_OVER) continue;

		int standard_dist = GetDist(santa_pos[i].first, santa_pos[i].second, rudolf.first, rudolf.second);
		int min_dir = -1, min_dist = standard_dist;

		for (int dir = 0; dir < DIR_NUM; dir += 2) {
			int nx = santa_pos[i].first + dx[dir], ny = santa_pos[i].second + dy[dir];
			if (InRange(nx, ny) && !Exist(i, nx, ny) && min_dist > GetDist(nx, ny, rudolf.first, rudolf.second)) {
				min_dir = dir;
				min_dist = GetDist(nx, ny, rudolf.first, rudolf.second);
			}
		}
		if (min_dist == standard_dist) continue;

		santa_pos[i].first += dx[min_dir], santa_pos[i].second += dy[min_dir];
		if (!(rudolf.first == santa_pos[i].first && rudolf.second == santa_pos[i].second)) continue;
		score[i] += D;
		santa_pos[i].first += (dx[(min_dir + 4) % 8] * D), santa_pos[i].second += (dy[(min_dir + 4) % 8] * D);
		if (!InRange(santa_pos[i].first, santa_pos[i].second)) santa_pos[i] = GAME_OVER;
		else Interaction(i, (min_dir + 4) % 8);
		stunned[i] = turn + 2;
	}
}

void Print(int turn) {
	cout << "///////////////////////// " << turn << " ////////////////////////////\n";

	for (int i = 1; i <= P; i++) {
		cout << score[i] << " ";
	}
	cout << "\n";

	cout << "Rudolf " << rudolf.first << " " << rudolf.second << "\n";
	for (int i = 1; i <= P; i++) {
		cout << "Santa #" << i << " " << santa_pos[i].first << " " << santa_pos[i].second << " " << stunned[i] << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	
	cin >> N >> M >> P >> C >> D;

	cin >> rudolf.first >> rudolf.second;

	for (int i = 1; i <= P; i++) {
		int num, x, y;
		cin >> num >> x >> y;
		santa_pos[num] = make_pair(x, y);
	}

	for (int turn = 1; turn <= M; turn++) {
		if (StopTest()) break;
		//Print(turn);

		RudolfMove(turn);
		//Print(turn);

		SantaMove(turn);
		//Print(turn);
		
		for (int i = 1; i <= P; i++) {
			if (santa_pos[i] == GAME_OVER) continue;
			score[i] += 1;
		}
		//Print(turn);
	}

	for (int i = 1; i <= P; i++) {
		cout << score[i] << " ";
	}
	cout << "\n";
	return 0;
}