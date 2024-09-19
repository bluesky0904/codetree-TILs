/*
토끼 : P마리. 고유한 번호, 한번 움직일 시 꼭 이동해야 하는 거리
처음 토끼들은 전부 (1행, 1열)에 있음
격자 : N x M
(1) 경주 시작 준비
(2) 경주 진행
가장 우선순위가 높은 토끼를 뽑아 멀리 보내주는 것을 K번 반복
현재까지의 총 점프 횟수 최소 > 행 번호 + 열 번호 최소 > 행 번호 최소 > 열 번호 최소 > 고유번호 최소
우선순위가 가장 높은 토끼 : 상하좌우 di만큼 이동했을 때 행 + 열 번호 최대 > 행 번호 최대 > 열 번호 최대
i번 토끼를 제외한 나머지 P-1마리의 토끼들은 전부 ri + ci만큼의 점수를 동시에 얻게 됨.
K번의 턴이 모두 진행된 이후 행 + 열 번호 최대 > 행 최대 > 열 최대 > 고유번호 최대 토끼에게 S점 +
단, K번의 턴 동안 한번이라도 뽑혔던 적이 있던 토끼 중 가장 우선순위가 높은 토끼를 골라야 함.
(3) 이동거리 변경
고유번호가 pidt인 토끼의 이동거리를 L배 해줌.
(4) 최고의 토끼 선정
각 토끼가 모든 경주를 진행하며 얻은 점수 중 가장 높은 점수를 출력
*/

#include <iostream>
#include <queue>
#include <map>
using namespace std;

#define MAX_N 2000

int n, m, p;

int id[MAX_N + 1];
int pw[MAX_N + 1];
int jump_cnt[MAX_N + 1];
long long result[MAX_N + 1];
pair<int, int> point[MAX_N + 1];
map<int, int> id_to_idx;
bool is_runned[MAX_N + 1];

long long total_sum;

struct Rabbit {
	int x, y, j, id;

	bool operator < (const Rabbit& b) const {
		if (j != b.j) return j > b.j;
		if (x + y != b.x + b.y) return x + y > b.x + b.y;
		if (x != b.x) return x > b.x;
		if (y != b.y) return y > b.y;
		return id > b.id;
	}
};

bool Cmp(Rabbit a, Rabbit b) {
	if (a.x + a.y != b.x + b.y) return a.x + a.y < b.x + b.y;
	if (a.x != b.x) return a.x < b.x;
	if (a.y != b.y) return a.y < b.y;
	return a.id < b.id;
}

void init() {
	cin >> n >> m >> p;
	for (int i = 1; i <= p; i++) {
		cin >> id[i] >> pw[i];
		id_to_idx[id[i]] = i;
		point[i] = make_pair(1, 1);
	}
}

Rabbit GetUpRabbit(Rabbit cur_rabbit, int dis) {
	Rabbit up_rabbit = cur_rabbit;
	dis %= 2 * (n - 1);

	if (1 >= up_rabbit.x - dis) {
		dis -= (up_rabbit.x - 1);
		up_rabbit.x = 1;
	}
	else {
		up_rabbit.x -= dis;
		dis = 0;
	}

	if (n <= up_rabbit.x + dis) {
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

Rabbit GetDownRabbit(Rabbit cur_rabbit, int dis) {
	Rabbit down_rabbit = cur_rabbit;
	dis %= 2 * (n - 1);

	if (n <= down_rabbit.x + dis) {
		dis -= (n - down_rabbit.x);
		down_rabbit.x = n;
	}
	else {
		down_rabbit.x += dis;
		dis = 0;
	}

	if (1 >= down_rabbit.x - dis) {
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

Rabbit GetLeftRabbit(Rabbit cur_rabbit, int dis) {
	Rabbit left_rabbit = cur_rabbit;
	dis %= 2 * (m - 1);

	if (1 >= left_rabbit.y - dis) {
		dis -= (left_rabbit.y - 1);
		left_rabbit.y = 1;
	}
	else {
		left_rabbit.y -= dis;
		dis = 0;
	}

	if (m <= left_rabbit.y + dis) {
		dis -= (m - left_rabbit.y);
		left_rabbit.y = m;
	}
	else {
		left_rabbit.y -= dis;
		dis = 0;
	}

	left_rabbit.y -= dis;

	return left_rabbit;
}

Rabbit GetRightRabbit(Rabbit cur_rabbit, int dis) {
	Rabbit right_rabbit = cur_rabbit;
	dis %= 2 * (m - 1);

	if (m <= right_rabbit.y + dis) {
		dis -= (m - right_rabbit.y);
		right_rabbit.y = m;
	}
	else {
		right_rabbit.y -= dis;
		dis = 0;
	}

	if (1 >= right_rabbit.y - dis) {
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

void start_round() {
	int k, bonus;
	cin >> k >> bonus;
	priority_queue<Rabbit> rabbit_pq;

	for (int i = 1; i <= p; i++) {
		is_runned[i] = false;
	}

	for (int i = 1; i <= p; i++) {
		Rabbit new_rabbit;
		new_rabbit.x = point[i].first;
		new_rabbit.y = point[i].second;
		new_rabbit.j = jump_cnt[i];
		new_rabbit.id = id[i];

		rabbit_pq.push(new_rabbit);
	}

	while (k--) {
		Rabbit cur_rabbit = rabbit_pq.top(); rabbit_pq.pop();

		int dis = pw[id_to_idx[cur_rabbit.id]];
		Rabbit nex_rabbit = cur_rabbit;
		nex_rabbit.x = 0;
		nex_rabbit.y = 0;

		Rabbit up_rabbit = GetUpRabbit(cur_rabbit, dis);
		if (Cmp(nex_rabbit, up_rabbit)) nex_rabbit = up_rabbit;

		Rabbit down_rabbit = GetDownRabbit(cur_rabbit, dis);
		if (Cmp(nex_rabbit, down_rabbit)) nex_rabbit = down_rabbit;

		Rabbit left_rabbit = GetLeftRabbit(cur_rabbit, dis);
		if (Cmp(nex_rabbit, left_rabbit)) nex_rabbit = left_rabbit;

		Rabbit right_rabbit = GetRightRabbit(cur_rabbit, dis);
		if (Cmp(nex_rabbit, right_rabbit)) nex_rabbit = right_rabbit;

		nex_rabbit.j++;
		rabbit_pq.push(nex_rabbit);

		int nex_idx = id_to_idx[nex_rabbit.id];
		point[nex_idx] = make_pair(nex_rabbit.x, nex_rabbit.y);
		jump_cnt[nex_idx]++;

		is_runned[nex_idx] = true;

		result[nex_idx] -= (nex_rabbit.x + nex_rabbit.y);
		total_sum += (nex_rabbit.x + nex_rabbit.y);
	}

	Rabbit bonus_rabbit;
	bonus_rabbit.x = 0;
	bonus_rabbit.y = 0;
	while (!rabbit_pq.empty()) {
		Rabbit cur_rabbit = rabbit_pq.top(); rabbit_pq.pop();

		if (!is_runned[id_to_idx[cur_rabbit.id]]) continue;

		if (Cmp(bonus_rabbit, cur_rabbit)) bonus_rabbit = cur_rabbit;
	}

	result[id_to_idx[bonus_rabbit.id]] += bonus;
}

void power_up() {
	int id, t;
	cin >> id >> t;
	int idx = id_to_idx[id];
	pw[idx] *= t;
}

void print_result() {
	long long ans = 0;
	for (int i = 1; i <= p; i++) ans = max(ans, result[i] + total_sum);
	cout << ans;
}

int main() {
	int q;
	cin >> q;
	while (q--) {
		int query;
		cin >> query;
		if (query == 100) init();
		if (query == 200) start_round();
		if (query == 300) power_up();
		if (query == 400) print_result();
	}
}