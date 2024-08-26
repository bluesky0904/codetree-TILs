#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 101;
int grid[MAX][MAX] = {0};

// 방향을 위한 배열 (오른쪽, 위, 왼쪽, 아래 순서)
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

// 드래곤 커브를 그리는 함수
void drawDragonCurve(int x, int y, int d, int g) {
    vector<int> directions;
    directions.push_back(d);

    // 이전 세대 방향들을 추가해서 다음 세대 방향을 만듦
    for (int i = 0; i < g; ++i) {
        int size = directions.size();
        for (int j = size - 1; j >= 0; --j) {
            directions.push_back((directions[j] + 1) % 4);
        }
    }

    // 드래곤 커브 그리기
    grid[x][y] = 1;
    for (int dir : directions) {
        x += dx[dir];
        y += dy[dir];
        grid[x][y] = 1;
    }
}

// 전체 좌표평면에서 정사각형의 개수를 세는 함수
int countSquares() {
    int count = 0;
    for (int i = 0; i < MAX - 1; ++i) {
        for (int j = 0; j < MAX - 1; ++j) {
            if (grid[i][j] && grid[i + 1][j] && grid[i][j + 1] && grid[i + 1][j + 1]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        drawDragonCurve(x, y, d, g);
    }

    // 결과 출력
    cout << countSquares() << endl;

    return 0;
}