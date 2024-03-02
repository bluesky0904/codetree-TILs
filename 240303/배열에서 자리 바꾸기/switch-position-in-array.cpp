#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        auto start1 = find(arr.begin(), arr.end(), a);
        auto end1 = find(arr.begin(), arr.end(), b) + 1;
        auto start2 = find(arr.begin(), arr.end(), c);
        auto end2 = find(arr.begin(), arr.end(), d) + 1;

        vector<int> temp1(start1, end1);
        vector<int> temp2(start2, end2);

        arr.erase(start1, end1);
        arr.insert(start1, start2, end2);
        arr.erase(start2 + (end2 - start2 - (end1 - start1)), start2 + (end2 - start2));
        arr.insert(start2 + (end2 - start2 - (end1 - start1)), temp1.begin(), temp1.end());
    }

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    return 0;
}