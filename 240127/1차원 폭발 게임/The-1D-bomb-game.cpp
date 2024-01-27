#include <iostream>
#include <vector>
using namespace std;

void Simulate(vector<int>& bombs, int M) {
    int write = 0; // 새로 쓸 위치를 추적하는 인덱스
    while (true) {
        int read = 0; // 읽을 위치를 추적하는 인덱스
        bool exploded = false;

        while (read < bombs.size()) {
            int start = read;
            while (read < bombs.size() && bombs[read] == bombs[start]) {
                read++;
            }

            int length = read - start;
            if (length >= M) {
                exploded = true;
            } else {
                while (start < read) {
                    bombs[write++] = bombs[start++];
                }
            }
        }

        if (!exploded) break;
        bombs.resize(write); // 벡터의 크기를 유효한 요소의 수에 맞추어 조정
        write = 0; // 다음 순회를 위해 쓰기 인덱스 초기화
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