#include <iostream>
#include <queue>
#include <algorithm> // std::fill 사용을 위해 필요
using namespace std;

#define MAX_L 40
#define MAX_N 30
#define DIR_NUM 4

int l, n, q;
int grid[MAX_L + 1][MAX_L + 1];
bool visited[MAX_N + 1];
bool participate[MAX_N + 1];

int nr[MAX_L + 1], nc[MAX_L + 1];
int r[MAX_L + 1], c[MAX_L + 1];
int h[MAX_L + 1], w[MAX_L + 1];
int k[MAX_N + 1], ori_k[MAX_N + 1];

int dx[DIR_NUM] = { -1, 0, 1, 0 };
int dy[DIR_NUM] = { 0, 1, 0, -1 };

bool IsIntersect(int idx1, int idx2) {
    // 교차 여부를 정확히 확인
    bool row_overlap = (nr[idx1] <= nr[idx2] + h[idx2] - 1 && nr[idx2] <= nr[idx1] + h[idx1] - 1);
    bool col_overlap = (nc[idx1] <= nc[idx2] + w[idx2] - 1 && nc[idx2] <= nc[idx1] + w[idx1] - 1);
    return row_overlap && col_overlap;
}

bool MovePossible(int idx, int d) {
    int new_r = nr[idx] + dx[d];
    int new_c = nc[idx] + dy[d];

    if (new_r < 1 || new_r + h[idx] - 1 > l || new_c < 1 || new_c + w[idx] - 1 > l) {
        return false; // 체스판 경계 초과 확인
    }

    for (int i = new_r; i < new_r + h[idx]; i++) {
        for (int j = new_c; j < new_c + w[idx]; j++) {
            if (grid[i][j] == 2) return false; // 벽에 부딪히는지 확인
        }
    }

    return true;
}

void GetDamage(int idx) {
    int cnt = 0;
    for (int i = max(1, r[idx]); i <= min(l, r[idx] + h[idx] - 1); i++) {
        for (int j = max(1, c[idx]); j <= min(l, c[idx] + w[idx] - 1); j++) {
            if (grid[i][j] == 1) cnt++; // 함정의 수 계산
        }
    }
    k[idx] -= cnt;
    if (k[idx] < 0) k[idx] = 0;
}

void MoveKnight(int idx, int d) {
    fill(visited, visited + MAX_N + 1, false);
    fill(participate, participate + MAX_N + 1, false);

    queue<int> q;

    for (int i = 1; i <= n; i++) {
        nr[i] = r[i];
        nc[i] = c[i];
    }

    if (!MovePossible(idx, d)) return;
    nr[idx] += dx[d], nc[idx] += dy[d];

    q.push(idx);
    visited[idx] = true;
    while (!q.empty()) {
        int cx = q.front(); q.pop();

        for (int i = 1; i <= n; i++) {
            if (i == cx || visited[i]) continue;
            if (IsIntersect(cx, i)) {
                participate[i] = true;

                if (!MovePossible(i, d)) return;
                nr[i] += dx[d], nc[i] += dy[d];

                q.push(i);
                visited[i] = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!participate[i]) continue;
        r[i] = nr[i];
        c[i] = nc[i];
    }

    r[idx] = nr[idx];
    c[idx] = nc[idx];

    for (int i = 1; i <= n; i++) {
        if (!participate[i]) continue;
        GetDamage(i);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> l >> n >> q;

    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= l; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
        if (r[i] < 1 || r[i] + h[i] - 1 > l || c[i] < 1 || c[i] + w[i] - 1 > l) {
            cerr << "Invalid input for knight position or size.\n";
            return -1;
        }
        ori_k[i] = k[i];
    }

    while (q--) {
        int idx, d;
        cin >> idx >> d;
        if (k[idx] == 0) continue; // 체력이 0인 기사는 무시
        MoveKnight(idx, d);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (k[i] == 0) continue; // 사라진 기사는 제외
        ans += (ori_k[i] - k[i]);
    }

    cout << ans << "\n";
    return 0;
}