#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> bombs;

void Simulate() {
    while (true) {
        vector<int> tmp; // 임시 벡터
        bool exploded = false; // 폭발 발생 여부
        int cnt = 1;

        for (int i = 0; i < bombs.size(); i++) {
            // 연속된 같은 숫자 세기
            if (i < bombs.size() - 1 && bombs[i] == bombs[i + 1]) {
                cnt++;
            } else {
                // 폭발 기준에 도달하면 폭발 처리
                if (cnt >= M) {
                    exploded = true;
                    cnt = 1;
                    continue;
                }

                // 폭발하지 않은 경우 벡터에 추가
                while (cnt > 0) {
                    tmp.push_back(bombs[i - cnt + 1]);
                    cnt--;
                }
                cnt = 1;
            }
        }

        // 폭발이 발생하지 않았으면 종료
        if (!exploded) break;

        // bombs 벡터 업데이트
        bombs = tmp;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;

    bombs.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> bombs[i];
    }

    Simulate();

    cout << bombs.size() << "\n";
    for (int i = 0; i < bombs.size(); i++) {
        cout << bombs[i] << "\n";
    }
}