#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_N 8
#define MAX_M 8
#define DIR_NUM 4

using namespace std;

int grid[MAX_N][MAX_M];
int n, m;
vector<pair<int, int> > empty_places;
vector<int> selected_indices;
queue<pair<int, int> > bfs_q;
bool visited[MAX_N][MAX_M];
int max_empty_cnt;

bool CanGo(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m && !visited[x][y] && grid[x][y] != 1;
}

// visited 배열을 초기화 해줍니다.
void InitializeVisited() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            visited[i][j] = false;
}

// BFS 탐색을 위해 존재하는 불을 queue에 넣어줍니다.
void EnqueueFires() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(grid[i][j] == 2){
                bfs_q.push(make_pair(i, j));
                visited[i][j] = true;
            }
}

// 선택된 위치에 방화벽을 설치합니다.
void PlaceFirewalls() {
    for(int i = 0; i < (int) selected_indices.size(); i++) {
        int idx = selected_indices[i];
        int curr_x = empty_places[idx].first;
        int curr_y = empty_places[idx].second;

        grid[curr_x][curr_y] = 1;
    }
}

// 다음 탐색을 위해 설치했던 방화벽을 제거합니다.
void RemoveFirewalls() {
    for(int i = 0; i < (int) selected_indices.size(); i++) {
        int idx = selected_indices[i];
        int curr_x = empty_places[idx].first;
        int curr_y = empty_places[idx].second;

        grid[curr_x][curr_y] = 0;
    }
}

// 선택된 빈 칸에 방화벽을 설치했을 때 영역의 크기를 구합니다.
void GetArea() {

    //0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽
    int dx[DIR_NUM] = {0, 1, 0, -1};
    int dy[DIR_NUM] = {1, 0, -1, 0};

    // BFS 탐색을 위한 초기화 작업을 수행합니다.
    InitializeVisited();
    PlaceFirewalls();
    EnqueueFires();

    // BFS 탐색을 수행합니다.
    while(!bfs_q.empty()) {
        pair<int, int> curr_fire = bfs_q.front();
        int curr_x = curr_fire.first;
        int curr_y = curr_fire.second;
        bfs_q.pop();

        for(int i = 0; i < DIR_NUM; i++) {
            int new_x = curr_x + dx[i];
            int new_y = curr_y + dy[i];

            if(CanGo(new_x, new_y)) {
                bfs_q.push(make_pair(new_x, new_y));
                visited[new_x][new_y] = true;
            }
        }
    }

    // BFS 탐색 과정에서 방문한 적이 없는 빈 칸의 개수를 세줍니다.
    int empty_cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(!visited[i][j] && grid[i][j] == 0)
                empty_cnt++;

    max_empty_cnt = max(empty_cnt, max_empty_cnt);

    // 탐색이 끝난 뒤 설치한 방화벽을 제거해줍니다.
    RemoveFirewalls();
}

void SearchCombinations(int curr_idx, int cnt) {
    if(cnt == 3) {
        GetArea();
        return;
    }
        
    if(curr_idx == (int) empty_places.size()) 
        return;

    selected_indices.push_back(curr_idx);
    SearchCombinations(curr_idx + 1, cnt + 1);
    selected_indices.pop_back();

    SearchCombinations(curr_idx + 1, cnt);
}

int main() {
    cin >> n >> m;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
            
            if(grid[i][j] == 0)
                empty_places.push_back(make_pair(i, j));
        }
    }

    SearchCombinations(0, 0);

    cout << max_empty_cnt;
    return 0;
}
