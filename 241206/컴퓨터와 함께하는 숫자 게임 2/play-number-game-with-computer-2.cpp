#include <iostream>
#include <cmath> // for log2
using namespace std;

int main() {
    int m, a, b;
    cin >> m >> a >> b;

    int min_cnt = 1e9, max_cnt = 0;

    for (int target = a; target <= b; target++) {
        int cnt = 0;
        int left = 1, right = m;

        while (left <= right) {
            int mid = (left + right) / 2;
            cnt++;
            if (mid == target) break;
            if (mid > target)
                right = mid - 1;
            else
                left = mid + 1;
        }

        min_cnt = min(min_cnt, cnt);
        max_cnt = max(max_cnt, cnt);
    }

    cout << min_cnt << " " << max_cnt << "\n";
    return 0;
}
