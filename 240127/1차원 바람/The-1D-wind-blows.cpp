#include <iostream>

#define MAX_N 100
#define MAX_M 100
#define SHIFT_RIGHT 0
#define SHIFT_LEFT 1

using namespace std;

int n, m, q;

int a[MAX_N + 1][MAX_M + 1];

void Shift(int row, int dir) {
  
    if(dir == SHIFT_RIGHT) {
        int temp = a[row][m];
        for(int col = m; col >= 2; col--)
            a[row][col] = a[row][col - 1];
        a[row][1] = temp;
    }
 
    else {
        int temp = a[row][1];
        for(int col = 1; col <= m - 1; col++)
            a[row][col] = a[row][col + 1];
        a[row][m] = temp;
    }
}

bool HasSameNumber(int row1, int row2) {
    for(int col = 1; col <= m; col++)
        if(a[row1][col] == a[row2][col])
            return true;
    
    return false;
}

bool Flip(int dir) {
    return (dir == SHIFT_LEFT) ? SHIFT_RIGHT : SHIFT_LEFT;
}

void Simulate(int start_row, int start_dir) {

    Shift(start_row, start_dir);

    start_dir = Flip(start_dir);

    for(int row = start_row, dir = start_dir; row >= 2; row--) {

        if(HasSameNumber(row, row - 1)) {
            Shift(row - 1, dir);
            dir = Flip(dir);
        }
        else
            break;
    }

    for(int row = start_row, dir = start_dir; row <= n - 1; row++) {
    
        if(HasSameNumber(row, row + 1)) {
            Shift(row + 1, dir);
            dir = Flip(dir);
        }

        else
            break;
    }
}

int main() {

    cin >> n >> m >> q;
    
    for(int row = 1; row <= n; row++)
        for(int col = 1; col <= m; col++)
            cin >> a[row][col];
    
    while(q--) {
        int r; char d;
        cin >> r >> d;

        Simulate(r, d == 'L' ? SHIFT_RIGHT : SHIFT_LEFT);
    }

    for(int row = 1; row <= n; row++) {
        for(int col = 1; col <= m; col++)
            cout << a[row][col] << " ";
        cout << endl;
    }
    return 0;
}