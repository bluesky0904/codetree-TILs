#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 15;
const int MAXM = 30;
const int INF = 1e9;

int n, m; // 격자의 크기 n, 사람의 수 m

// 이미 사람들이 도착한 편의점이나 출발한 적이 있는 베이스캠프의 경우 움직일 때 절대 지나갈 수 없는 공간임을 유의
int base[MAXN + 10][MAXN + 10]; // 베이스캠프
pair<int, int> player[MAXM + 10];
pair<int, int> conv[MAXM + 10]; // 편의점

int dist[MAXN + 10][MAXN + 10];

int dx[4] = { -1,0,0,1 };
int dy[4] = { 0,-1,1,0 };

void print() {
    cout << "base" << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << base[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    cout << "conv" << "\n";
    for (int i = 1; i <= m; i++) {
        cout << i << " : " << conv[i].first << " " << conv[i].second << "\n";
    }
    cout << "\n";

    cout << "player" << "\n";
    for (int i = 1; i <= m; i++) {
        cout << i << " : " << player[i].first << " " << player[i].second << "\n";
    }
    cout << "\n";
}

bool isOver() {
    for (int i = 1; i <= m; i++) {
        if (player[i] != conv[i]) return false;
    }
    return true;
}

bool inRange(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

void BFS(int idx) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = -1;
        }
    }
    queue<pair<int, int>> q;

    q.push(conv[idx]);
    dist[conv[idx].first][conv[idx].second] = 0;
    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nx = cx + dx[dir];
            int ny = cy + dy[dir];

            if (inRange(nx, ny) && dist[nx][ny] == -1 && base[nx][ny] != -1) {
                q.push({ nx, ny });
                dist[nx][ny] = dist[cx][cy] + 1;
            }
        }
    }

    /*
    cout << "dist" << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";       
    */
}

void moveAllPlayer() {
    vector<pair<int, int>> v;

    for (int i = 1; i <= m; i++) {
        if (player[i].first == -1 && player[i].second == -1) continue;
        if (player[i] == conv[i]) continue;

        BFS(i);
        int min_dist = INF;
        int min_dir = -1;

        for (int dir = 0; dir < 4; dir++) {
            int nx = player[i].first + dx[dir]; // 방향을 안 더해줬네 뭐지
            int ny = player[i].second + dy[dir]; // 방향을 안 더해줬네 뭐지

            if (inRange(nx, ny) && dist[nx][ny] != -1 && min_dist > dist[nx][ny]) {
                min_dist = dist[nx][ny];
                min_dir = dir;
            }
        }

        player[i].first += dx[min_dir];
        player[i].second += dy[min_dir];
        if (player[i] == conv[i]) v.push_back(player[i]);
    }

    for (int i = 0; i < (int)v.size(); i++) {
        base[v[i].first][v[i].second] = -1;
    }
}

void goBase(int t) {
    if (t > m) return;

    BFS(t);
    int min_dist = INF;
    int min_x = -1;
    int min_y = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (base[i][j] == 1 && dist[i][j] != -1 && dist[i][j] < min_dist) { // 도달가능한 베이스여야지!
                min_dist = dist[i][j];
                min_x = i;
                min_y = j;
            }
        }
    }

    player[t] = { min_x, min_y };
    base[min_x][min_y] = -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("sample_input.txt", "r", stdin);
    
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> base[i][j];
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        conv[i] = { x, y };
        player[i] = { -1, -1 };
    }

    //print();

    // 어떤 함수부터 구현할건지도 생각. 디버그하기 쉬워야한다!
    for (int turn = 1;; turn++) {
        //cout << "turn : " << turn << "\n";

        //cout << "moveAllPlayer" << "\n";
        moveAllPlayer();
        if (isOver()) {
            cout << turn << "\n";
            return 0;
        }
        //print();

        //cout << "goBase" << "\n";
        goBase(turn);
        //print();
    }
}