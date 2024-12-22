#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// 전역 변수
vector<queue<pair<int, int>>> belts; // 벨트별 큐 (ID, 무게)
unordered_map<int, int> id_to_belt; // {ID: 벨트 번호}
vector<bool> broken_belts; // 벨트 고장 여부

// 공장 설립
void setup_factory(int n, int m, vector<int>& ids, vector<int>& weights) {
    belts.resize(m);
    broken_belts.resize(m, false);

    int items_per_belt = n / m;
    int idx = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < items_per_belt; ++j) {
            int id = ids[idx];
            int weight = weights[idx];
            belts[i].push({ id, weight });
            id_to_belt[id] = i;
            ++idx;
        }
    }
}

// 물건 하차
int unload_items(int w_max) {
    int total_weight = 0;

    for (int i = 0; i < belts.size(); ++i) {
        if (broken_belts[i]) continue; // 고장난 벨트는 건너뛴다
        if (!belts[i].empty() && belts[i].front().second <= w_max) {
            // 하차 조건 만족 시
            total_weight += belts[i].front().second;
            id_to_belt.erase(belts[i].front().first);
            belts[i].pop();
        }
        else if (!belts[i].empty()) {
            // 조건을 만족하지 않으면 뒤로 보낸다
            auto front = belts[i].front();
            belts[i].pop();
            belts[i].push(front);
        }
    }

    return total_weight;
}

// 물건 제거
int remove_item(int r_id) {
    if (id_to_belt.find(r_id) == id_to_belt.end()) return -1;

    int belt_idx = id_to_belt[r_id];
    queue<pair<int, int>> new_queue;

    while (!belts[belt_idx].empty()) {
        auto item = belts[belt_idx].front();
        belts[belt_idx].pop();
        if (item.first != r_id) {
            new_queue.push(item);
        }
    }

    belts[belt_idx] = new_queue;
    id_to_belt.erase(r_id);
    return r_id;
}

// 물건 확인
int find_item(int f_id) {
    if (id_to_belt.find(f_id) == id_to_belt.end()) return -1;

    int belt_idx = id_to_belt[f_id];
    queue<pair<int, int>> new_queue;

    while (!belts[belt_idx].empty()) {
        auto item = belts[belt_idx].front();
        belts[belt_idx].pop();
        if (item.first != f_id) {
            new_queue.push(item);
        }
        else {
            new_queue.push(item); // 해당 아이템을 앞으로 이동
            break;
        }
    }

    while (!belts[belt_idx].empty()) {
        new_queue.push(belts[belt_idx].front());
        belts[belt_idx].pop();
    }

    belts[belt_idx] = new_queue;
    return belt_idx + 1; // 1-based index
}

// 벨트 고장
int break_belt(int b_num) {
    if (broken_belts[b_num - 1]) return -1; // 이미 고장난 경우

    int idx = b_num - 1;
    broken_belts[idx] = true;

    queue<pair<int, int>> temp_items;

    // 고장난 벨트의 아이템을 이동할 벨트를 찾음
    for (int i = 1; i <= belts.size(); ++i) {
        int next_belt = (idx + i) % belts.size();
        if (!broken_belts[next_belt]) {
            while (!belts[idx].empty()) {
                temp_items.push(belts[idx].front());
                belts[idx].pop();
            }

            while (!temp_items.empty()) {
                auto item = temp_items.front();
                temp_items.pop();
                belts[next_belt].push(item);
                id_to_belt[item.first] = next_belt; // 새 위치 업데이트
            }

            break;
        }
    }

    return b_num;
}

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int cmd;
        cin >> cmd;

        if (cmd == 100) {
            int n, m;
            cin >> n >> m;
            vector<int> ids(n), weights(n);
            for (int j = 0; j < n; ++j) cin >> ids[j];
            for (int j = 0; j < n; ++j) cin >> weights[j];
            setup_factory(n, m, ids, weights);
        }
        else if (cmd == 200) {
            int w_max;
            cin >> w_max;
            cout << unload_items(w_max) << endl;
        }
        else if (cmd == 300) {
            int r_id;
            cin >> r_id;
            cout << remove_item(r_id) << endl;
        }
        else if (cmd == 400) {
            int f_id;
            cin >> f_id;
            cout << find_item(f_id) << endl;
        }
        else if (cmd == 500) {
            int b_num;
            cin >> b_num;
            cout << break_belt(b_num) << endl;
        }
    }

    return 0;
}