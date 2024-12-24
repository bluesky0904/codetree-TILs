/*
출발지 변수
관리 목록 자료구조

코드트리 랜드 :
	n개의 도시 : 0번 ~ n-1번
	m개의 간선 : 양방향 간선.
				 두 도시 사이를 연결하는 간선은 여러 개
				 자기 자신을 향하는 간선 또한 존재할 수 있음

여행 상품의 출발지를 하나로 통일하여 관리
처음 코드트리 여행 상품의 출발지는 0번 도시

코드트리 투어는 5가지 명령에 따라 진행
1. 코드트리 랜드 건설

2. 여행 상품 생성
여행사는 (id, revenue_id, dest_id)에 해당하는 여행 상품을 추가로 만들고 관리 목록에 추가
여행 상품은 고유한 식별자 id를 가지며, 이 여행 상품을 통해 여행사가 얻게되는 매출 revenue_id, 상품의 도착지 dest_id

3. 여행 상품 취소
고유 식별자 id에 해당하는 여행 상품이 존재하는 경우, 해당 id의 여행 상품을 관리 목록에서 삭제합니다.

4. 최적의 여행 상품 판매
관리 목록에서 조건에 맞는 최적인 여행 상품을 선택하여 판매.
선택 조건은 여행사가 이 상품을 판매함으로써 얻게 되는 이득 (revenue_id - cost_id)가 최대인 상품을 우선적으로 고려
같은 값을 가지는 상품이 여러 개 있을 경우 id가 가장 작은 상품을 선택
cost_id는 현재 여행 상품의 출발지로부터 id 상품의 도착지 dest_id까지 도달하기 위한 최단거리
만약 출발지로부터 dest_id에 도달하는 것이 불가능하거나, cost_id가 revenue_id 값보다 큰 경우 판매 불가 상품

코드트리는 판매 가능한 상품 중 가장 우선순위가 높은 상품을 1개 판매
이 상품의 id를 출력한 뒤 관리 목록에서 제거
만약 판매 가능한 상품이 전혀 없다면 -1 출력

5. 여행 상품의 출발지 변경
여행 상품의 출발지를 전부 s로 변경
출발지가 변경됨에 따라 각 상품의 cost_id가 변경

Q번에 걸쳐 명령을 순서대로 진행하며 알맞은 답을 출력하는 프로그램
*/
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <set>
using namespace std;

#define MAX_N 2000
#define INF (int)1e9

int q, n, m;
int source;
vector<pair<int, int>> graph[MAX_N];
int dist[MAX_N];
map<int, pair<int, int>> travel_list;

void construct_land() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		if(v1 == v2) graph[v1].push_back({ v1, d });
		else {
			graph[v1].push_back({ v2, d });
			graph[v2].push_back({ v1, d });
		}
	}
}

void sell_product() {
	set<pair<int, int>> choose_list;

	map<int, pair<int, int>>::iterator it;
	for (it = travel_list.begin(); it != travel_list.end(); it++) {
		int id;
		pair<int, int> info;
		tie(id, info) = *it;
		if (dist[info.second] == INF || info.first < dist[info.second]) continue;
		choose_list.insert({-(info.first - dist[info.second]), id});
	}

	if (choose_list.empty()) {
		cout << -1 << "\n";
	}
	else {
		int id;
		tie(ignore, id) = *choose_list.begin();
		cout << id << "\n";
		travel_list.erase(id);
	}
}

void set_source() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	for (int i = 0; i < n; i++)
		dist[i] = INF;

	dist[source] = 0;
	pq.push({0, source});
	while (!pq.empty()) {
		int min_idx, min_dist;
		tie(min_dist, min_idx) = pq.top();
		pq.pop();

		if (dist[min_idx] != min_dist) continue;

		for (int i = 0; i < (int)graph[min_idx].size(); i++) {
			int next_idx, next_dist;
			tie(next_idx, next_dist) = graph[min_idx][i];

			int new_dist = min_dist + next_dist;
			if (dist[next_idx] > new_dist) {
				dist[next_idx] = new_dist;
				pq.push({ new_dist, next_idx });
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	source = 0;

	cin >> q;
	while (q--) {
		int command; cin >> command;
		if (command == 100) {
			construct_land();
			set_source();
		}
		else if (command == 200) {
			int id, revenue, dest; cin >> id >> revenue >> dest;
			travel_list[id] = make_pair(revenue, dest);
		}
		else if (command == 300) {
			int id; cin >> id;
			travel_list.erase(id);
		}
		else if (command == 400) sell_product();
		else if (command == 500) {
			cin >> source;
			set_source();
		}
	}
}
