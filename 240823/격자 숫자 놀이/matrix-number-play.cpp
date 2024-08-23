#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int r, c, k;
vector<vector<int>> A(3, vector<int>(3));

void fillZero(vector<vector<int>>& A, int max_len) {
    for (auto& row : A) {
        while (row.size() < max_len) {
            row.push_back(0);
        }
    }
}

vector<vector<int>> operationR(vector<vector<int>>& A) {
    int max_len = 0;
    vector<vector<int>> new_A;

    for (auto& row : A) {
        map<int, int> count_map;
        vector<pair<int, int>> count_vector;

        for (int num : row) {
            if (num != 0) {
                count_map[num]++;
            }
        }

        for (auto& it : count_map) {
            count_vector.push_back({ it.second, it.first });
        }

        sort(count_vector.begin(), count_vector.end(), [](pair<int, int>& a, pair<int, int>& b) {
            if (a.first == b.first)
                return a.second < b.second;
            return a.first < b.first;
            });

        vector<int> new_row;
        for (auto& it : count_vector) {
            new_row.push_back(it.second);
            new_row.push_back(it.first);
        }

        max_len = max(max_len, static_cast<int>(new_row.size()));
        new_A.push_back(new_row);
    }

    fillZero(new_A, max_len);
    return new_A;
}

vector<vector<int>> transpose(vector<vector<int>>& A) {
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int>> transposed_A(cols, vector<int>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed_A[j][i] = A[i][j];
        }
    }

    return transposed_A;
}

int main() {
    cin >> r >> c >> k;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> A[i][j];
        }
    }

    int sec = 0;

    while (true) {
        if (r <= A.size() && c <= A[0].size() && A[r - 1][c - 1] == k) {
            cout << sec << endl;
            break;
        }

        if (sec > 100) {
            cout << -1 << endl;
            break;
        }

        if (A.size() >= A[0].size()) {
            A = operationR(A);
        }
        else {
            A = transpose(A);
            A = operationR(A);
            A = transpose(A);
        }

        sec++;
    }

    return 0;
}