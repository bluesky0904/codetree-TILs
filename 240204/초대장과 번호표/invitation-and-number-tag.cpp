#include <iostream>
#include <unordered_set>
#include <queue>
#include <vector>

using namespace std;

#define MAX_N 100000
#define MAX_G 250000

// 변수 선언
int n, g;
bool invited[MAX_N];
// 각 그룹마다 초대장을 받지 못한 사람들을 관리해줍니다.
unordered_set<int> groups[MAX_G];
// 각 사람이 어떤 그룹에 속하는지를 관리해줍니다.
vector<int> people_groups[MAX_N];
queue<int> q;
int ans;

int main() {
    // 입력:
    cin >> n >> g;

    for(int i = 0; i < g; i++) {
        int s, x;
        cin >> s;
        for(int j = 0; j < s; j++) {
            cin >> x; x--;
            groups[i].insert(x);
            people_groups[x].push_back(i);
        }
    }

    q.push(0);
    invited[0] = true;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        ans++;

        // x가 들어있는 그룹에서 x를 지웁니다.
        // hashset에는 그룹에서 초대받지 않은 인원만을 남깁니다.
        for(int i = 0; i < (int) people_groups[x].size(); i++) {
            int g_num = people_groups[x][i];

            // 해당 그룹에서 x를 지웁니다.
            groups[g_num].erase(x);
            // 초대받지 않은 인원이 한명밖에 없다면 초대합니다.
            if((int) groups[g_num].size() == 1) {
                int p_num = *(groups[g_num].begin());
                if(!invited[p_num]) {
                    invited[p_num] = true;
                    q.push(p_num);
                }
            }
        }
    }

    // 초대장을 받는 인원을 출력합니다.
    cout << ans;
    return 0;
}