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
    int id, row, col, jump_cnt;
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

// 우선순위 큐 정렬 비교 (최소 우선순위 기준)
struct CompareMin {
    bool operator()(const Rabbit& a, const Rabbit& b) const {
        if (a.jump_cnt != b.jump_cnt) return a.jump_cnt > b.jump_cnt;
        if (a.row + a.col != b.row + b.col) return a.row + a.col > b.row + b.col;
        if (a.row != b.row) return a.row > b.row;
        if (a.col != b.col) return a.col > b.col;
        return a.id > b.id;
    }
};

// 우선순위 큐 정렬 비교 (최대 우선순위 기준)
struct CompareMax {
    bool operator()(const Rabbit& a, const Rabbit& b) const {
        if (a.row + a.col != b.row + b.col) return a.row + a.col < b.row + b.col;
        if (a.row != b.row) return a.row < b.row;
        if (a.col != b.col) return a.col < b.col;
        return a.id < b.id;
    }
};


priority_queue<Rabbit, vector<Rabbit>, CompareMin> pq;

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

    for (auto& it : rabbits) {
        pq.push(it.second);
    }
}

void start_race() {
    int k, s;
    cin >> k >> s;

    
   

    priority_queue<Rabbit, vector<Rabbit>, CompareMax> max_pq;
    while (k--) {
        Rabbit cur_rabbit = pq.top();
        pq.pop();

        int id = cur_rabbit.id;
        int cur_row = cur_rabbit.row;
        int cur_col = cur_rabbit.col;

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
        cur_rabbit.row = next_x;
        cur_rabbit.col = next_y;
        cur_rabbit.jump_cnt++;

        total_score += score;
        sub_score[id] += score;

        rabbits[id] = cur_rabbit;
        pq.push(cur_rabbit);
        max_pq.push(cur_rabbit);
    }

    sub_score[max_pq.top().id] -= s;
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
    ios::sync_with_stdio(0);
    cin.tie(0);

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