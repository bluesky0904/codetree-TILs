#include <iostream>
#include <queue>
#include <algorithm>

#define OPERATOR_NUM 4
#define MAX_N 1000000

using namespace std;

enum OPERATOR {
    SUBTRACT,
    ADD,
    DIV2,
    DIV3
};

// 전역 변수 선언:
int n;

// bfs에 필요한 변수들 입니다.
queue<int> q;
bool visited[MAX_N * 2];
int step[MAX_N * 2]; // step[i] : 정점 n에서 시작하여 
                     // 정점 i 지점에 도달하기 위한 
                     // 최단거리를 기록합니다.

int ans;

// num이라는 값에 해당 operator를
// 사용할 수 있는지를 판단합니다.
// 2로 나누거나 3으로 나누려는 경우
// num이 해당 값으로 나누어 떨어질 때에만
// 해당 연산을 사용 가능합니다.
bool Possible(int num, int op) {
    if(op == SUBTRACT || op == ADD)
        return true;
    else if(op == DIV2)
        return num % 2 == 0;
    else
        return num % 3 == 0;
}

// num에 op 연산을 수행했을 때의
// 결과를 반환합니다.
int Calculate(int num, int op) {
    if(op == SUBTRACT)
        return num - 1;
    else if(op == ADD)
        return num + 1;
    else if(op == DIV2)
        return num / 2;
    else
        return num / 3;
};

// 1에서 2n - 1 사이의 숫자만 이용해도
// 올바른 답을 구할 수 있으므로 
// 그 범위 안에 들어오는 숫자인지를 확인합니다.
bool InRange(int num) {
    return 1 <= num && num <= 2 * n - 1;
}

// 1에서 2n - 1 사이의 숫자이면서
// 아직 방문한 적이 없다면 가야만 합니다. 
bool CanGo(int num) {
    return InRange(num) && !visited[num];
}

// queue에 새로운 위치를 추가하고
// 방문 여부를 표시해줍니다.
// 시작점으로 부터의 최단거리 값도 갱신해줍니다.
void Push(int num, int new_step) {
    q.push(num);
    visited[num] = true;
    step[num] = new_step;
}

// BFS를 통해 최소 연산 횟수를 구합니다.
void FindMin() {
    // queue에 남은 것이 없을때까지 반복합니다.
    while(!q.empty()) {
        // queue에서 가장 먼저 들어온 원소를 뺍니다.
        int curr_num = q.front();
        q.pop();

        // queue에서 뺀 원소의 위치를 기준으로 4가지 연산들을 적용해봅니다.
        for(int i = 0; i < OPERATOR_NUM; i++) {
            // 연산을 적용할 수 없는 경우라면 패스합니다.
            if(!Possible(curr_num, i))
                continue;
            
            int new_num = Calculate(curr_num, i);
            // 아직 방문한 적이 없으면서 갈 수 있는 곳이라면
            // 새로 queue에 넣어줍니다.
            if(CanGo(new_num))
                // 최단 거리는 이전 최단거리에 1이 증가하게 됩니다. 
                Push(new_num, step[curr_num] + 1);
        }
    }

    // 1번 정점까지 가는 데 필요한 최소 연산 횟수를
    // 답으로 기록합니다.
    ans = step[1];
}

int main() {
    // 입력:
    cin >> n;

    // BFS를 통해 최소 연산 횟수를 구합니다.
    Push(n, 0);
    FindMin();

    // 출력:
    cout << ans;

    return 0;
}