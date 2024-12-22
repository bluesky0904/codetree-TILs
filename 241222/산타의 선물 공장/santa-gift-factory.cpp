#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX_M 10

using namespace std;

int n, m, q;

// 각 id별로 상자 무게를 저장합니다.
unordered_map<int, int> weight;

// id에 해당하는 상자의 nxt값과 prv값을 관리합니다.
// 0이면 없다는 뜻입니다.
unordered_map<int, int> prv, nxt;

// 각 벨트별로 head, tail id를 관리합니다.
// 0이면 없다는 뜻입니다.
int head[MAX_M], tail[MAX_M];

// 벨트가 망가졌는지를 표시합니다.
bool broken[MAX_M];

// 물건 별로 벨트 번호를 기입합니다.
// 벨트 번호가 0이면 사라진 것입니다.
unordered_map<int, int> belt_num;

// 공장 설립
void BuildFactory() {
    // 공장 정보를 입력받습니다.
    cin >> n >> m;
    vector<int> ids(n), ws(n);
    for(int i = 0; i < n; i++)
        cin >> ids[i];
    for(int i = 0; i < n; i++)
        cin >> ws[i];

    // id마다 무게를 관리합니다.
    for(int i = 0; i < n; i++)
        weight[ids[i]] = ws[i];
    
    // 벨트 별로 상자 목록을 넣어줍니다.
    int size = n / m;
    for(int i = 0; i < m; i++) {
        // head, tail을 설정해줍니다.
        head[i] = ids[i * size];
        tail[i] = ids[(i + 1) * size - 1];
        for(int j = i * size; j < (i + 1) * size; j++) {
            // 상자 ID마다 벨트 번호를 기입합니다.
            belt_num[ids[j]] = i + 1;

            // nxt, prv를 설정해줍니다.
            if(j < (i + 1) * size - 1) {
                nxt[ids[j]] = ids[j + 1];
                prv[ids[j + 1]] = ids[j];
            }
        }
    }
}

// Id에 해당하는 상자를 삭제합니다.
void RemoveId(int id, bool remove_belt) {
    int b_num = belt_num[id] - 1;
    // 벨트 번호를 제거해줍니다.
    if(remove_belt)
        belt_num[id] = 0;

    // 하나 남은 원소라면
    // head, tail이 사라지고 끝납니다.
    if(head[b_num] == tail[b_num])
        head[b_num] = tail[b_num] = 0;

    // 삭제 되는게 head라면
    // head만 변경되고 끝납니다.
    else if(id == head[b_num]) {
        int nid = nxt[id];
        head[b_num] = nid;
        prv[nid] = 0;
    }
    // 삭제 되는게 tail이라면
    // tail만 변경되고 끝납니다.
    else if(id == tail[b_num]) {
        int pid = prv[id];
        tail[b_num] = pid;
        nxt[pid] = 0;
    }
    // 중간에 있는 id가 삭제되는 것이라면
    // nxt, prv만 수선해줍니다.
    else {
        int pid = prv[id], nid = nxt[id];
        nxt[pid] = nid;
        prv[nid] = pid;
    }

    // nxt, prv값을 지워줍니다.
    nxt[id] = prv[id] = 0;
}

// target_id 바로 뒤에
// id를 추가합니다.
void PushId(int target_id, int id) {
    nxt[target_id] = id;
    prv[id] = target_id;

    // 만약 target_id가 tail이었다면
    // tail을 변경해줍니다.
    int b_num = belt_num[target_id] - 1;
    if(tail[b_num] == target_id)
        tail[b_num] = id;
}

// 물건 하차
void DropOff() {
    int w_max;
    cin >> w_max;

    // 각 벨트마다 보며
    // 첫 번째 상자를 열어봅니다.
    long long w_sum = 0;
    for(int i = 0; i < m; i++) {
        // 망가진 벨트라면 넘어갑니다.
        if(broken[i])
            continue;

        // 벨트의 head를 확인합니다.
        if(head[i] != 0) {
            int id = head[i];
            int w = weight[id];

            // 가장 앞에 있는 상자의 무게가 w_max 이하라면
            // 하차시키고 답에 더해줍니다.
            if(w <= w_max) {
                w_sum += w;

                // 하차를 진행합니다.
                RemoveId(id, true);
            }
            // 그렇지 않다면
            // 상자를 맨 뒤로 올려줍니다.
            else if(nxt[id] != 0) {
                // 제거해준 뒤
                RemoveId(id, false);
                
                // 맨 뒤에 push해줍니다.
                PushId(tail[i], id);
            }
        }
    }

    // 하차한 상자의 무게 합을 출력합니다.
    cout << w_sum << endl;
}

// 물건 제거
void Remove() {
    int r_id;
    cin >> r_id;

    // 이미 삭제된 상자라면
    // -1을 출력하고 패스합니다.
    if(belt_num[r_id] == 0) {
        cout << -1 << endl;
        return;
    }
        
    // 해당 상자를 제거합니다.
    RemoveId(r_id, true);
    cout << r_id << endl;
}

// 물건 확인
void Find() {
    int f_id;
    cin >> f_id;

    // 이미 삭제된 상자라면
    // -1을 출력하고 패스합니다.
    if(belt_num[f_id] == 0) {
        cout << -1 << endl;
        return;
    }

    // 해당 상자를 찾아
    // 이를 맨 앞으로 당겨줍니다.
    // head가 아닌 경우에만 유효합니다.
    int b_num = belt_num[f_id] - 1;
    if(head[b_num] != f_id) {
        int orig_tail = tail[b_num];
        int orig_head = head[b_num];

        // 새로 tail을 갱신해줍니다.
        int now_tail = prv[f_id];
        tail[b_num] = now_tail;
        nxt[now_tail] = 0;

        // 기존 tail의 nxt를 head로,
        // heda의 prv를 기존 tail로 만들어줍니다.
        nxt[orig_tail] = orig_head;
        prv[orig_head] = orig_tail;

        // 새로 head를 지정합니다.
        head[b_num] = f_id;
    }

    // 해당 ID의 belt 번호를 출력합니다.
    cout << b_num + 1 << endl;
}

// 벨트 고장
void BrokenBelt() {
    int b_num;
    cin >> b_num;

    b_num--;
    // 이미 망가져 있다면
    // -1을 출력하고 패스합니다.
    if(broken[b_num]) {
        cout << -1 << endl;
        return;
    }

    broken[b_num] = 1;

    // 만약 빈 벨트라면 패스합니다.
    if(head[b_num] == 0) {
        cout << b_num + 1 << endl;
        return;
    }

    // 오른쪽으로 돌면서
    // 아직 망가지지 않은 벨트 위로 상자를 전부 옮겨줍니다.
    int nxt_num = b_num;
    while(true) {
        nxt_num = (nxt_num + 1) % m;
        // 최초로 망가지지 않은 곳이 보이면
        if(!broken[nxt_num]) {
            // 만약 해당 벨트가 비어있다면
            // 그대로 옮겨줍니다.
            if(tail[nxt_num] == 0) {
                head[nxt_num] = head[b_num];
                tail[nxt_num] = tail[b_num];
            }
            else {
                // 해당 위치로 상자를 전부 옮겨줍니다.
                // head만 tail뒤에 붙여준 뒤
                PushId(tail[nxt_num], head[b_num]);
                // tail만 갈아껴주면 됩니다.
                tail[nxt_num] = tail[b_num];
            }

            // head부터 tail까지 보며
            // belt_num을 갱신해줍니다.
            int id = head[b_num];
            while(id != 0) {
                belt_num[id] = nxt_num + 1;
                id = nxt[id];
            }

            head[b_num] = tail[b_num] = 0;
            break;
        }
    }

    cout << b_num + 1 << endl;
}

int main() {
    // 입력:
    cin >> q;
    while(q--) {
        int q_type;
        cin >> q_type;
        if(q_type == 100)
            BuildFactory();
        else if(q_type == 200)
            DropOff();
        else if(q_type == 300)
            Remove();
        else if(q_type == 400)
            Find();
        else
            BrokenBelt();
    }
    return 0;
}