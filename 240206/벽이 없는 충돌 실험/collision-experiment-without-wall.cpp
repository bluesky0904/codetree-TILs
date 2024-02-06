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
//            x    y    d    w   idx
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
    // 1. Marble vector에서 순회하며, nxtBoard에 업데이트한다.
        // 1.1 순회하며, vector도 업데이트하고, nxtBoard에는 값을 넣는다
        // 1.2 nxtBoard가 0이 아닌경우, ans = g_time
        // 1.3 무게 및 번호를 비교해서 nxtBoard를 업데이트한다
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
            // 무게 비교
            if(w > nxtBoard[nx][ny].X){
                nxtBoard[nx][ny] = {w, idx};
                // 번호 비교
            }else if(w == nxtBoard[nx][ny].X && idx > nxtBoard[nx][ny].Y){
                nxtBoard[nx][ny] = {w, idx};
            }
        }
    }
    marbles = tmp;
}

void Update(){
    // 2. Update된 Marble vector를 순회하며, nxtBoard와 비교한다
        // 2.1 tmp vector 하나 생성
        // 2.2 비교해서 같으면 nxtBoard를 {0,0}으로 초기화, tmp에 push_back
        // 2.3 다르면 continue;
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
    // // nxtBoard update
    // Clear();
    // 모든 board를 순회하며, marble nxt Board에 update O(B^2), Simulate가 B만큼 돌고 있어서, 
    // O(B^3)만큼 걸린다. B는 약 4*10^3 이므로, 64*10^9정도. 64억개정도의 명령어... 64초정도 걸리게 되는것이다. 이 방법은 포기.
    
    // MoveAll();
    // // nxtBoard를 탐색하며, board update
    // Update();
    
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