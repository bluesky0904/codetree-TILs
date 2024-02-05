#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

#define MAX_N 50
#define ASCII_NUM 128
#define DIR_NUM 4

using namespace std;

int n, m, t, k;
vector<tuple<int, int, int> > grid[MAX_N][MAX_N];
vector<tuple<int, int, int> > next_grid[MAX_N][MAX_N];

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

tuple<int, int, int> NextPos(int x, int y, int vnum, int move_dir) {
	int dx[DIR_NUM] = {-1, 0, 0, 1};
	int dy[DIR_NUM] = {0, 1, -1, 0};
    
    // vnum 횟수만큼 이동한 이후의 위치를 반환합니다.
    while(vnum--) {
        int nx = x + dx[move_dir], ny = y + dy[move_dir];
        // 벽에 부딪히면
        // 방향을 바꾼 뒤 이동합니다.
        if(!InRange(nx, ny)) {
            move_dir = 3 - move_dir;
            nx = x + dx[move_dir]; ny = y + dy[move_dir];
        }
        x = nx; y = ny;
    }
    return make_tuple(x, y, move_dir);
}

void MoveAll() {
    for(int x = 0; x < n; x++)
        for(int y = 0; y < n; y++)
            for(int i = 0; i < (int) grid[x][y].size(); i++) {
                int v, num, move_dir;
                tie(v, num, move_dir) = grid[x][y][i];
                
                int next_x, next_y, next_dir;
                // v값이 음수이므로, -를 붙여 넘겨줍니다.
                tie(next_x, next_y, next_dir) = NextPos(x, y, -v, move_dir);
                next_grid[next_x][next_y].push_back(
                    make_tuple(v, num, next_dir)
                );
            }
}

void SelectMarbles() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) 
            if((int) next_grid[i][j].size() >= k) {
                // 우선순위가 높은 k개만 남겨줍니다.
                sort(next_grid[i][j].begin(), next_grid[i][j].end());
                while((int) next_grid[i][j].size() > k)
                    next_grid[i][j].pop_back();
            }
}

void Simulate() {
    // Step1. next_grid를 초기화합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            next_grid[i][j].clear();
		
    // Step2. 구슬들을 전부 움직입니다.
    MoveAll();
    
    // Step3. 각 칸마다 구슬이 최대 k개만 있도록 조정합니다.
    SelectMarbles();
    
    // Step4. next_grid 값을 grid로 옮겨줍니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            grid[i][j] = next_grid[i][j];
}

int main() {
	cin >> n >> m >> t >> k;
	
	int dir_mapper[ASCII_NUM];
	dir_mapper['U'] = 0;
	dir_mapper['R'] = 1;
	dir_mapper['L'] = 2;
	dir_mapper['D'] = 3;
	
	for(int i = 0; i < m; i++) {
		int r, c, v; char d;
		cin >> r >> c >> d >> v;
        
        // 살아남는 구슬의 우선순위가 더 빠른 속도, 더 큰 번호 이므로
        // 정렬시 속도가 먼저 내림차순, 그 다음에는 번호가 내림차순으로 오도록
        // (-속도, -번호, 방향) 순서를 유지합니다.
		grid[r - 1][c - 1].push_back(
            make_tuple(-v, -(i + 1), dir_mapper[d])
        );
	}
	
    // t초에 걸쳐 시뮬레이션을 반복합니다.
	while(t--)
		Simulate();
	
	int ans = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			ans += (int) grid[i][j].size();
	
	cout << ans;
	
	return 0;
}