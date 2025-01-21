#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define MAX_M 30
#define DIR_NUM 4

int n, m, k;
vector<int> grid[MAX_N + 1][MAX_N + 1]; // 총 위치
pair<int, int> p_pos[MAX_M + 1];        // 플레이어 위치
int p_dir[MAX_M + 1];                   // 플레이어 방향
int p_power[MAX_M + 1];                 // 플레이어 초기 능력치
int g_power[MAX_M + 1];                 // 플레이어 총 공격력
int p_point[MAX_M + 1];                 // 플레이어 포인트

int dx[DIR_NUM] = { -1, 0, 1, 0 };
int dy[DIR_NUM] = { 0, 1, 0, -1 };

bool inRange(int x, int y) {
    return (1 <= x && x <= n && 1 <= y && y <= n);
}

void movePlayer(int idx) {
    int cx = p_pos[idx].first, cy = p_pos[idx].second, dir = p_dir[idx];
    int nx = cx + dx[dir], ny = cy + dy[dir];

    // 격자 범위를 벗어나면 방향 반대
    if (!inRange(nx, ny)) {
        dir = (dir + 2) % DIR_NUM;
        nx = cx + dx[dir], ny = cy + dy[dir];
    }

    p_pos[idx] = { nx, ny };
    p_dir[idx] = dir;
}

int findOpponent(int idx) {
    for (int i = 1; i <= m; i++) {
        if (i != idx && p_pos[i] == p_pos[idx]) {
            return i;
        }
    }
    return -1;
}

void handleLoser(int loser) {
    int x = p_pos[loser].first, y = p_pos[loser].second, dir = p_dir[loser];

    // 현재 총을 격자에 내려놓음
    if (g_power[loser] > 0) {
        grid[x][y].push_back(g_power[loser]);
        g_power[loser] = 0;
    }

    // 빈칸을 찾아 이동
    for (int cnt = 0; cnt < DIR_NUM; cnt++) {
        int nd = (dir + cnt) % DIR_NUM;
        int nx = x + dx[nd], ny = y + dy[nd];
        if (inRange(nx, ny) && findOpponent(loser) == -1) {
            p_pos[loser] = { nx, ny };
            p_dir[loser] = nd;

            if (!grid[nx][ny].empty()) {
                sort(grid[nx][ny].begin(), grid[nx][ny].end());
                g_power[loser] = grid[nx][ny].back();
                grid[nx][ny].pop_back();
            }
            return;
        }
    }
}

void handleWinner(int winner) {
    int x = p_pos[winner].first, y = p_pos[winner].second;

    // 총을 획득하거나 교체
    if (!grid[x][y].empty()) {
        if (g_power[winner] > 0) {
            grid[x][y].push_back(g_power[winner]);
        }
        sort(grid[x][y].begin(), grid[x][y].end());
        g_power[winner] = grid[x][y].back();
        grid[x][y].pop_back();
    }
}

void resolveCollision(int idx1, int idx2) {
    int winner, loser;

    int power1 = p_power[idx1] + g_power[idx1];
    int power2 = p_power[idx2] + g_power[idx2];

    if (power1 > power2 || (power1 == power2 && p_power[idx1] > p_power[idx2])) {
        winner = idx1;
        loser = idx2;
    }
    else {
        winner = idx2;
        loser = idx1;
    }

    p_point[winner] += abs(power1 - power2);
    handleLoser(loser);
    handleWinner(winner);
}

void moveAllPlayers() {
    for (int i = 1; i <= m; i++) {
        movePlayer(i);

        int opponent = findOpponent(i);
        if (opponent != -1) {
            resolveCollision(i, opponent);
        }
        else {
            int x = p_pos[i].first, y = p_pos[i].second;

            if (!grid[x][y].empty()) {
                if (g_power[i] > 0) {
                    grid[x][y].push_back(g_power[i]);
                }
                sort(grid[x][y].begin(), grid[x][y].end());
                g_power[i] = grid[x][y].back();
                grid[x][y].pop_back();
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int g; cin >> g;
            if (g > 0) {
                grid[i][j].push_back(g);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y, d, s;
        cin >> x >> y >> d >> s;
        p_pos[i] = { x, y };
        p_dir[i] = d;
        p_power[i] = s;
        g_power[i] = 0;
        p_point[i] = 0;
    }

    for (int t = 0; t < k; t++) {
        moveAllPlayers();
    }

    for (int i = 1; i <= m; i++) {
        cout << p_point[i] << " ";
    }
    cout << "\n";

    return 0;
}
