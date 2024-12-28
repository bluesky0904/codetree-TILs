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
unordered_map<int, int> sub_score;

int total_score = 0;
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

        int id = cur_rabbit.id;
        int cur_row = cur_rabbit.x;
        int cur_col = cur_rabbit.y;

        // 이동 가능한 위치 계산
        priority_queue<tuple<int, int, int>> next_positions;
        for (int dir = 0; dir < DIR_NUM; dir++) {
            int nx = cur_row, ny = cur_col;
            int cdir = dir;
            int dis;
            if(dir % 2 == 0) dis = (stride[id] % (2 * (n-1)));
            else dis = (stride[id] % (2 * (m - 1)));

            for (int i = 0; i < dis; i++) {
                int tx = nx + dx[cdir];
                int ty = ny + dy[cdir];
                if (!in_range(tx, ty)) {
                    cdir = (cdir + 2) % 4;
                    nx += dx[cdir];
                    ny += dy[cdir];
                }
                else {
                    nx = tx;
                    ny = ty;
                }
            }

            next_positions.push({ nx + ny, nx, ny });
        }

        int score, next_x, next_y;
        tie(score, next_x, next_y) = next_positions.top();
        cur_rabbit.x = next_x;
        cur_rabbit.y = next_y;
        cur_rabbit.j++;

        total_score += score;
        sub_score[id] += score;

        rabbits[id] = cur_rabbit;
        pq.push(cur_rabbit);
        is_runned[id] = true;
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
    int min_sub = (int)1e9;
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