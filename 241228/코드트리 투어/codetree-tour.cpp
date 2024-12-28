/*
코드트리 랜드 : n개의 도시 0 ~ n-1번
				m개의 간선, 양방향성. 두 도시를 연결하는 간선은 여러 개가 존재할 수 있으며
				자기 자신을 향하는 간선 또한 존재할 수 있음
출발지 : 항상 여행 상품의 출발지를 하나로 통일하여 관리
		 처음 코드트리 여행 상품의 출발지는 0번 도시
관리 목록 : 여행 상품이 들어가 있음.

코드트리 투어 5가지 명령어
1. 코드트리 랜드 건설
2. 여행 상품 생성
(id, revenue_id, dest_id)에 해당하는 여행 상품을 추가로 만들고 이를 관리 목록에 추가
각각 고유 식별자, 여행사가 얻게 되는 매출, 상품의 도착지
3. 여행 상품 취소
id에 해당하는 여행 상품이 존재하는 경우, 해당 id의 여행 상품을 관리 목록에서 삭제
4. 최적의 여행 상품 판매
관리 목록에서 조건에 맞는 최적의 여행 상품을 선택하여 판매
판매 가능한 상품 중에서 우선순위가 높은 상품의 id 출력 후 관리목록에서 삭제
판매 가능한 상품이 전혀 없다면 -1 출력하고 상품을 제거하지 않음.
(revenue_id - cost_id) 최대 id 최소 우선순위
이때 cost_id는 출발지로부터 id상품의 도착지 dest_id까지 도달하기 위한 최단거리
만약 출발지로부터 dest_id에 도달하는 것이 불가능 || cost_id > revenue_id 인 경우
판매 불가 상품
5. 여행 상품의 출발지 변경
여행 상품의 출발지를 전부 s로 변경. 출발지가 변경됨에 따라 각 상품의 cost_id가 변경될 수 있음
*/
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define MAX_N 2000
#define INF (int)1e9

int n, m;
vector<pair<int, int>> graph[MAX_N];
int dist[MAX_N];
int source;

struct Item {
	int id, profit;

	bool operator < (const Item& other) const {
		if (profit != other.profit) return profit < other.profit;
		return id > other.id;
	}
};

unordered_map<int, pair<int, int>> travel_list;
priority_queue<Item> item_pq;

void SetSource() {
	fill(dist, dist + n, INF);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

	dist[source] = 0;
	pq.push({0, source});
	while (!pq.empty()) {
		int min_dist, min_idx;
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

	while (!item_pq.empty()) item_pq.pop();
	for (unordered_map<int, pair<int, int>>::iterator it = travel_list.begin(); it != travel_list.end(); it++) {
		Item new_item;
		new_item.id = it->first;
		new_item.profit = it->second.first - dist[it->second.second];
		item_pq.push(new_item);
	}
}

void ConstructLand() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		graph[v1].push_back({ v2, d });
		graph[v2].push_back({ v1, d });
	}

	SetSource();
}

void AddItem() {
	int id, revenue, dest; cin >> id >> revenue >> dest;
	travel_list[id] = { revenue, dest };

	Item new_item;
	new_item.id = id;
	new_item.profit = revenue - dist[dest];
	item_pq.push(new_item);
}

void DeleteItem() {
	int id; cin >> id;
	if (travel_list.find(id) != travel_list.end()) travel_list.erase(id);
}

void SellItem() {
	while (!item_pq.empty()) {
		Item best_item = item_pq.top();
		item_pq.pop();

		if (travel_list.find(best_item.id) == travel_list.end()) continue;
		if (dist[travel_list[best_item.id].second] == INF || best_item.profit < 0) continue;
		
		cout << best_item.id << "\n";
		travel_list.erase(best_item.id);
		return;
	}
	cout << -1 << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int q; cin >> q;

	source = 0;
	while (q--) {
		int command; cin >> command;
		if (command == 100) ConstructLand();
		else if (command == 200) AddItem();
		else if (command == 300) DeleteItem();
		else if (command == 400) SellItem();
		else if (command == 500) {
			cin >> source;
			SetSource();
		}
	}
}