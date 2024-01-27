#include <iostream>
#include <cmath>

#define MAX_N 200

using namespace std;

int n;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];

bool InBombRange(int x, int y, int center_x, int center_y, int bomb_range) {
    return (x == center_x || y == center_y) && 
           abs(x - center_x) + abs(y - center_y) < bomb_range;
}

void Bomb(int center_x, int center_y) {
	int bomb_range = grid[center_x][center_y];
    
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(InBombRange(i, j, center_x, center_y, bomb_range))
				grid[i][j] = 0;
	
	for(int j = 0; j < n; j++) {
        int next_row = n - 1;
		for(int i = n - 1; i >= 0; i--) {
			if(grid[i][j])
				next_grid[next_row--][j] = grid[i][j];
		}
    }
	
    for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
            grid[i][j] = next_grid[i][j];
}

int main() {
	cin >> n;
    
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> grid[i][j];
	
	int r, c;
	cin >> r >> c;
    
    Bomb(r - 1, c - 1);
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
	
	return 0;
}