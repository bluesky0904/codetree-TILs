#include <iostream>
#include <algorithm>
#include <climits>

#define MAX_NUM 5

using namespace std;

int n, m;
int grid[MAX_NUM][MAX_NUM];
int board[MAX_NUM][MAX_NUM];

void ClearBoard() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            board[i][j] = 0;
}

void Draw(int x1, int y1, int x2, int y2) {
    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            board[i][j]++;
}

bool CheckBoard() {
    // 동일한 칸을 2개의 직사각형이 모두 포함한다면
    // 겹치게 됩니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(board[i][j] >= 2)
                return true;
    return false;
}

// (x1, y1), (x2, y2) 그리고
// (x3, y3), (x4, y4) 로 이루어져있는
// 두 직사각형이 겹치는지 확인하는 함수
bool Overlapped(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    ClearBoard();
    Draw(x1, y1, x2, y2);
    Draw(x3, y3, x4, y4);
    return CheckBoard();
}

int RectSum(int x1, int y1, int x2, int y2) {
    int sum_of_nums = 0;
    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            sum_of_nums += grid[i][j];
    
    return sum_of_nums;
}

// 첫 번째 직사각형이 (x1, y1), (x2, y2)를 양쪽 꼭지점으로 할 때
// 두 번째 직사각형을 겹치지 않게 잘 잡아
// 최대 합을 반환하는 함수
int FindMaxSum(int x1, int y1, int x2, int y2) {
    int max_sum = INT_MIN;
    
    // (i, j), (k, l)을 양쪽 꼭지점으로 하는
    // 두 번째 직사각형을 정하여
    // 겹치지 않았을 때 중
    // 최댓값을 찾아 반환합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            for(int k = i; k < n; k++)
                for(int l = j; l < m; l++) {
                    if(!Overlapped(x1, y1, x2, y2, i, j, k, l))
                        max_sum = max(max_sum, 
                                      RectSum(x1, y1, x2, y2) +
                                      RectSum(i, j, k, l));
                }
    
    return max_sum;
}

// 두 직사각형을 잘 잡았을 때의 최대 합을 반환하는 함수
int FindMaxSum() {
    int max_sum = INT_MIN;
    
	// (i, j), (k, l)을 양쪽 꼭지점으로 하는
    // 첫 번째 직사각형을 정하여
    // 그 중 최댓값을 찾아 반환합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            for(int k = i; k < n; k++)
                for(int l = j; l < m; l++)
                    max_sum = max(max_sum,
                                  FindMaxSum(i, j, k, l));
    return max_sum;
}

int main() {
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> grid[i][j];
	
	int ans = FindMaxSum();
	cout << ans;
	
	return 0;
}