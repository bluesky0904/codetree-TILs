#include <iostream>
#include <vector>
#include <tuple>

#define MAX_M 1000
#define INF (long long)1e17 + 1

using namespace std;

// 변수 선언
int a, b, n, m = 1000;
pair<long long, long long> graph[MAX_M + 1][MAX_M + 1]; // (비용, 시간)을 기록
bool visited[MAX_M + 1];

pair<long long, long long> dist[MAX_M + 1];             // (비용, 시간)을 기록

int main() {
    // 입력
    cin >> a >> b >> n;

    // 초기 graph 값에 전부 큰 값 기록
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= m; j++) {
            graph[i][j] = make_pair(INF, 0);
        }
        // 자기 자신은 비용과 시간이 전혀 소요되지 않음
        graph[i][i] = make_pair(0, 0);
    }

    // 그래프를 인접행렬로 표현
    for(int i = 1; i <= n; i++) {
        int cost, stop_num;
        cin >> cost >> stop_num;
        
        vector<int> stops(stop_num);
        for(int j = 0; j < stop_num; j++)
            cin >> stops[j];

        for(int j = 0; j < stop_num; j++) {
            for(int k = j + 1; k < stop_num; k++) {
                graph[stops[j]][stops[k]] = min(graph[stops[j]][stops[k]],
                                                make_pair((long long)cost, (long long)k - j));
            }
        }
    }
    
    // 그래프에 있는 모든 노드들에 대해
    // 초기값을 전부 아주 큰 값으로 설정
    // INT_MAX 그 자체로 설정하면
    // 후에 덧셈 진행시 overflow가 발생할 수도 있으므로
    // 적당히 큰 숫자로 적어줘야함에 유의!
    for(int i = 1; i <= m; i++)
        dist[i] = make_pair(INF, 0);

    // 시작위치에는 dist값을 0으로 설정
    dist[a] = make_pair(0, 0);

    // O(|V|^2) 다익스트라 코드
    for(int i = 1; i <= m; i++) {
        // V개의 정점 중 
        // 아직 방문하지 않은 정점 중
        // dist값이 가장 작은 정점을 찾아줍니다.
        int min_index = -1;
        for(int j = 1; j <= m; j++) {
            if(visited[j])
                continue;
            
            if(min_index == -1 || dist[min_index] > dist[j])
                min_index = j;
        }

        // 최솟값에 해당하는 정점에 방문 표시를 진행합니다.
        visited[min_index] = true;

        long long min_cost, min_time;
        tie(min_cost, min_time) = dist[min_index];

        // 최솟값에 해당하는 정점에 연결된 간선들을 보며
        // 시작점으로부터의 최단거리 값을 갱신해줍니다.
        for(int j = 1; j <= m; j++) {
            long long cost, time;
            tie(cost, time) = graph[min_index][j];
            dist[j] = min(dist[j], make_pair(min_cost + cost, min_time + time));
        }
    }

    // 만약 도달이 불가능하다면 -1 -1이 답이 됩니다.
    if(dist[b] == make_pair(INF, 0LL))
        dist[b] = make_pair(-1, -1);
    
    long long min_cost, min_time;
    tie(min_cost, min_time) = dist[b];

    cout << min_cost << " " << min_time;
    return 0;
}