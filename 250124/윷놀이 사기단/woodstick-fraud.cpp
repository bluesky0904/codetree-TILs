#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#define MOVE_NUMS 10
#define PIECE_NUM 4
#define MAX_NUM 45
#define START 0
#define END 20

int curr_pos[PIECE_NUM];
int move_nums[MOVE_NUMS];
int points[MAX_NUM] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,0,
13,16,19,0,0,
22,24,0,0,0,
28,27,26,0,0,0,0,0,0,0,
25,30,35,40};

int max_score;

bool isBlue(int curr_pos) {
	return curr_pos != START && curr_pos % 5 == 0;
}

int getNextPos(int curr_pos, int move_num) {
	if (curr_pos == END) return END;
	if (move_num == 0) return curr_pos;

	int next_pos = curr_pos + 1;
	if (curr_pos == 23 || curr_pos == 27 || curr_pos == 33) next_pos = 41;
	else if (curr_pos == 19) next_pos = 44;
	else if (curr_pos == 44) next_pos = 20;

	return getNextPos(next_pos, move_num - 1);
}

bool isOverlapped() {
	for (int i = 0; i < PIECE_NUM; i++) {
		for (int j = i + 1; j < PIECE_NUM; j++) {
			if (curr_pos[i] == curr_pos[j] && curr_pos[i] != START && curr_pos[i] != END) return true;
		}
	}
	return false;
}

void findMaxScore(int cnt, int score) {
	if (cnt == MOVE_NUMS) {
		max_score = max(max_score, score);
		return;
	}

	for (int i = 0; i < PIECE_NUM; i++) {
		if (curr_pos[i] == END) continue;

		int tmp = curr_pos[i];

		if (isBlue(curr_pos[i]))
			curr_pos[i] = getNextPos(curr_pos[i] + 16, move_nums[cnt] - 1);
		else
			curr_pos[i] = getNextPos(curr_pos[i], move_nums[cnt]);

		if (!isOverlapped())
			findMaxScore(cnt + 1, score + points[curr_pos[i]]);

		curr_pos[i] = tmp;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);

	for (int i = 0; i < MOVE_NUMS; i++)
		cin >> move_nums[i];

	findMaxScore(0, 0);

	cout << max_score << "\n";
	return 0;
}