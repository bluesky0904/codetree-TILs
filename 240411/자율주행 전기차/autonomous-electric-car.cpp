#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int dx[DIR_NUM] = {-1, 0, 1, 0};
int dy[DIR_NUM] = {0, 1, 0, -1};

int n, m, c; // 격자의 크기, 승객의 수, 초기 배터리 충전량
int grid[MAX_N][MAX_N];
int car_x, car_y, remain;
bool is_possible = true;

struct Passenger {
    int sx, sy, ex, ey;
    int dist_to_start;
};

vector<Passenger> passengers;

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

void CalculateDistancesToPassengers() {
    queue<pair<int, int>> q;
    vector<vector<int>> distance(n, vector<int>(n, -1));
    q.push({car_x, car_y});
    distance[car_x][car_y] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int dir = 0; dir < DIR_NUM; ++dir) {
            int nx = x + dx[dir], ny = y + dy[dir];
            if (InRange(nx, ny) && grid[nx][ny] == 0 && distance[nx][ny] == -1) {
                distance[nx][ny] = distance[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    for (auto& p : passengers) {
        p.dist_to_start = distance[p.sx][p.sy];
    }
}

bool cmp(const Passenger& a, const Passenger& b) {
    if (a.dist_to_start != b.dist_to_start) return a.dist_to_start < b.dist_to_start;
    if (a.sx != b.sx) return a.sx < b.sx;
    return a.sy < b.sy;
}

int BFS(int sx, int sy, int ex, int ey) {
    vector<vector<int>> distance(n, vector<int>(n, -1));
    queue<pair<int, int>> q;
    q.push({sx, sy});
    distance[sx][sy] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (x == ex && y == ey) return distance[x][y];

        for (int dir = 0; dir < DIR_NUM; ++dir) {
            int nx = x + dx[dir], ny = y + dy[dir];
            if (InRange(nx, ny) && grid[nx][ny] == 0 && distance[nx][ny] == -1) {
                distance[nx][ny] = distance[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1; // 경로가 없는 경우
}

bool Simulate() {
    if (passengers.empty()) return false;

    CalculateDistancesToPassengers();
    sort(passengers.begin(), passengers.end(), cmp);

    Passenger cur_passenger = passengers.front();
    passengers.erase(passengers.begin());

    if (cur_passenger.dist_to_start == -1 || remain < cur_passenger.dist_to_start) {
        is_possible = false;
        return false;
    }

    remain -= cur_passenger.dist_to_start;
    car_x = cur_passenger.sx;
    car_y = cur_passenger.sy;

    int min_route_end = BFS(car_x, car_y, cur_passenger.ex, cur_passenger.ey);
    if (min_route_end == -1 || remain < min_route_end) {
        is_possible = false;
        return false;
    }

    remain -= min_route_end;
    remain += 2 * min_route_end;
    car_x = cur_passenger.ex;
    car_y = cur_passenger.ey;

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cin >> car_x >> car_y;
    car_x--; car_y--; // 0-indexed adjustment
    remain = c;

    for (int i = 0; i < m; i++) {
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        passengers.push_back({sx - 1, sy - 1, ex - 1, ey - 1, -1});
    }

    while (Simulate());

    if (is_possible && passengers.empty())
        cout << remain << "\n";
    else
        cout << -1 << "\n";

    return 0;
}