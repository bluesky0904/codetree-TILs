/*
1~N 번호표, 1~N 자리
i분에 ai번째 자리의 사람과 bi번째 자리의 사람이 자리 교환
K분 동안 K번 자리 바꾸기 진행 후 똑같은 방식으로 K번 자리 바꿈이 반복
3K번에 걸쳐 자리바꿈이 진행될 동안, 각자 몇 군데의 자리에 앉을 수 있는지
*/

#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

#define MAX_N 100000
int n, k;

int seats[MAX_N+1];
unordered_set<int> cnt[MAX_N+1];
vector<pair<int, int>> exchange_pair;

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		seats[i] = i;
		cnt[seats[i]].insert(i);
	}
	for (int i = 0; i < k; i++) {
		int a, b; cin >> a >> b;
		exchange_pair.push_back({ a,b });
		cnt[seats[a]].insert(b);
		cnt[seats[b]].insert(a);
		int tmp = seats[a];
		seats[a] = seats[b];
		seats[b] = tmp;
	}
	for (int i = 0; i < exchange_pair.size(); i++) {
		int a = exchange_pair[i].first, b = exchange_pair[i].second;
		cnt[seats[a]].insert(b);
		cnt[seats[b]].insert(a);
		int tmp = seats[a];
		seats[a] = seats[b];
		seats[b] = tmp;
	}
	for (int i = 0; i < exchange_pair.size(); i++) {
		int a = exchange_pair[i].first, b = exchange_pair[i].second;
		cnt[seats[a]].insert(b);
		cnt[seats[b]].insert(a);
		int tmp = seats[a];
		seats[a] = seats[b];
		seats[b] = tmp;
	}
	for (int i = 1; i <= n; i++) {
		cout << cnt[i].size() << "\n";
	}
}