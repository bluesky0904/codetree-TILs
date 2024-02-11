#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> lines;

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, x2;
        cin >> x1 >> x2;
        lines.push_back({x1, x2});
    }

    // 선분의 끝점을 기준으로 정렬
    sort(lines.begin(), lines.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });

    int ans = 0;
    int last_end = 0;
    for (auto &line : lines) {
        if (line.first > last_end) { // 겹치지 않는 경우에만 선택
            ans++;
            last_end = line.second;
        }
    }

    cout << ans << "\n";
    return 0;
}