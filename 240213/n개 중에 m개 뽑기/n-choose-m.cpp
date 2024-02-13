#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> combination;

// 방문한 원소들을 출력해줍니다.
void PrintCombination() {
    for(int i = 0; i < combination.size(); i++)
        cout << combination[i] << " ";
    cout << endl;
}

// 지금까지 뽑은 갯수와 마지막으로 뽑힌 숫자를 추적하여
// 그 다음에 뽑힐 수 있는 원소의 후보를 정합니다.
void FindCombination(int cnt, int last_num) {
    // m개를 모두 뽑은 경우 답을 출력해줍니다.
    if(cnt == m)  {
        PrintCombination();
        return;
    }

    // 뽑을 수 있는 원소의 후보들을 탐색합니다.
    for(int i = last_num + 1; i <= n; i++) { 
        combination.push_back(i);
        FindCombination(cnt + 1, i);
        combination.pop_back();
    }
}

int main() {
    cin >> n >> m;

    // 가능한 범위를 순회하며 해당 숫자가 
    // 조합의 첫번째 숫자일 때를 탐색합니다.
    for(int i = 1; i <= n; i++) {
        combination.push_back(i);
        FindCombination(1, i);
        combination.pop_back();
    }

    return 0;
}