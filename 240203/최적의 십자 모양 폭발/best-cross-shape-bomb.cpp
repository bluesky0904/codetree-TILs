#include <iostream>
#include <cmath>

#define MAX_N 50
#define DIR_NUM 4

using namespace std;

int n;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];

bool InBombRange(int x, int y, int center_x, int center_y, int bomb_range) {
    return (x == center_x || y == center_y) && 
           abs(x - center_x) + abs(y - center_y) < bomb_range;
}

void Bomb(int center_x, int center_y) {
	// Step1. next_grid 값을 0으로 초기화합니다.
    for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
            next_grid[i][j] = 0;

    // Step2. 폭탄이 터질 위치는 0으로 채워줍니다.
	int bomb_range = grid[center_x][center_y];
    
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(InBombRange(i, j, center_x, center_y, bomb_range))
				grid[i][j] = 0;
	
    // Step3. 폭탄이 터진 이후의 결과를 next_grid에 저장합니다.
	for(int j = 0; j < n; j++) {
        int next_row = n - 1;
		for(int i = n - 1; i >= 0; i--) {
			if(grid[i][j])
				next_grid[next_row--][j] = grid[i][j];
		}
    }
	
    // Step4. grid로 다시 값을 옮겨줍니다.
    for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
            grid[i][j] = next_grid[i][j];
}


void SaveGrid() {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			temp[i][j] = grid[i][j];
}

void LoadGrid() {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			grid[i][j] = temp[i][j];
}

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool MeetTheCondition(int x, int y, int nx, int ny) {
    return InRange(nx, ny) && grid[x][y] && grid[x][y] == grid[nx][ny];
}

int Calc() {
	int cnt = 0;
	for(int x = 0; x < n; x++)
		for(int y = 0; y < n; y++) {
			int dx[DIR_NUM] = {-1, 1, 0, 0};
			int dy[DIR_NUM] = {0, 0, 1, -1};
            
			for(int k = 0; k < 4; k++) {
				int nx = x + dx[k], ny = y + dy[k];
                if(MeetTheCondition(x, y, nx, ny))
				    cnt++;
			}
		}
	
    // 중복되어 2번씩 count되므로
    // 2로 나누어줍니다.
	return cnt / 2;
}

int main() {
	cin >> n;
    
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> grid[i][j];
	
    int ans = 0;
    
    // 각 위치에 대해 진행해보고
    // 그 중 최대 만족 횟수를 구합니다.
    for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			SaveGrid();
			Bomb(i, j);
			ans = max(ans, Calc());
			LoadGrid();
		}
    
    cout << ans;
	
	return 0;
}