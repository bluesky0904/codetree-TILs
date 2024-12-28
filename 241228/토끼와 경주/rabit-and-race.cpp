#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define MAX_P 2000
#define DIR_NUM 4

struct Rabbit {
    int id, x, y, j;

    bool operator <(const Rabbit& b) const {
        if (j != b.j) return j > b.j;
        if (x + y != b.x + b.y) return x + y > b.x + b.y;
        if (x != b.x) return x > b.x;
        if (y != b.y) return y > b.y;
        return id > b.id;
    }
};

unordered_map<int, Rabbit> rabbits;
unordered_map<int, int> stride;
unordered_map<int, long long> sub_score;

long long total_score = 0;
int n, m, p;

int dx[DIR_NUM] = { -1, 0, 1, 0 };
int dy[DIR_NUM] = { 0, 1, 0, -1 };

bool in_range(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

bool Cmp(Rabbit a, Rabbit b) {
    if (a.x + a.y != b.x + b.y) return a.x + a.y < b.x + b.y;
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.id < b.id;
}

void race_ready() {
    cin >> n >> m >> p;
    for (int i = 1; i <= p; i++) {
        int pid, d;
        cin >> pid >> d;
        Rabbit rabbit = { pid, 1, 1, 0};
        rabbits[pid] = rabbit;
        stride[pid] = d;
        sub_score[pid] = 0;
    }
}

Rabbit GetUpRabbit(Rabbit cur_rabbit, int dis) {
    Rabbit up_rabbit = cur_rabbit;
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

// 토끼를 아래로 이동시킵니다.
Rabbit GetDownRabbit(Rabbit cur_rabbit, int dis) {
    Rabbit down_rabbit = cur_rabbit;
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

// 토끼를 왼쪽으로 이동시킵니다.
Rabbit GetLeftRabbit(Rabbit cur_rabbit, int dis) {
    Rabbit left_rabbit = cur_rabbit;
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

// 토끼를 오른쪽으로 이동시킵니다.
Rabbit GetRightRabbit(Rabbit cur_rabbit, int dis) {
    Rabbit right_rabbit = cur_rabbit;
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

void start_race() {
    int k, s;
    cin >> k >> s;

    priority_queue<Rabbit> pq;
    for (unordered_map<int, Rabbit>::iterator it = rabbits.begin(); it != rabbits.end(); it++) {
        pq.push(it->second);
    }

    unordered_map<int, bool> is_runned;

    while (k--) {
        Rabbit cur_rabbit = pq.top(); pq.pop();

        int dis = stride[cur_rabbit.id];
        Rabbit nex_rabbit = cur_rabbit;
        nex_rabbit.x = 0;
        nex_rabbit.y = 0;

        Rabbit up_rabbit = GetUpRabbit(cur_rabbit, dis);
        // 지금까지의 도착지들보다 더 멀리 갈 수 있다면 도착지를 갱신합니다.
        if (Cmp(nex_rabbit, up_rabbit)) nex_rabbit = up_rabbit;


        // 토끼를 아래로 이동시킵니다.
        Rabbit down_rabbit = GetDownRabbit(cur_rabbit, dis);
        // 지금까지의 도착지들보다 더 멀리 갈 수 있다면 도착지를 갱신합니다.
        if (Cmp(nex_rabbit, down_rabbit)) nex_rabbit = down_rabbit;


        // 토끼를 왼쪽으로 이동시킵니다.
        Rabbit left_rabbit = GetLeftRabbit(cur_rabbit, dis);
        // 지금까지의 도착지들보다 더 멀리 갈 수 있다면 도착지를 갱신합니다.
        if (Cmp(nex_rabbit, left_rabbit)) nex_rabbit = left_rabbit;


        // 토끼를 오른쪽으로 이동시킵니다.
        Rabbit right_rabbit = GetRightRabbit(cur_rabbit, dis);
        // 지금까지의 도착지들보다 더 멀리 갈 수 있다면 도착지를 갱신합니다.
        if (Cmp(nex_rabbit, right_rabbit)) nex_rabbit = right_rabbit;

        nex_rabbit.j++;
        pq.push(nex_rabbit);
        rabbits[nex_rabbit.id] = nex_rabbit;
        int score = nex_rabbit.x + nex_rabbit.y;
        total_score += score;
        sub_score[nex_rabbit.id] += score;
        is_runned[nex_rabbit.id] = true;
    }

    Rabbit bonus_rabbit;
    bonus_rabbit.x = 0;
    bonus_rabbit.y = 0;
    while (!pq.empty()) {
        Rabbit new_rabbit = pq.top(); pq.pop();
        if (is_runned.find(new_rabbit.id) == is_runned.end()) continue;
        if(Cmp(bonus_rabbit, new_rabbit))
            bonus_rabbit = new_rabbit;
    }
    sub_score[bonus_rabbit.id] -= s;
}

void change_distance() {
    int pid, l;
    cin >> pid >> l;
    stride[pid] *= l;
}

void choose_best() {
    long long  min_sub = (int)1e9;
    for (auto& it : sub_score) {
        min_sub = min(min_sub, it.second);
    }
    cout << total_score - min_sub << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int q;
    cin >> q;

    while (q--) {
        int command;
        cin >> command;
        if (command == 100) race_ready();
        else if (command == 200) start_race();
        else if (command == 300) change_distance();
        else if (command == 400) choose_best();
    }

    return 0;
}