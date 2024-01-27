#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> bombs;

void Simulate() {
	
	while (true) {
		int cnt = 1;
		vector<pair<int, int>> explode_pair;

		for (int i = 0; i < bombs.size(); i++) {
			if (i + 1 < bombs.size() && bombs[i] == bombs[i + 1]) cnt++;
			else {
				if (cnt >= M) explode_pair.push_back({ i + 1 - cnt, i });
				cnt = 1;
			}
		}

		if (explode_pair.size() == 0) return;

		for (int i = 0; i < explode_pair.size(); i++) {
			for (int j = explode_pair[i].first; j <= explode_pair[i].second; j++) {
				bombs[j] = 0;
			}
		}

		vector<int> tmp;
		for (int i = 0; i < bombs.size(); i++) {
			if (bombs[i] != 0) tmp.push_back(bombs[i]);
		}

		bombs = tmp;
	}
	

	/*
	while (true) {
		vector<int> tmp;
		bool exploded = false;
		int cnt = 1;

		for (int i = 0; i < bombs.size(); i++) {
			if (i < bombs.size() - 1 && bombs[i] == bombs[i + 1]) {
				cnt++;
			}
			else {
				if (cnt >= M) {
					exploded = true;
					cnt = 1;
					continue;
				}

				while (cnt > 0) {
					tmp.push_back(bombs[i - cnt + 1]);
					cnt--;
				}
				cnt = 1;
			}
		}

		if (!exploded) break;

		bombs = tmp;
	}
	*/
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	
	bombs.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> bombs[i];
	}

	Simulate();

	cout << bombs.size() << "\n";
	for (int i = 0; i < bombs.size(); i++) {
		cout << bombs[i] << "\n";
	}
}