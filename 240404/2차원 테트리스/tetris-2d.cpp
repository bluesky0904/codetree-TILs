#include <iostream>
using namespace std;

#define X_SIZE 6
#define Y_SIZE 4

int k;
int yellow_grid[X_SIZE][Y_SIZE];
int next_yellow_grid[X_SIZE][Y_SIZE];
int red_grid[X_SIZE][Y_SIZE];
int next_red_grid[X_SIZE][Y_SIZE];
int score = 0;

int CountRemainBlock() {
	int cnt = 0;
	for (int x = 2; x < X_SIZE; x++) {
		for (int y = 0; y < Y_SIZE; y++) {
			if (yellow_grid[x][y] == 1) cnt++;
		}
	}
	for (int x = 2; x < X_SIZE; x++) {
		for (int y = 0; y < Y_SIZE; y++) {
			if (red_grid[x][y] == 1) cnt++;
		}
	}
	return cnt;
}

void DeleteMiddleYellowLine(int full_row) {
	for (int row = 0; row < X_SIZE; row++) {
		for (int col = 0; col < Y_SIZE; col++) {
			next_yellow_grid[row][col] = 0;
		}
	}

	for (int row = X_SIZE - 1; row >= full_row - 1; row--) {
		for (int col = 0; col < Y_SIZE; col++) {
			next_yellow_grid[row][col] = yellow_grid[row][col];
		}
	}
	for (int row = full_row; row >= 1; row--) {
		for (int col = 0; col < Y_SIZE; col++) {
			next_yellow_grid[row][col] = yellow_grid[row - 1][col];
		}
	}

	for (int row = 0; row < X_SIZE; row++) {
		for (int col = 0; col < Y_SIZE; col++) {
			yellow_grid[row][col] = next_yellow_grid[row][col];
		}
	}
}

void DeleteYellowLine(int cnt) {
	if (cnt == 0)
		return;
	for (int row = 0; row < X_SIZE; row++) {
		for (int col = 0; col < Y_SIZE; col++) {
			next_yellow_grid[row][col] = 0;
		}
	}
	if (cnt == 1) {
		for (int row = X_SIZE - 2; row >= 0; row--) {
			for (int col = 0; col < Y_SIZE; col++) {
				next_yellow_grid[row + 1][col] = yellow_grid[row][col];
			}
		}
	}
	else if (cnt == 2) {
		for (int row = X_SIZE - 3; row >= 0; row--) {
			for (int col = 0; col < Y_SIZE; col++) {
				next_yellow_grid[row + 2][col] = yellow_grid[row][col];
			}
		}
	}
	for (int row = 0; row < X_SIZE; row++) {
		for (int col = 0; col < Y_SIZE; col++) {
			yellow_grid[row][col] = next_yellow_grid[row][col];
		}
	}
}

void MoveToYellow(int t, int x, int y) {
	if (t == 1) {
		// 1. 블록 내리기
		int last_row = X_SIZE - 1;
		for (int row = 1; row < X_SIZE; row++) {
			if (yellow_grid[row][y] == 1) {
				yellow_grid[row - 1][y] = 1;
				last_row = row - 1;
				break;
			}
		}
		if(last_row == X_SIZE - 1) yellow_grid[last_row][y] = 1;
		// 2. 한 줄 채우면 점수 얻기
		bool is_full = true;
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[last_row][col] == 0) {
				is_full = false;
				break;
			}
		}
		if (is_full) {
			for (int col = 0; col < Y_SIZE; col++) {
				yellow_grid[last_row][col] = 0;
			}
			score++;
			DeleteMiddleYellowLine(last_row);
		}
		// 3. 연한 부분에 블록이 위치할 경우 처리
		int cnt = 0;
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[0][col] == 1) {
				cnt++;
				break;
			}
		}
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[1][col] == 1) {
				cnt++;
				break;
			}
		}
		DeleteYellowLine(cnt);
	}

	else if (t == 2) {
		int last_row = X_SIZE - 1;
		for (int row = 1; row < X_SIZE; row++) {
			if (yellow_grid[row][y] == 1 || yellow_grid[row][y+1] == 1) {
				yellow_grid[row - 1][y] = 1;
				yellow_grid[row - 1][y + 1] = 1;
				last_row = row - 1;
				break;
			}
		}
		if (last_row == X_SIZE - 1) {
			yellow_grid[last_row][y] = 1;
			yellow_grid[last_row][y + 1] = 1;
		}

		bool is_full = true;
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[last_row][col] == 0) is_full = false;
		}
		if (is_full) {
			for (int col = 0; col < Y_SIZE; col++) {
				yellow_grid[last_row][col] = 0;
			}
			score++;
			DeleteMiddleYellowLine(last_row);
		}

		int cnt = 0;
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[0][col] == 1) {
				cnt++;
				break;
			}
		}
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[1][col] == 1) {
				cnt++;
				break;
			}
		}
		DeleteYellowLine(cnt);
	}
	else if (t == 3) {
		int last_row = X_SIZE - 1;
		for (int row = 1; row < X_SIZE - 1; row++) {
			if (yellow_grid[row + 1][y] == 1) {
				yellow_grid[row - 1][y] = 1;
				yellow_grid[row][y] = 1;
				last_row = row;
				break;
			}
		}
		if (last_row == X_SIZE - 1) {
			yellow_grid[last_row - 1][y] = 1;
			yellow_grid[last_row][y] = 1;
		}

		bool is_full = true;
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[last_row - 1][col] == 0) {
				is_full = false;
				break;
			}
		}
		if (is_full) {
			for (int col = 0; col < Y_SIZE; col++) {
				yellow_grid[last_row - 1][col] = 0;
			}
			score++;
			DeleteMiddleYellowLine(last_row - 1);
		}
		is_full = true;
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[last_row][col] == 0) {
				is_full = false;
				break;
			}
		}
		if (is_full) {
			for (int col = 0; col < Y_SIZE; col++) {
				yellow_grid[last_row][col] = 0;
			}
			score++;
			DeleteMiddleYellowLine(last_row);
		}

		int cnt = 0;
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[0][col] == 1) {
				cnt++;
				break;
			}
		}
		for (int col = 0; col < Y_SIZE; col++) {
			if (yellow_grid[1][col] == 1) {
				cnt++;
				break;
			}
		}
		DeleteYellowLine(cnt);
	}
}

void DeleteMiddleRedLine(int full_row) {
	for (int row = 0; row < X_SIZE; row++) {
		for (int col = 0; col < Y_SIZE; col++) {
			next_red_grid[row][col] = 0;
		}
	}

	for (int row = X_SIZE - 1; row >= full_row - 1; row--) {
		for (int col = 0; col < Y_SIZE; col++) {
			next_red_grid[row][col] = red_grid[row][col];
		}
	}
	for (int row = full_row; row >= 1; row--) {
		for (int col = 0; col < Y_SIZE; col++) {
			next_red_grid[row][col] = red_grid[row - 1][col];
		}
	}

	for (int row = 0; row < X_SIZE; row++) {
		for (int col = 0; col < Y_SIZE; col++) {
			red_grid[row][col] = next_red_grid[row][col];
		}
	}
}

void DeleteRedLine(int cnt) {
	if (cnt == 0) return;

	for (int row = 0; row < X_SIZE; row++) {
		for (int col = 0; col < Y_SIZE; col++) {
			next_red_grid[row][col] = 0;
		}
	}

	if (cnt == 1) {
		for (int row = X_SIZE - 2; row >= 0; row--) {
			for (int col = 0; col < Y_SIZE; col++) {
				next_red_grid[row + 1][col] = red_grid[row][col];
			}
		}
	}
	else if (cnt == 2) {
		for (int row = X_SIZE - 3; row >= 0; row--) {
			for (int col = 0; col < Y_SIZE; col++) {
				next_red_grid[row + 2][col] = red_grid[row][col];
			}
		}
	}

	for (int row = 0; row < X_SIZE; row++) {
		for (int col = 0; col < Y_SIZE; col++) {
			red_grid[row][col] = next_red_grid[row][col];
		}
	}
}

void MoveToRed(int t, int x, int y) {
	if (t == 1) {
		// 1. 블록 내리기
		int last_row = X_SIZE - 1;
		for (int row = 1; row < X_SIZE; row++) {
			if (red_grid[row][y] == 1) {
				red_grid[row - 1][y] = 1;
				last_row = row - 1;
				break;
			}
		}
		if(last_row == X_SIZE - 1) red_grid[last_row][y] = 1;

		// 2. 한 줄 채우면 점수 얻기
		bool is_full = true;
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[last_row][col] == 0) {
				is_full = false;
				break;
			}
		}
		if (is_full) {
			for (int col = 0; col < Y_SIZE; col++) {
				red_grid[last_row][col] = 0;
			}
			score++;
			DeleteMiddleRedLine(last_row);
		}

		// 3. 연한 부분에 블록이 위치할 경우 처리
		int cnt = 0;
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[0][col] == 1) {
				cnt++;
				break;
			}
		}
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[1][col] == 1) {
				cnt++;
				break;
			}
		}
		DeleteRedLine(cnt);
	}
	else if (t == 2) {
		int last_row = X_SIZE - 1;
		for (int row = 1; row < X_SIZE; row++) {
			if (red_grid[row][y] == 1 || red_grid[row][y + 1] == 1) {
				red_grid[row - 1][y] = 1;
				red_grid[row - 1][y + 1] = 1;
				last_row = row - 1;
				break;
			}
		}
		if (last_row == X_SIZE - 1) {
			red_grid[last_row][y] = 1;
			red_grid[last_row][y + 1] = 1;
		}

		bool is_full = true;
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[last_row][col] == 0) {
				is_full = false;
				break;
			}
		}
		if (is_full) {
			for (int col = 0; col < Y_SIZE; col++) {
				red_grid[last_row][col] = 0;
			}
			score++;
			DeleteMiddleRedLine(last_row);
		}

		int cnt = 0;
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[0][col] == 1) {
				cnt++;
				break;
			}
		}
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[1][col] == 1) {
				cnt++;
				break;
			}
		}
		DeleteRedLine(cnt);
	}
	else if (t == 3) {
		int last_row = X_SIZE - 1;
		for (int row = 1; row < X_SIZE - 1; row++) {
			if (red_grid[row + 1][y] == 1) {
				red_grid[row - 1][y] = 1;
				red_grid[row][y] = 1;
				last_row = row;
				break;
			}
		}
		if (last_row == X_SIZE - 1) {
			red_grid[last_row - 1][y] = 1;
			red_grid[last_row][y] = 1;
		}

		bool is_full = true;
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[last_row - 1][col] == 0) {
				is_full = false;
				break;
			}
		}
		if (is_full) {
			for (int col = 0; col < Y_SIZE; col++) {
				red_grid[last_row - 1][col] = 0;
			}
			score++;
			DeleteMiddleRedLine(last_row - 1);
		}

		is_full = true;
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[last_row][col] == 0) {
				is_full = false;
				break;
			}
		}
		if (is_full) {
			for (int col = 0; col < Y_SIZE; col++) {
				red_grid[last_row][col] = 0;
			}
			score++;
			DeleteMiddleRedLine(last_row);
		}

		int cnt = 0;
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[0][col] == 1) {
				cnt++;
				break;
			}
		}
		for (int col = 0; col < Y_SIZE; col++) {
			if (red_grid[1][col] == 1) {
				cnt++;
				break;
			}
		}
		DeleteRedLine(cnt);
	}
}

void Simulate(int t, int x, int y) {
	MoveToYellow(t, x, y);
	if(t == 1) MoveToRed(1, y, 3 - x);
	else if(t == 2) MoveToRed(3, y, 3 - x);
	else if(t == 3) MoveToRed(2, y, 3 - x - 1);
}

void Print() {
	cout << "Yellow GRID" << "\n"; 
	for (int i = 0; i < X_SIZE; i++) {
		for (int j = 0; j < Y_SIZE; j++) {
			cout << yellow_grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "Red GRID" << "\n";
	for (int i = 0; i < X_SIZE; i++) {
		for (int j = 0; j < Y_SIZE; j++) {
			cout << red_grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "Score: " << score << "\n";
	cout << "-------------------------\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	cin >> k;
	while (k--) {
		int t, x, y;
		cin >> t >> x >> y;
		Simulate(t, x, y);
		//Print();
	}

	cout << score << "\n" << CountRemainBlock() << "\n";
	return 0;
}