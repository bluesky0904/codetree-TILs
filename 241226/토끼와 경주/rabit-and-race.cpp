#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <unordered_map>
using namespace std;

#define DIR_NUM 4

struct Rabbit {
    int id, row, col, jump_cnt;
};

int n, m, p;
unordered_map<int, Rabbit> rabbits;
unordered_map<int, int> stride;
unordered_map<int, int> sub_score;
int total_score = 0;

int dx[DIR_NUM] = {-1, 0, 1, 0};
int dy[DIR_NUM] = {0, 1, 0, -1};

bool in_range(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

// 우선순위 큐 정렬 기준 (최소 우선순위 기준)
struct CompareMin {
    bool operator()(const Rabbit& a, const Rabbit& b) const {
        if (a.jump_cnt != b.jump_cnt) return a.jump_cnt > b.jump_cnt;
        if (a.row + a.col != b.row + b.col) return a.row + a.col > b.row + b.col;
        if (a.row != b.row) return a.row > b.row;
        if (a.col != b.col) return a.col > b.col;
        return a.id > b.id;
    }
};

// 우선순위 큐 정렬 기준 (최대 우선순위 기준)
struct CompareMax {
    bool operator()(const Rabbit& a, const Rabbit& b) const {
        if (a.row + a.col != b.row + b.col) return a.row + a.col < b.row + b.col;
        if (a.row != b.row) return a.row < b.row;
        if (a.col != b.col) return a.col < b.col;
        return a.id < b.id;
    }
};

void race_ready() {
    cin >> n >> m >> p;
    for (int i = 1; i <= p; i++) {
        int pid, d;
        cin >> pid >> d;
        rabbits[pid] = {pid, 1, 1, 0};
        stride[pid] = d;
        sub_score[pid] = 0;
    }
}

void start_race() {
    int k, s;
    cin >> k >> s;

    priority_queue<Rabbit, vector<Rabbit>, CompareMin> pq;
    for (auto& it : rabbits) {
        pq.push(it.second);
    }

    unordered_map<int, bool> picked;
    while (k--) {
        Rabbit cur_rabbit = pq.top();
        pq.pop();

        int id = cur_rabbit.id;
        int cur_row = cur_rabbit.row;
        int cur_col = cur_rabbit.col;

        // 이동 가능한 위치 계산
        int best_score = -1, best_row = -1, best_col = -1;
        for (int dir = 0; dir < DIR_NUM; dir++) {
            int nx = cur_row, ny = cur_col;
            int cdir = dir;

            for (int i = 0; i < stride[id]; i++) {
                int tx = nx + dx[cdir];
                int ty = ny + dy[cdir];
                if (!in_range(tx, ty)) {
                    cdir = (cdir + 2) % 4; // 방향 반전
                }
                nx += dx[cdir];
                ny += dy[cdir];
            }

            int score = nx + ny;
            if (score > best_score || (score == best_score && (nx > best_row || (nx == best_row && ny > best_col)))) {
                best_score = score;
                best_row = nx;
                best_col = ny;
            }
        }

        cur_rabbit.row = best_row;
        cur_rabbit.col = best_col;
        cur_rabbit.jump_cnt++;

        total_score += best_score;
        sub_score[id] += best_score;

        picked[id] = true;
        rabbits[id] = cur_rabbit;
        pq.push(cur_rabbit);
    }

    // 마지막 점수 계산
    Rabbit top_rabbit = {0, 0, 0, 0};
    for (auto& it : rabbits) {
        if (picked[it.first]) {
            Rabbit r = it.second;
            if (r.row + r.col > top_rabbit.row + top_rabbit.col ||
                (r.row + r.col == top_rabbit.row + top_rabbit.col && (r.row > top_rabbit.row || (r.row == top_rabbit.row && r.col > top_rabbit.col)))) {
                top_rabbit = r;
            }
        }
    }
    sub_score[top_rabbit.id] -= s;
}

void change_distance() {
    int pid, l;
    cin >> pid >> l;
    stride[pid] *= l;
}

void choose_best() {
    int min_sub = 1e9;
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
