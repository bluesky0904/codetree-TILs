/*
도시 : n개. 0번 ~ n-1번. 처음 출발지는 0번 도시.
간선 : m개. 방향성x. 두 도시 사이를 연결하는 간선 여러개 가능. 자기 자신을 향하는 것도 가능
(1) 코드트리 랜드 건설
도시의 수 n, 간선의 수 m, 각 간선마다 도시 도시 가중치
(2) 여행 상품 생성
(id, revenue id, dest id)
(3) 여행 상품 취소
고유 식별자 id에 해당하는 여행 상품이 존재하는 경우 목록에서 삭제
(4) 최적의 여행 상품 판매
revenue id - cost id 가 최대 > id가 최소
cost id는 현재 여행 상품의 출발지로부터 id 상품의 도착지 dest id까지 도달하기 위한 최단거리

dest id에 도달하는 것이 불가 or cost id가 revenue id보다 더 큰 경우 -> 판매 불가

(5) 여행 상품의 출발지 변경
여행 상품의 출발지를 전부 s로 변경. cost id가 변경될 수 있음.

다익스트라 알고리즘 -> 각 도시로 가는 최소 비용을 미리 계산
우선순위 큐 -> 수익을 최대화하는 여행상품을 도출
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 0x7fffffff // INT 최대값
#define MAX_N 2000 // 코드트리 랜드의 최대 도시 개수
#define MAX_ID 30005 // 여행상품 ID의 최대값

int N, M;
int A[MAX_N][MAX_N]; // 코드트리 랜드의 간선을 인접 행렬로 표현
int D[MAX_N]; //Dijkstra 알고리즘을 통해 시작도시 S부터 각 도시까지의 최단경로 저장
bool isMade[MAX_ID]; // index에 해당하는 ID를 갖는 상품이 있는지 확인
bool isCancel[MAX_ID]; // index에 해당하는 ID를 갖는 상품이 취소되었는지 확인
int S; // 여행 상품의 출발지

struct Package {
	int id, revenue, dest, profit;

	struct Comparator {
		bool operator()(const Package& a, const Package& b) const {
			if (a.profit == b.profit) {
				return a.id > b.id;
			}
			return a.profit < b.profit;
		}
	};
};

priority_queue<Package, vector<Package>, Package::Comparator> pq;

void dijkstra() {
	bool visited[MAX_N];
	for (int i = 0; i < N; i++) {
		D[i] = INF;
		visited[i] = false;
	}
	D[S] = 0;
	for (int i = 0; i < N - 1; i++) {
		int v = 0, min_dist = INF;
		for (int j = 0; j < N; j++) {
			if (!visited[j] && min_dist > D[j]) {
				v = j;
				min_dist = D[j];
			}
		}
		visited[v] = true;
		for (int j = 0; j < N; j++) {
			if (!visited[j] && D[v] != INF && A[v][j] != INF && D[j] > D[v] + A[v][j]) {
				D[j] = D[v] + A[v][j];
			}
		}
	}
}

void buildLand() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A[i][j] = INF;
		}
		A[i][i] = 0;
	}
	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		A[u][v] = min(A[u][v], w);
		A[v][u] = min(A[v][u], w);
 	}
}

void addPackage(int id, int revenue, int dest) {
	Package p;
	isMade[id] = true;
	p.id = id;
	p.revenue = revenue;
	p.dest = dest;
	p.profit = p.revenue - D[p.dest];

	pq.push(p);
}

void cancelPackage(int id) {
	if (isMade[id]) isCancel[id] = true;
}

int sellPackage() {
	while (!pq.empty()) {
		Package p = pq.top();
		if (p.profit < 0) break;
		pq.pop();
		if (!isCancel[p.id]) return p.id;
	}
	return -1;
}

void changeStart() {
	cin >> S;
	vector<Package> packages;
	dijkstra();
	while (!pq.empty()) {
		packages.push_back(pq.top());
		pq.pop();
	}
	for (Package p : packages) {
		addPackage(p.id, p.revenue, p.dest);
	}
}

int main() {
	int Q, id, revenue, dest;
	cin >> Q;
	while (Q--) {
		int T;
		cin >> T;

		switch(T)
		{
		case 100:
			buildLand();
			dijkstra();
			break;
		case 200:
			cin >> id >> revenue >> dest;
			addPackage(id, revenue, dest);
			break;
		case 300:
			cin >> id;
			cancelPackage(id);
			break;
		case 400:
			cout << sellPackage() << "\n";
			break;
		case 500:
			changeStart();
			break;
		}
	}

	return 0;
}