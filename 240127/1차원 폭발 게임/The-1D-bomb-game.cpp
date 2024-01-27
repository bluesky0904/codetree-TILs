#include <iostream>
#include <vector>
using namespace std;

void Simulate(vector<int>& bombs, int M) {
    while (true) {
        int cnt = 1;
        bool exploded = false;
        for (int i = 0; i < static_cast<int>(bombs.size()) - 1; ++i) {
            if (bombs[i] == bombs[i + 1]) {
                cnt++;
            } else {
                if (cnt >= M) {
                    // 폭발 발생
                    exploded = true;
                    for (int j = i; j > i - cnt; --j) {
                        bombs[j] = 0;
                    }
                }
                cnt = 1;
            }
        }

        // 마지막 연속된 폭탄 그룹 처리
        if (cnt >= M) {
            exploded = true;
            for (int j = static_cast<int>(bombs.size()) - 1; j > static_cast<int>(bombs.size()) - 1 - cnt; --j) {
                bombs[j] = 0;
            }
        }

        if (!exploded) break;

        // 0이 아닌 요소를 유지하며 벡터 재구성
        vector<int> tmp;
        for (int i = 0; i < static_cast<int>(bombs.size()); ++i) {
            if (bombs[i] != 0) tmp.push_back(bombs[i]);
        }
        bombs = tmp;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    cin >> N >> M;
    vector<int> bombs(N);
    for (int i = 0; i < N; i++) {
        cin >> bombs[i];
    }

    Simulate(bombs, M);

    cout << bombs.size() << "\n";
    for (int i = 0; i < bombs.size(); i++) {
        cout << bombs[i] << "\n";
    }
}