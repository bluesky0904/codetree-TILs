/*
체스판 : L x L, 좌상단 (1, 1)
    빈칸 : 0
        함정 : 1
            벽 : 체스판 밖도 벽으로 간주 : 2

                기사 :위치 (r, c), (r, c)를 좌측 상단으로 하며 h(높이) x w(너비) 크기의 직사각형 방패, 체력k (삭제 여부)

                (1) 기사 이동
                상하좌우 중 하나로 한 칸 이동할 수 있음
                만약 이동하려는 위치에 다른 기사가 있다면 그 기사도 함께 연쇄적으로 한 칸 밀려남
                그 옆에 또 기사가 있다면 연쇄적으로 한 칸씩 밀려남
                하지만 만약 기사가 이동하려는 방향의 끝에 벽이 있다면 모든 기사는 이동할 수 없게 됨
                또, 체스판에서 사라진 기사에게 명령을 내리면 아무런 반응이 없게 됨

                (2) 대결 대미지
                명령을 받은 기사가 다른 기사를 밀치게 되면, 밀려난 기사들은 피해를 입게 됨.
                이때 각 기사들은 해당 기사가 이동한 곳에서 w x h 직사각형 내에 놓여 있는 함정의 수만큼만 피해를 입게 됨
                각 기사마다 피해를 받은 만큼 체력이 깎이게 되며, 현재 체력 이상의 대미지를 받을 경우 기사는 체스판에서 사라지게 됨
                단, 명령을 받은 기사는 피해를 입지 않으며, 기사들은 모두 밀린 이후에 대미지를 입게 됨
                밀렸더라도 밀쳐진 위치에 함정이 전혀 없다면 그 기사는 피해를 전혀 입지 않게 됨에 유의

                Q번에 걸쳐 왕의 명령이 주어졌을 때, Q번의 대결이 모두 끝난 후 생존한 기사들이 총 받은 대미지의 합을 출력
                */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

const int MAXL = 40;
const int MAXN = 30;

int L, N, Q;
int grid[MAXL + 10][MAXL + 10];

int r[MAXN + 10];
int c[MAXN + 10];
int nr[MAXN + 10];
int nc[MAXN + 10];
int h[MAXN + 10];
int w[MAXN + 10];
int def_k[MAXN + 10];
int k[MAXN + 10];

int print_grid[MAXL + 10][MAXL + 10];
bool visited[MAXN + 10];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void print() {
    cout << "knight info" << "\n";
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            print_grid[i][j] = 0;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (k[i] == 0) continue;
        for (int x = r[i]; x < r[i] + h[i]; x++) {
            for (int y = c[i]; y < c[i] + w[i]; y++) {
                print_grid[x][y] = i;
            }
        }
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            cout << print_grid[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    cout << "grid" << "\n";
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    cout << "k" << "\n";
    for (int i = 1; i <= N; i++) {
        cout << k[i] << " ";
    }
    cout << "\n";
}

bool inRange(int x, int y) {
    return (x >= 0 && x < L && y >= 0 && y < L);
}

bool isOverlapped(int id1, int id2) {
    return !((nc[id1] + w[id1] <= nc[id2]) || (nc[id2] + w[id2] <= nc[id1]) || (nr[id1] + h[id1] <= nr[id2]) || (nr[id2] + h[id2] <= nr[id1])); // 등호 안 넣었네
}

bool isWall(int id) {
    for (int x = nr[id]; x < nr[id] + h[id]; x++) {
        for (int y = nc[id]; y < nc[id] + w[id]; y++) {
            if (!inRange(x, y) || grid[x][y] == 2) return true;
        }
    }
    return false;
}

bool isPossible(int id, int dir) {
    for (int i = 1; i <= N; i++) {
        nr[i] = r[i];
        nc[i] = c[i];
    }

    nr[id] += dx[dir];
    nc[id] += dy[dir];

    queue<int> q;
    for (int i = 1; i <= N; i++) visited[i] = false;

    q.push(id);
    visited[id] = true;
    while (!q.empty()) {
        int cx = q.front();
        q.pop();

        if (isWall(cx)) return false;

        for (int i = 1; i <= N; i++) {
            if (i == cx) continue;
            if (k[i] == 0) continue;
            if (visited[i]) continue;
            if (!isOverlapped(cx, i)) continue;

            nr[i] += dx[dir];
            nc[i] += dy[dir];
            q.push(i);
            visited[i] = true;
        }
    }

    return true;
}

void getDamage(int id) {
    for (int i = 1; i <= N; i++) {
        if (k[i] == 0) continue;
        if (i == id) continue;
        if (!visited[i]) continue; // 방문 안한 사람 cut

        int cnt = 0;
        for (int x = r[i]; x < r[i] + h[i]; x++) { // 여기서 인덱스 주의
            for (int y = c[i]; y < c[i] + w[i]; y++) {
                if (grid[x][y] == 1) cnt++;
            }
        }

        k[i] -= cnt;
        if (k[i] < 0) k[i] = 0;
    }
}

void moveKnight(int id, int dir) {
    if (k[id] == 0) return;
    if (!isPossible(id, dir)) return;

    for (int i = 1; i <= N; i++) {
        r[i] = nr[i];
        c[i] = nc[i];
    }

   // cout << "getDamage" << "\n";
    getDamage(id);
    //print();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("sample_input.txt", "r", stdin);

    cin >> L >> N >> Q;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 1; i <= N; i++) {
        cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
        r[i]--;
        c[i]--;
        def_k[i] = k[i];
    }

    //print();
    for (int turn = 1; turn <= Q; turn++) {
        //cout << "turn : " << turn << "\n";

        int i, d; cin >> i >> d;
       // cout << "moveKnight" << "\n";
        moveKnight(i, d);
       // print();
    }

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        if (k[i] > 0) ans += (def_k[i] - k[i]);
    }
    cout << ans << "\n";
    return 0;
}
