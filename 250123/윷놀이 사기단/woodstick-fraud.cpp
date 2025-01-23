/*
윷을 던질 수 있는 횟수는 10회 밖에 없으며 각 횟수마다 나오는 이동 칸 수도 정해져 있음
주어진 이동 횟수에 나갈 말의 종류를 잘 조합하여 얻을 숭 있는 점수의 최댓값을 구해보자

처음에는 시작 칸에 말 4개가 주어짐

말은 게임판에 그려진 화살표를 따라서만 이동 가능
파란색 칸에서 이동을 시작하면 빨간색 화살표를 따라 가야 함
말이 도착 칸으로 이동하면 남은 이동 횟수와 관계 없이 이동을 마침

게임은 10개의 턴으로 이뤄지고 도착칸에 도착하지 않은 말을 골라 원하는 이동횟수만큼 이동
시작칸과 도착칸을 제외하고는 칸에 말들을 겹쳐서 올릴 수 없음
특정 말을 움직였을 때 도달하게 되는 위치에 다른 말이 이미 있다면, 이는 불가능한 이동임을 의미
그림에서 40이 적혀있는 칸은 도착칸이 아님

말이 한 번 이동을 마칠 때마다 칸에 있는 수가 점수에 추가

10개의 이동할 수 있는 칸 수가 순서대로 주어질 때 얻을 수 있는 점수의 최댓값

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

#define MOVE_NUMS 10
#define PIECE_NUM 4
#define MAX_NUM 45
#define START 0
#define END 20

int move_nums[MOVE_NUMS];
int curr_pos[PIECE_NUM];
int points[MAX_NUM] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,0,
						13, 16, 19, 0, 0,
						22, 24, 0, 0, 0, 
						28, 27, 26, 0, 0 ,0, 0, 0, 0, 0,
						25, 30, 35, 40};

int max_score;

bool isBlue(int curr_pos) {
	return curr_pos != START && curr_pos % 5 == 0;
}

bool isOverlapped() {
	for (int i = 0; i < PIECE_NUM; i++)
		for (int j = i + 1; j < PIECE_NUM; j++)
			if (curr_pos[i] == curr_pos[j] && curr_pos[i] != START && curr_pos[i] != END) return true;
	return false;
}

int getNextPos(int curr_pos, int move_num){
	if (curr_pos == END) return END;
	if (move_num == 0) return curr_pos;

	int next_pos = curr_pos + 1;
	if (curr_pos == 23 || curr_pos == 27 || curr_pos == 33)
		next_pos = 41;
	else if (curr_pos == 19)
		next_pos = 44;
	else if (curr_pos == 44)
		next_pos = END;
	
	return getNextPos(next_pos, move_num - 1);
}

void searchMaxScore(int cnt, int score) {
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
			searchMaxScore(cnt + 1, score + points[curr_pos[i]]);

		curr_pos[i] = tmp;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("input.txt", "r", stdin);

	for (int i = 0; i < MOVE_NUMS; i++)
		cin >> move_nums[i];

	searchMaxScore(0, 0);
	
	cout << max_score << "\n";
	return 0;
}