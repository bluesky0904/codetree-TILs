#include <iostream>

#define MAX_N 100

using namespace std;

int n, m, k;
int grid[MAX_N][MAX_N];

// 해당 row에 [col_s, col_e] 열에
// 전부 블럭이 없는지를 확인합니다.
int AllBlank(int row, int col_s, int col_e) {
    for(int col = col_s; col <= col_e ; col++)
        if(grid[row][col])
            return false;

    return true;
}

// 최종적으로 도달하게 될 위치는
// 그 다음 위치에 최초로 블럭이 존재하는 순간임을 이용합니다.
int GetTargetRow() {
    for(int row = 0; row < n - 1; row++)
		if(!AllBlank(row + 1, k, k + m - 1))
            return row;

    return n - 1;
}

int main() {
	cin >> n >> m >> k; k--;
    
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> grid[i][j];
	
    // 최종적으로 멈추게 될 위치를 구합니다.
    int target_row = GetTargetRow();
    
    // 최종 위치에 전부 블럭을 표시합니다.
    for(int col = k; col < k + m; col++)
        grid[target_row][col] = 1;
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
	return 0;
}