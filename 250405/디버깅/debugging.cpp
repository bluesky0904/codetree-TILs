#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 10;
const int MAXH = 30;
const int INF = 1e9;

int n, m, h; // 세로선 개수, 기존 가로선의 개수, 가로선을 놓을 수 있는 행의 개수
int ans;
int line[MAXH + 10][MAXN + 10];
vector<pair<int, int>> candidate; // (행, 열) 순으로 후보 위치 저장

int num[MAXN + 10];

// 사다리 타기 시뮬레이션
bool isPossible() {
    // 인접한 선이 동시에 존재하면 사다리 규칙 위반
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j < n; j++) {
            if (line[i][j] == 1 && line[i][j + 1] == 1) return false;
        }
    }
    
    // 초기 번호 할당
    for (int i = 1; i <= n; i++) 
        num[i] = i;
    
    // 각 행마다 선이 있으면 번호 교환
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j < n; j++) {
            if (line[i][j]) {
                int tmp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = tmp;
            }
        }
    }
    
    // 최종 결과가 i번이 i번으로 가는지 확인
    for (int i = 1; i <= n; i++) {
        if (num[i] != i) return false;
    }
    
    return true;
}

// DFS(백트래킹)로 추가 선 선택 (최대 3개)
void dfs(int cnt, int start) {
    // 현재까지 추가한 선의 수가 이미 최적해(ans) 이상이면 탐색 종료
    if (cnt >= ans) return;
    // 올바른 상태가 되면 최적해 갱신 후 종료
    if (isPossible()) {
        ans = cnt;
        return;
    }
    // 최대 3개까지만 추가 가능
    if (cnt == 3) return;
    
    // 후보 위치를 순차적으로 탐색
    for (int i = start; i < candidate.size(); i++) {
        int r = candidate[i].first;
        int c = candidate[i].second;
        // 인접한 선이 이미 있으면 놓을 수 없음 (왼쪽 또는 오른쪽)
        if (line[r][c - 1] || line[r][c + 1]) continue;
        
        // 후보 위치에 선을 추가
        line[r][c] = 1;
        dfs(cnt + 1, i + 1);
        line[r][c] = 0; // 되돌리기
    }
}

int main() {
    ios::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
    //freopen("sample_input.txt", "r", stdin);
    
    cin >> n >> m >> h;
    
    // 초기 상태: 모든 위치에 선 없음 (행: 1~h, 열: 1~n-1)
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j < n; j++) {
            line[i][j] = 0;
        }
    }
    
    // 기존에 배치된 선 입력
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        line[a][b] = 1;
    }
    
    // 추가 가능한 모든 후보 위치 탐색
    // 후보는 행, 열 순으로 정렬되어 들어감
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j < n; j++) {
            if (!line[i][j])
                candidate.push_back({ i, j });
        }
    }
    
    // 초기 상태에서 이미 올바른 경우 0 출력
    if (isPossible()) {
        cout << 0 << "\n";
        return 0;
    }
    
    ans = INF;
    dfs(0, 0);
    
    if (ans == INF) cout << -1 << "\n";
    else cout << ans << "\n";
    
    return 0;
}
