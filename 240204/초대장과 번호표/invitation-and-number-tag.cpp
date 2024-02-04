#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, G;
    cin >> N >> G;

    vector<unordered_set<int>> groups(G);
    for (int i = 0; i < G; i++) {
        int groupSize;
        cin >> groupSize;
        while (groupSize--) {
            int person;
            cin >> person;
            groups[i].insert(person);
        }
    }

    unordered_set<int> invited{1}; // 1번 사람은 무조건 초대장을 받음
    bool updated = true;

    // 새로운 사람이 초대장을 받을 때까지 반복
    while (updated) {
        updated = false;
        for (auto& group : groups) {
            int countNotInvited = 0; // 초대장을 받지 않은 사람 수
            int lastNotInvited = -1; // 마지막으로 초대장을 받지 않은 사람
            for (int person : group) {
                if (invited.find(person) == invited.end()) {
                    countNotInvited++;
                    lastNotInvited = person;
                }
            }
            if (countNotInvited == 1) { // 초대장을 받지 않은 사람이 한 명이라면, 그 사람도 초대장을 받아야 함
                if (invited.insert(lastNotInvited).second) {
                    updated = true;
                }
            }
        }
    }

    cout << invited.size() << "\n";
}