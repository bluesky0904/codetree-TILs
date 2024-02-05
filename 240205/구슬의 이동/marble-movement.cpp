#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
using namespace std;

#define DIR_NUM 4
#define MAX_N 50
#define ASCII_NUM 128

typedef tuple<int, int, int, int, int> Marble; // x, y, speed, direction, number

int n, m, t, k;
int mapper[ASCII_NUM];
int dx[DIR_NUM] = {1, 0, -1, 0};
int dy[DIR_NUM] = {0, -1, 0, 1};
vector<Marble> marbles;

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

Marble Move(Marble marble) {
    int x, y, v, d, num;
    tie(x, y, v, d, num) = marble;
    for (int cnt = 0; cnt < v; cnt++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (!InRange(nx, ny)) {
            d = (d + 2) % 4; // Change direction
        }
        nx = x + dx[d];
        ny = y + dy[d];
        x = nx;
        y = ny;
    }
    return make_tuple(x, y, v, d, num);
}

void MoveAll() {
    for (int i = 0; i < marbles.size(); i++) {
        marbles[i] = Move(marbles[i]);
    }
}

void RemoveDuplicateMarbles() {
    map<pair<int, int>, vector<Marble>> marbleMap;
    for (auto& marble : marbles) {
        int x, y, v, d, num;
        tie(x, y, v, d, num) = marble;
        marbleMap[{x, y}].push_back(marble);
    }

    vector<Marble> temp_vector;
    for (auto& entry : marbleMap) {
        auto& vec = entry.second;
        // Sort by speed (descending), then by number (descending)
        sort(vec.begin(), vec.end(), [](const Marble& a, const Marble& b) {
            return get<2>(a) > get<2>(b) || (get<2>(a) == get<2>(b) && get<4>(a) > get<4>(b));
        });
        // Keep up to k marbles
        for (int i = 0; i < min(k, (int)vec.size()); i++) {
            temp_vector.push_back(vec[i]);
        }
    }

    marbles = temp_vector;
}

void Simulate() {
    MoveAll();
    RemoveDuplicateMarbles();
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> t >> k;

    mapper['D'] = 0; mapper['L'] = 1; mapper['U'] = 2; mapper['R'] = 3;

    for (int num = 1; num <= m; num++) {
        int r, c, v;
        char d;
        cin >> r >> c >> d >> v;
        r--; c--;
        marbles.push_back(make_tuple(r, c, v, mapper[d], num));
    }

    while (t--) {
        Simulate();
    }

    cout << marbles.size() << "\n";
}