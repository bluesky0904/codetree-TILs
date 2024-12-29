/*
토끼 : P마리
	   고유번호 pid
	   한번 움직일 시 꼭 이동해야 하는 거리 d
	   위치. 초기 위치는 (1, 1) 
	   총 점프 횟수
	   점수

격자 : N x M 크기

1. 경주 시작 준비
2. 경주 진행
가장 우선순위가 높은 토끼를 뽑아 멀리 보내주는 것을 K번 반복
총 점프 횟수 최소 > 행 + 열 최소 > 행 최소 > 열 최소 > 고유번호 최소
상하좌우 네 방향으로 각각 d만큼 이동했을 때의 위치를 구하고 이동하는 도중 그 다음 칸이
격자를 벗어나게 된다면 방향을 반대로 바꿔 한 칸 이동
이렇게 구해진 4개의 위치 중
행 + 열 최대 > 행 최대 > 열 최대
가장 우선순위가 높은 칸을 골라 그 위치로 해당 토끼를 이동
이 칸의 위치를 (r,c)라 하면 해당 토끼를 제외한 나머지 P-1마리의 토끼들은 전부 r+c 만큼 점수 획득

K번의 턴이 모두 진행된 직후에는 행+열 최대 > 행 최대 > 열 최대 > 고유번호 최대
우선순위가 높은 토끼를 골라 점수 S를 더해줌.
단 이 경우에는 K번의 턴 동안 한번이라도 뽑혔던 적이 있던 토끼 중 골라야 함

3. 이동거리 변경
고유번호가 pid인 토끼의 이동거리를 L배 해줌

4. 최고의 토끼 선정
각 토끼가 모든 경주를 진행하며 얻은 점수 중 가장 높은 점수를 출력
*/

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <unordered_map>
using namespace std;

struct Rabbit {
	int x, y, j, id;

	bool operator < (const Rabbit& other) const {
		if (j != other.j) return j > other.j;
		if (x + y != other.x + other.y) return x + y > other.x + other.y;
		if (x != other.x) return x > other.x;
		if (y != other.y) return y > other.y;
		return id > other.id;
	}
};

unordered_map<int, int> stride;
unordered_map<int, pair<int, int>> pos;
unordered_map<int, int> jump_cnt;
unordered_map<int, long long> sub_score;
long long total_score;

priority_queue<Rabbit> pq;

int n, m, p;

bool Cmp(const Rabbit& a, const Rabbit& b) {
	if (a.x + a.y != b.x + b.y) return a.x + a.y < b.x + b.y;
	if (a.x != b.x) return a.x < b.x;
	if (a.y != b.y) return a.y < b.y;
	return a.id < b.id;
}

void RaceReady() {
	cin >> n >> m >> p;
	for (int i = 0; i < p; i++) {
		int id, d; cin >> id >> d;
		stride[id] = d;
		pos[id] = make_pair(1, 1);
		jump_cnt[id] = 0;
		sub_score[id] = 0;

		Rabbit new_rabbit;
		new_rabbit.id = id;
		new_rabbit.x = 1;
		new_rabbit.y = 1;
		new_rabbit.j = 0;

		pq.push(new_rabbit);
	}
	total_score = 0;
}

Rabbit GetUpRabbit(Rabbit cur_rabbit) {
	Rabbit up_rabbit = cur_rabbit;

	int dis = stride[up_rabbit.id];
	dis %= 2 * (n - 1);

	if (dis >= up_rabbit.x - 1) {
		dis -= (up_rabbit.x - 1);
		up_rabbit.x = 1;
	}
	else {
		up_rabbit.x -= dis;
		dis = 0;
	}

	if (dis >= n - up_rabbit.x) {
		dis -= (n - up_rabbit.x);
		up_rabbit.x = n;
	}
	else {
		up_rabbit.x += dis;
		dis = 0;
	}

	up_rabbit.x -= dis;

	return up_rabbit;
}

Rabbit GetDownRabbit(Rabbit cur_rabbit) {
	Rabbit down_rabbit = cur_rabbit;

	int dis = stride[down_rabbit.id];
	dis %= 2 * (n - 1);

	if (dis >= n - down_rabbit.x) {
		dis -= (n - down_rabbit.x);
		down_rabbit.x = n;
	}
	else {
		down_rabbit.x += dis;
		dis = 0;
	}

	if (dis >= down_rabbit.x - 1) {
		dis -= (down_rabbit.x - 1);
		down_rabbit.x = 1;
	}
	else {
		down_rabbit.x -= dis;
		dis = 0;
	}

	down_rabbit.x += dis;

	return down_rabbit;
}

Rabbit GetLeftRabbit(Rabbit cur_rabbit) {
	Rabbit left_rabbit = cur_rabbit;

	int dis = stride[left_rabbit.id];
	dis %= 2 * (m - 1);

	if (dis >= left_rabbit.y - 1) {
		dis -= (left_rabbit.y - 1);
		left_rabbit.y = 1;
	}
	else {
		left_rabbit.y -= dis;
		dis = 0;
	}

	if (dis >= m - left_rabbit.y) {
		dis -= (m - left_rabbit.y);
		left_rabbit.y = m;
	}
	else {
		left_rabbit.y += dis;
		dis = 0;
	}

	left_rabbit.y -= dis;

	return left_rabbit;
}

Rabbit GetRightRabbit(Rabbit cur_rabbit) {
	Rabbit right_rabbit = cur_rabbit;

	int dis = stride[right_rabbit.id];
	dis %= 2 * (m - 1);


	if (dis >= m - right_rabbit.y) {
		dis -= (m - right_rabbit.y);
		right_rabbit.y = m;
	}
	else {
		right_rabbit.y += dis;
		dis = 0;
	}

	if (dis >= right_rabbit.y - 1) {
		dis -= (right_rabbit.y - 1);
		right_rabbit.y = 1;
	}
	else {
		right_rabbit.y -= dis;
		dis = 0;
	}

	right_rabbit.y += dis;

	return right_rabbit;
}

void DoRace() {
	int k, s; cin >> k >> s;

	unordered_map<int, bool> is_selected;
	while (k--) {
		Rabbit cur_rabbit = pq.top(); pq.pop();
		is_selected[cur_rabbit.id] = true;

		Rabbit nex_rabbit = cur_rabbit;
		nex_rabbit.x = 0;
		nex_rabbit.y = 0;

		Rabbit up_rabbit = GetUpRabbit(cur_rabbit);
		if (Cmp(nex_rabbit, up_rabbit)) nex_rabbit = up_rabbit;
		
		Rabbit down_rabbit = GetDownRabbit(cur_rabbit);
		if (Cmp(nex_rabbit, down_rabbit)) nex_rabbit = down_rabbit;

		Rabbit left_rabbit = GetLeftRabbit(cur_rabbit);
		if (Cmp(nex_rabbit, left_rabbit)) nex_rabbit = left_rabbit;

		Rabbit right_rabbit = GetRightRabbit(cur_rabbit);
		if (Cmp(nex_rabbit, right_rabbit)) nex_rabbit = right_rabbit;

		nex_rabbit.j++;

		int nex_score = nex_rabbit.x + nex_rabbit.y;
		pos[nex_rabbit.id] = make_pair(nex_rabbit.x, nex_rabbit.y);
		jump_cnt[nex_rabbit.id] = nex_rabbit.j;
		total_score += nex_score;
		sub_score[nex_rabbit.id] += nex_score;
		pq.push(nex_rabbit);
	}

	Rabbit max_rabbit;
	max_rabbit.x = 1;
	max_rabbit.y = 1;
	for (unordered_map<int, pair<int, int>>::iterator it = pos.begin(); it != pos.end(); it++) {
		Rabbit cur_rabbit;
		cur_rabbit.id = it->first;
		cur_rabbit.x = it->second.first;
		cur_rabbit.y = it->second.second;
		if (is_selected.find(cur_rabbit.id) == is_selected.end()) continue;
		if (Cmp(max_rabbit, cur_rabbit)) max_rabbit = cur_rabbit;
	}

	sub_score[max_rabbit.id] -= s;
}

void ChangeDist() {
	int id, l; cin >> id >> l;
	stride[id] *= l;
}

void SelectBest() {
	long long min_sub = (int)1e9;
	for (unordered_map<int, long long>::iterator it = sub_score.begin(); it != sub_score.end(); it++) {
		min_sub = min(min_sub, it->second);
	}
	cout << total_score - min_sub << "\n";
}

int main() {
	int q; cin >> q;
	while (q--) {
		int command; cin >> command;
		if (command == 100) RaceReady();
		else if (command == 200) DoRace();
		else if (command == 300) ChangeDist();
		else if (command == 400) SelectBest();
	}
}