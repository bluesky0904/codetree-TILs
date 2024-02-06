#include <iostream>
#include <tuple>
#include <vector>

#define MAX_BOARD 4000
#define ASCII_NUM 128
#define MARBLE_NUM 100
#define X first
#define Y second

using namespace std;

pair<int, int> nxtBoard[MAX_BOARD+1][MAX_BOARD+1];
vector<tuple<int, int, int, int, int>> marbles;
vector<tuple<int, int, int, int, int>> tmp;
int mapper[ASCII_NUM];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int g_time;
int T,N,ans = -1;

bool InRange(int x, int y){
    return 0 <= x && x <= MAX_BOARD && 0 <= y && y <= MAX_BOARD;
}

void MoveAll(){
    vector<tuple<int, int, int, int, int>> tmp;
    int x, y, dir, w, idx;
    for(int i = 0 ; i < marbles.size() ; i++){
        tie(x, y, dir, w, idx) = marbles[i];
        int nx = x + dx[dir], ny = y + dy[dir];
        if(!InRange(nx, ny)) continue;
        tmp.push_back({nx, ny, dir, w, idx});
        if(nxtBoard[nx][ny].X == 0 && nxtBoard[nx][ny].Y == 0){
            nxtBoard[nx][ny] = {w, idx};
        }else{
            ans = g_time;
            if(w > nxtBoard[nx][ny].X){
                nxtBoard[nx][ny] = {w, idx};
            }else if(w == nxtBoard[nx][ny].X && idx > nxtBoard[nx][ny].Y){
                nxtBoard[nx][ny] = {w, idx};
            }
        }
    }
    marbles = tmp;
}

void Update(){
    tmp.clear();
    for(int i = 0 ; i < marbles.size() ; i++){
        int x, y, dir, w, idx;
        tie(x, y, dir, w, idx) = marbles[i];
        if(w == nxtBoard[x][y].X && idx == nxtBoard[x][y].Y){
            tmp.push_back({x, y, dir, w, idx});
            nxtBoard[x][y] = {0,0};
        }
    }
    marbles = tmp;
}

void Simulate(){
    MoveAll();
    Update();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    mapper['R'] = 0;
    mapper['D'] = 3;
    mapper['L'] = 2;
    mapper['U'] = 1;
    int x, y ,w;
    char d;
    while(T--){
        marbles.clear();
        cin >> N;
        ans = -1;
        for(int i = 1 ; i <= N ; i++){
            cin >> y >> x >> w >> d;
            x += 1000; y += 1000;
            x *= 2; y *= 2;
            marbles.push_back({x,y,mapper[d],w,i});
        }
        for(g_time = 1 ; g_time <= MAX_BOARD ; g_time++){
            Simulate();
        }
        cout << ans << '\n';
    }
    return 0;
}