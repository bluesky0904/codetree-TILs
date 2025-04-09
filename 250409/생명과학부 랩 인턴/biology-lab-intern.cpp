#include <iostream>
#include <tuple>

#define MAX_NUM 100
#define DIR_NUM 4
#define BLANK make_tuple(-1, -1, -1)

using namespace std;

int n, m, k;

tuple<int, int, int> mold[MAX_NUM][MAX_NUM];
tuple<int, int, int> next_mold[MAX_NUM][MAX_NUM];

int ans;

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

void Collect(int col) {
    for(int row = 0; row < n; row++)
        if(mold[row][col] != BLANK) {
            int mold_size;
            tie(mold_size, ignore, ignore) = mold[row][col];
            
            ans += mold_size;
            mold[row][col] = BLANK;
            break;
        }
}

tuple<int, int, int> GetNextPos(int x, int y, int dist, int move_dir) {
    // 문제에서 주어진 순서인 위, 아래, 오른쪽, 왼쪽 순으로 적어줍니다. 
    int dx[DIR_NUM] = {-1, 1, 0, 0};
    int dy[DIR_NUM] = {0, 0, 1, -1};
    
    // dist번 한 칸씩 이동하면 됩니다.
    while(dist--) {
        int next_x = x + dx[move_dir], next_y = y + dy[move_dir];
        // 현재 방향으로 이동했다 했을 때
        // 만약 격자를 벗어나지 않는다면, 그대로 이동합니다.
        if(InRange(next_x, next_y))
            x = next_x, y = next_y;
        // 만약 격자를 벗어나게 된다면
        // 방향을 반대로 바꾸고 한 칸 이동하면 됩니다.
        else {
            move_dir = (move_dir % 2 == 0) ? (move_dir + 1) : (move_dir - 1);
            x = x + dx[move_dir]; y = y + dy[move_dir];
        }
    }
    
    return make_tuple(x, y, move_dir);
}

// (x, y) 위치에 있는 곰팡이를 이동시킵니다.
void Move(int x, int y) {
    int mold_size, dist, move_dir;
    tie(mold_size, dist, move_dir) = mold[x][y];
    
    int next_x, next_y, next_dir;
    tie(next_x, next_y, next_dir) = GetNextPos(x, y, dist, move_dir);
    
    tuple<int, int, int> new_mold = make_tuple(mold_size, dist, next_dir);
    
    // 현재 곰팡이의 크기가 해당 위치에 있던 것 보다 더 큰 경우에만
    // 곰팡이 정보를 적어줍니다.
    // 그렇지 않은 경우라면 충돌시 사라지게 될 곰팡이이므로
    // 무시하면 됩니다.
    if(new_mold > next_mold[next_x][next_y])
        next_mold[next_x][next_y] = new_mold;
}

void MoveAll() {
    // next_mold 값을 전부 빈칸으로 초기화합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            next_mold[i][j] = BLANK;
    
    // 곰팡이를 한번씩 이동시킵니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(mold[i][j] != BLANK)
                Move(i, j);
    
    // next_mold 값을 mold에 옮겨줍니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            mold[i][j] = next_mold[i][j];
}

void Simulate(int col) {
    // 해당 열에 있는 곰팡이를 채취합니다.
    Collect(col);
    
    // 곰팡이들을 전부 움직입니다.
    MoveAll();
}

int main() {
    cin >> n >> m >> k;
    
    // 처음 맵 초기 상태를 전부 빈 공간으로 초기화합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            mold[i][j] = BLANK;
    
    for(int i = 0; i < k; i++) {
        int x, y, s, d, b;
        cin >> x >> y >> s >> d >> b;
        
        // 위, 아래 방향으로 움직이는 경우
        // 2n - 2번 움직이면 다시 제자리로 돌아오게 되므로
        // 움직여야 할 거리를 2n - 2로 나눴을 때의 나머지 만큼만
        // 움직이게 하면 최적화가 가능합니다.
        if(d <= 2)
            s %= (2 * n - 2);
        // 왼쪽, 오른쪽 방향으로 움직이는 경우
        // 2m - 2번 움직이면 다시 제자리로 돌아오게 되므로
        // 움직여야 할 거리를 2m - 2로 나눴을 때의 나머지 만큼만
        // 움직이게 하면 최적화가 가능합니다.
        else
            s %= (2 * m - 2);
        
        // tuple에 넣을 때
        // 곰팡이 크기 정보를 먼저 넣어, 후에 곰팡이끼리 충돌이 일어날 경우
        // 크기부터 비교하여 최대인 곰팡이를 쉽게 판단할 수 있도록 합니다.
        mold[x - 1][y - 1] = make_tuple(b, s, d - 1);
    }
    
    // 한 칸씩 이동하면서 곰팡이를 채취합니다.
    for(int col = 0; col < m; col++)
        Simulate(col);
    
    cout << ans;
    return 0;
}
