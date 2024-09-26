#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define MAX_M 30
#define DIR_NUM 4

int n, m, k;
vector<int> grid[MAX_N + 1][MAX_N + 1];  // 각 격자에 있는 총의 리스트
int collide_idx;  // 충돌한 플레이어의 인덱스

// 플레이어 구조체
struct Player {
    int num, x, y, d, s, g;  // 번호, 위치(x, y), 방향(d), 초기 능력치(s), 들고 있는 총(g)
};

Player players[MAX_M + 1];  // 플레이어 배열
int point[MAX_M + 1];  // 각 플레이어의 포인트

// 방향 (↑, →, ↓, ←)
int dx[DIR_NUM] = { -1, 0, 1, 0 };
int dy[DIR_NUM] = { 0, 1, 0, -1 };

// 범위 체크
bool InRange(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

// 다음 위치와 방향 계산
tuple<int, int, int> GetNextPos(int x, int y, int d) {
    int nx = x + dx[d], ny = y + dy[d], nd = d;
    if (InRange(nx, ny)) {
        return make_tuple(nx, ny, nd);
    } else {
        // 범위를 벗어나면 정반대 방향으로 변경
        nd = (d + 2) % 4;
        nx = x + dx[nd], ny = y + dy[nd];
        return make_tuple(nx, ny, nd);
    }
}

// 해당 위치에 플레이어가 있는지 확인
bool IsPlayer(int x, int y) {
    for (int i = 1; i <= m; i++) {
        if (players[i].x == x && players[i].y == y) {
            collide_idx = i;
            return true;
        }
    }
    return false;
}

// 패배한 플레이어 이동
void LoserGo(int loser) {
    int x = players[loser].x, y = players[loser].y, d = players[loser].d;
    grid[x][y].push_back(players[loser].g);  // 패배자가 총을 내려놓음
    players[loser].g = 0;
    
    int nx = x + dx[d], ny = y + dy[d], nd = d;
    
    // 경계 밖이거나 다른 플레이어가 있으면 방향을 회전하여 빈칸을 찾음
    if (!InRange(nx, ny) || IsPlayer(nx, ny)) {
        for (int dir = 1; dir <= 3; dir++) {
            nx = x + dx[(d + dir) % 4], ny = y + dy[(d + dir) % 4], nd = (d + dir) % 4;
            if (InRange(nx, ny) && !IsPlayer(nx, ny)) {
                players[loser].x = nx; players[loser].y = ny; players[loser].d = nd;
                break;
            }
        }
    } else {
        players[loser].x = nx; players[loser].y = ny; players[loser].d = nd;
    }
    
    // 이동한 칸에 총이 있으면 가장 강한 총을 획득
    if (!grid[nx][ny].empty()) {
        sort(grid[nx][ny].begin(), grid[nx][ny].end());
        players[loser].g = grid[nx][ny].back();
        grid[nx][ny].pop_back();
    }
}

// 승리한 플레이어 총 획득
void WinnerGo(int winner) {
    int x = players[winner].x, y = players[winner].y;
    
    if (!grid[x][y].empty()) {
        sort(grid[x][y].begin(), grid[x][y].end());
        
        // 총을 가지고 있으면 더 강한 총을 선택
        if (players[winner].g > 0) {
            grid[x][y].push_back(players[winner].g);
            players[winner].g = grid[x][y].back();
            grid[x][y].pop_back();
        } else {
            // 총이 없으면 가장 강한 총을 획득
            players[winner].g = grid[x][y].back();
            grid[x][y].pop_back();
        }
    }
}

// 플레이어 충돌 처리
void Collide(int p1, int p2) {
    int winner, loser;
    
    // 총과 초기 능력치를 합산하여 승자를 결정
    if (players[p1].s + players[p1].g > players[p2].s + players[p2].g) {
        winner = p1; loser = p2;
    } else if (players[p1].s + players[p1].g == players[p2].s + players[p2].g) {
        // 공격력이 같으면 초기 능력치로 승부
        if (players[p1].s > players[p2].s) {
            winner = p1; loser = p2;
        } else {
            winner = p2; loser = p1;
        }
    } else {
        winner = p2; loser = p1;
    }
    
    // 승자는 포인트 획득
    point[winner] += (players[winner].s + players[winner].g) - (players[loser].s + players[loser].g);
    
    // 패배자 이동
    LoserGo(loser);
    
    // 승리자는 총 획득
    WinnerGo(winner);
}

// 모든 플레이어 이동 처리
void MoveAll() {
    for (int i = 1; i <= m; i++) {
        int nx, ny, nd;
        tie(nx, ny, nd) = GetNextPos(players[i].x, players[i].y, players[i].d);
        
        // 이동한 곳에 플레이어가 없는 경우
        if (!IsPlayer(nx, ny)) {
            players[i].x = nx; players[i].y = ny; players[i].d = nd;
            
            // 총이 있으면 획득
            if (!grid[nx][ny].empty()) {
                sort(grid[nx][ny].begin(), grid[nx][ny].end());
                if (players[i].g > 0) {
                    grid[nx][ny].push_back(players[i].g);
                    players[i].g = grid[nx][ny].back();
                    grid[nx][ny].pop_back();
                } else {
                    players[i].g = grid[nx][ny].back();
                    grid[nx][ny].pop_back();
                }
            }
        }
        // 이동한 곳에 다른 플레이어가 있는 경우
        else {
            Collide(i, collide_idx);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    // 입력 처리
    cin >> n >> m >> k;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x; cin >> x;
            if (x > 0) grid[i][j].push_back(x);
        }
    }
    
    for (int i = 1; i <= m; i++) {
        Player p;
        int x, y, d, s; cin >> x >> y >> d >> s;
        p.num = i;  p.x = x; p.y = y; p.d = d; p.s = s; p.g = 0;
        players[i] = p;
    }
    
    // k 라운드 동안 게임 진행
    while (k--) {
        MoveAll();
    }
    
    // 각 플레이어의 포인트 출력
    for (int i = 1; i <= m; i++) {
        cout << point[i] << ' ';
    }
    
    return 0;
}