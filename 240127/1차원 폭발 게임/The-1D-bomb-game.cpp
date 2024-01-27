#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> bombs;

void Simulate() {
	int cnt = 1;
	vector<pair<int, int>> explode_pair;
	for (int i = 0; i + 1 < bombs.size(); i++) {
		if (bombs[i] == bombs[i + 1]) cnt++;
		else{
			if (cnt >= M) explode_pair.push_back({ i +1 - cnt, i });
			cnt = 1;
		}
	}
	if (cnt >= M) explode_pair.push_back({ bombs.size()- 1 - cnt+1, bombs.size() - 1});
	
	if (explode_pair.size() == 0) return;

	for (int i = 0; i < explode_pair.size(); i++) {
		for (int j = explode_pair[i].first; j <= explode_pair[i].second;j++) {
			bombs[j] = 0;
		}
	}

	vector<int> tmp;
	for (int i = 0; i < bombs.size(); i++) {
		if (bombs[i] != 0) tmp.push_back(bombs[i]);
	}
	bombs = tmp;

	Simulate();
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	
	for (int i = 0; i < N; i++) {
		int x; cin >> x;
		bombs.push_back(x);
	}

	Simulate();

	cout << bombs.size() << "\n";
	for (int i = 0; i < bombs.size(); i++) {
		cout << bombs[i] << "\n";
	}
}