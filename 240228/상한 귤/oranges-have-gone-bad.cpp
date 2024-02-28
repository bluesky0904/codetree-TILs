#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>

#define MAX_N 100
#define DIR_NUM 4

using namespace std;

// 전역 변수 선언:
int n, k;

int a[MAX_N][MAX_N];

vector<pair<int, int> > s_pos;

// bfs에 필요한 변수들 입니다.
queue<pair<int, int> > q;
bool visited[MAX_N][MAX_N];
int step[MAX_N][MAX_N]; // step[i][j] : 
                        // (i, j) 지점에 있는 귤이 
                        // 최초로 상하게 되는 시간을 기록합니다.

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

// 격자를 벗어나지 않으면서, 해당 위치에 귤이 놓여있고, 아직 방문한 적이 없는 곳이라면
// 지금 이동하는 것이 최초로 해당 귤을 상하게 하는 것이므로 가야만 합니다. 
bool CanGo(int x, int y) {
    return InRange(x, y) && a[x][y] && !visited[x][y];
}

// queue에 새로운 위치를 추가하고
// 방문 여부를 표시해줍니다.
// 상하게 되는 시간 값도 갱신해줍니다.
void Push(int nx, int ny, int new_step) {
    q.push(make_pair(nx, ny));
    visited[nx][ny] = true;
    step[nx][ny] = new_step;
}

// bfs를 통해 각 칸마다 최초로 상하게 되는 시간을 구합니다.
void BFS() {
    // queue에 남은 것이 없을때까지 반복합니다.
    while(!q.empty()) {
        // queue에서 가장 먼저 들어온 원소를 뺍니다.
        pair<int, int> curr_pos = q.front();
        int x = curr_pos.first, y = curr_pos.second;
        q.pop();

        int dx[DIR_NUM] = {-1, 1, 0, 0};
        int dy[DIR_NUM] = {0, 0, -1, 1};

        // queue에서 뺀 원소의 위치를 기준으로 4방향을 확인해봅니다.
        for(int dir = 0; dir < DIR_NUM; dir++) {
            int nx = x + dx[dir], ny = y + dy[dir];

            // 아직 방문한 적이 없으면서 갈 수 있는 곳이라면
            // 새로 queue에 넣어줍니다.
            if(CanGo(nx, ny))
                // 시간은 이전 시간에 1이 더해지게 됩니다. 
                Push(nx, ny, step[x][y] + 1);
        }
    }
}

int main() {
    // 입력:
    cin >> n >> k;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			cin >> a[i][j];
			if(a[i][j] == 2)
				s_pos.push_back(make_pair(i, j));
		}
	
    // 처음 상해있던 귤들을
    // 전부 queue에 넣어놓고 시작합니다.
    // 이는 각 칸에 있는 신선한 귤에 대해
    // 가장 가까이에 있던 상한 귤로부터
    // 최초로 상하게 되는 시간을
    // 단 한번의 BFS로 가능하게끔 합니다.
	for(int i = 0; i < (int) s_pos.size(); i++)
		Push(s_pos[i].first, s_pos[i].second, 0);
	
    BFS();

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(a[i][j] == 0)
				cout << -1 << " ";
			else {
				if(!visited[i][j])
					cout << -2 << " ";
				else
					cout << step[i][j] << " ";
			}
		}
		cout << endl;
	}
    return 0;
}