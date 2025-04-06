#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 100;

int n, L;
int grid[MAXN + 10][MAXN + 10];
int next_grid[MAXN + 10][MAXN + 10];
int bridge[MAXN + 10][MAXN + 10];

void print() {
    cout << "grid" << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool inRange(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

/*
    각 행이 지나갈 수 있는지 판단하는 함수
    - 두 인접 칸의 높이 차이가 1보다 크면 false
    - 낮은 쪽에 경사로를 놓을 수 없으면 false
    - 경사로가 이미 놓여있는 칸에는 또 놓을 수 없음
*/
bool isRowPossible(int row) {
    for (int col = 0; col < n - 1; col++) {
        int diff = grid[row][col+1] - grid[row][col];
        if (abs(diff) > 1) return false;

        // 내리막인 경우 (현재 칸보다 오른쪽 칸이 1 낮은 경우)
        if (diff == -1) {
            // 오른쪽 칸부터 L개의 칸이 모두 같은 높이이고 경사로가 없으면 경사로 설치 가능
            for (int j = col+1; j <= col+L; j++) {
                if (!inRange(row, j)) return false;
                if (bridge[row][j] == 1) return false;
                if (grid[row][j] != grid[row][col+1]) return false;
            }
            // 경사로 설치 후 해당 칸들을 표시
            for (int j = col+1; j <= col+L; j++) {
                bridge[row][j] = 1;
            }
            // 경사로가 설치된 칸들은 이미 처리했으므로 col을 건너뜀
            col = col + L - 1;
        }
        // 올라막인 경우 (현재 칸보다 오른쪽 칸이 1 높은 경우)
        else if (diff == 1) {
            // 왼쪽 칸부터 L개의 칸이 모두 같은 높이이고 경사로가 없으면 경사로 설치 가능
            for (int j = col; j > col - L; j--) {
                if (!inRange(row, j)) return false;
                if (bridge[row][j] == 1) return false;
                if (grid[row][j] != grid[row][col]) return false;
            }
            // 경사로 설치 후 해당 칸들을 표시
            for (int j = col; j > col - L; j--) {
                bridge[row][j] = 1;
            }
        }
        // 높이 차가 0인 경우는 그대로 진행
    }
    return true;
}

void rotateGrid() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            next_grid[j][n - i - 1] = grid[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = next_grid[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); 
    cout.tie(0);
   // freopen("sample_input.txt", "r", stdin);

    cin >> n >> L;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    //print();
    int cnt = 0;
    
    // 행 검사 전 bridge 배열 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bridge[i][j] = 0;
        }
    }
    for (int row = 0; row < n; row++) {
        if (isRowPossible(row)) {
            //cout << "row : " << row << "\n";
            cnt++;
        }
    }

    // 열 검사를 위해 grid 회전
    rotateGrid();

    // 회전 후 다시 bridge 배열 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bridge[i][j] = 0;
        }
    }
    for (int row = 0; row < n; row++) {
        if (isRowPossible(row)) {
            //cout << "col : " << row << "\n";
            cnt++;
        }
    }

    cout << cnt << "\n";
    return 0;
}
