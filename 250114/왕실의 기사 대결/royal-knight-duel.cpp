#include <iostream>
#include <queue>
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

// 수정된 충돌 판정 함수
bool IsIntersect(int idx1, int idx2) {
    return !(nr[idx1] + h[idx1] - 1 < nr[idx2] || nr[idx2] + h[idx2] - 1 < nr[idx1] || 
             nc[idx1] + w[idx1] - 1 < nc[idx2] || nc[idx2] + w[idx2] - 1 < nc[idx1]);
}

// 이동 가능 여부 확인
bool MovePossible(int idx, int d) {
    int new_r = r[idx] + dx[d], new_c = c[idx] + dy[d];

    // 체스판 범위 벗어나는 경우
    if (new_r < 1 || new_r + h[idx] - 1 > l || new_c < 1 || new_c + w[idx] - 1 > l) 
        return false;

    // 벽(값이 2) 확인
    for (int i = new_r; i < new_r + h[idx]; i++) {
        for (int j = new_c; j < new_c + w[idx]; j++) {
            if (grid[i][j] == 2) return false;
        }
    }

    return true;
}

// 피해 계산
void GetDamage(int idx) {
    int cnt = 0;
    for (int i = nr[idx]; i < nr[idx] + h[idx]; i++) { // 이동 후 좌표 기준
        for (int j = nc[idx]; j < nc[idx] + w[idx]; j++) {
            if (grid[i][j] == 1) cnt++;
        }
    }

    k[idx] -= cnt;
    if (k[idx] < 0) k[idx] = 0;
}

// 기사 이동 및 피해 처리
void MoveKnight(int idx, int d) {
    fill(visited, visited + n + 1, false);
    fill(participate, participate + n + 1, false);

    queue<int> q;

    // 현재 위치를 복사
    for (int i = 1; i <= n; i++) {
        nr[i] = r[i];
        nc[i] = c[i];
    }

    q.push(idx);
    visited[idx] = true;

    while (!q.empty()) {
        int cx = q.front(); q.pop();

        // 이동 가능 여부 확인
        if (!MovePossible(cx, d)) return;
        
        nr[cx] += dx[d];
        nc[cx] += dy[d];
        participate[cx] = true;

        // 충돌하는 기사 추가 처리
        for (int i = 1; i <= n; i++) {
            if (i == cx) continue;
            if (!visited[i] && IsIntersect(cx, i)) {
                q.push(i);
                visited[i] = true;
            }
        }
    }

    // 위치 갱신
    for (int i = 1; i <= n; i++) {
        if (!participate[i]) continue;
        r[i] = nr[i];
        c[i] = nc[i];
    }

    // 피해 계산
    for (int i = 1; i <= n; i++) {
        if (i == idx || !participate[i]) continue;
        GetDamage(i);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> l >> n >> q;

    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= l; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
        ori_k[i] = k[i];
    }

    while (q--) {
        int idx, d; cin >> idx >> d;
        if (k[idx] == 0) continue; // 이미 체력이 0인 기사 제외
        MoveKnight(idx, d);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (k[i] == 0) continue; // 체력이 0인 기사 제외
        ans += (ori_k[i] - k[i]);
    }

    cout << ans << "\n";
    return 0;
}
