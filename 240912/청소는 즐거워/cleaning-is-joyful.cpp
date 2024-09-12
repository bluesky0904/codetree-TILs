#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#define MAX_N 499
#define DIR_NUM 4

int n;
int grid[MAX_N][MAX_N];

int broom_x, broom_y, broom_dir;

int dx[DIR_NUM] = { 0, 1, 0, -1 };
int dy[DIR_NUM] = { -1, 0, 1, 0 };

int ans = 0;

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool IsFinish() {
    return broom_x == 0 && broom_y == 0;
}

void MoveDust() {
    int curr, a, tmp = 0;
    int nx, ny;
    curr = grid[broom_x][broom_y];
    grid[broom_x][broom_y] = 0;

    // 위
    nx = broom_x + dx[(broom_dir + 3) % 4] * 2;
    ny = broom_y + dy[(broom_dir + 3) % 4] * 2;
    if (InRange(nx, ny)) {
        grid[nx][ny] += int(curr * 0.02);  // 부동소수점 캐스팅
    } else {
        ans += int(curr * 0.02);
    }
    tmp += int(curr * 0.02);

    nx = broom_x + dx[(broom_dir + 3) % 4] + dx[broom_dir];
    ny = broom_y + dy[(broom_dir + 3) % 4] + dy[broom_dir];
    if (InRange(nx, ny)) {
        grid[nx][ny] += int(curr * 0.1);  // 부동소수점 캐스팅
    } else {
        ans += int(curr * 0.1);
    }
    tmp += int(curr * 0.1);

    nx = broom_x + dx[(broom_dir + 3) % 4];
    ny = broom_y + dy[(broom_dir + 3) % 4];
    if (InRange(nx, ny)) {
        grid[nx][ny] += int(curr * 0.07);  // 부동소수점 캐스팅
    } else {
        ans += int(curr * 0.07);
    }
    tmp += int(curr * 0.07);

    nx = broom_x + dx[(broom_dir + 3) % 4] + dx[(broom_dir + 2) % 4];
    ny = broom_y + dy[(broom_dir + 3) % 4] + dy[(broom_dir + 2) % 4];
    if (InRange(nx, ny)) {
        grid[nx][ny] += int(curr * 0.01);  // 부동소수점 캐스팅
    } else {
        ans += int(curr * 0.01);
    }
    tmp += int(curr * 0.01);

    // 중간
    nx = broom_x + dx[broom_dir] * 2;
    ny = broom_y + dy[broom_dir] * 2;
    if (InRange(nx, ny)) {
        grid[nx][ny] += int(curr * 0.05);  // 부동소수점 캐스팅
    } else {
        ans += int(curr * 0.05);
    }
    tmp += int(curr * 0.05);

    // 아래
    nx = broom_x + dx[(broom_dir + 1) % 4] * 2;
    ny = broom_y + dy[(broom_dir + 1) % 4] * 2;
    if (InRange(nx, ny)) {
        grid[nx][ny] += int(curr * 0.02);  // 부동소수점 캐스팅
    } else {
        ans += int(curr * 0.02);
    }
    tmp += int(curr * 0.02);

    nx = broom_x + dx[(broom_dir + 1) % 4] + dx[broom_dir];
    ny = broom_y + dy[(broom_dir + 1) % 4] + dy[broom_dir];
    if (InRange(nx, ny)) {
        grid[nx][ny] += int(curr * 0.1);  // 부동소수점 캐스팅
    } else {
        ans += int(curr * 0.1);
    }
    tmp += int(curr * 0.1);

    nx = broom_x + dx[(broom_dir + 1) % 4];
    ny = broom_y + dy[(broom_dir + 1) % 4];
    if (InRange(nx, ny)) {
        grid[nx][ny] += int(curr * 0.07);  // 부동소수점 캐스팅
    } else {
        ans += int(curr * 0.07);
    }
    tmp += int(curr * 0.07);

    nx = broom_x + dx[(broom_dir + 1) % 4] + dx[(broom_dir + 2) % 4];
    ny = broom_y + dy[(broom_dir + 1) % 4] + dy[(broom_dir + 2) % 4];
    if (InRange(nx, ny)) {
        grid[nx][ny] += int(curr * 0.01);  // 부동소수점 캐스팅
    } else {
        ans += int(curr * 0.01);
    }
    tmp += int(curr * 0.01);

    // 남은 먼지 처리
    a = curr - tmp;
    nx = broom_x + dx[broom_dir];
    ny = broom_y + dy[broom_dir];
    if (InRange(nx, ny)) {
        grid[nx][ny] += a;
    } else {
        ans += a;
    }
}

void Simulate() {
    int dis_num = 1;
    while (true) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < dis_num; j++) {
                broom_x += dx[broom_dir], broom_y += dy[broom_dir];
                MoveDust();
                //Print();
                if (IsFinish()) return;
            }
            broom_dir = (broom_dir + 1) % 4;
        }
	    dis_num++;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    broom_x = n / 2;
    broom_y = n / 2;
    broom_dir = 0;
    Simulate();

    cout << ans << '\n';
}