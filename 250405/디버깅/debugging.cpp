/*
i번 줄의 결과는 무조건 i번으로 가야함
데이터가 제대로 옮겨지지 않는 경우 = 버그
가로선 = 메모리 유실선이 있을 수 있는 위치 = 취약 지점, 이웃한 선과만 이어질 수 있음
메모리 유실선을 추가할 때 선이 겹쳐지도록 추가하는 것은 불가능

최소한의 메모리 유실선을 추가해서 버그를 없애는 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 10;
const int MAXH = 30;
const int INF = 1e9;

int n, m, h; // 고객의 수, 메모리 유실 선의 개수, 취약 지점의 개수
int ans;
int line[MAXH + 10][MAXN + 10];
vector<pair<int, int>> candidate;

int num[MAXN + 10];

bool isPossible() {
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j < n; j++) {
			if (line[i][j] == 1 && line[i][j + 1] == 1) return false;
		}
	}

	for (int i = 1; i <= n; i++) num[i] = i;

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j < n; j++) {
			if (line[i][j]) {
				int tmp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = tmp;
			}
		}
	}

	for (int i = 1; i <= n; i++) if (num[i] != i) return false;

	return true;
}

void selectLine(int cnt, int start) {
	if (cnt >= ans) return;
	if (start >= (int)candidate.size()) return;
	if (cnt > 3) return;
	if (isPossible() && ans > cnt) {
		ans = cnt;
		return;
	}

	selectLine(cnt, start + 1);

	line[candidate[start].first][candidate[start].second] = 1;
	selectLine(cnt + 1, start + 1);
	line[candidate[start].first][candidate[start].second] = 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> n >> m >> h;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j < n; j++) {
			line[i][j] = 0;
		}
	}

	for (int i = 1; i <= m; i++) {
		int a, b; cin >> a >> b;
		line[a][b] = 1;
	}

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j < n; j++) {
			if (!line[i][j]) candidate.push_back({ i, j });
		}
	}
	if (isPossible()) {
		cout << 0 << "\n";
		return 0;
	}
	ans = INF;
	selectLine(0, 0);
	if (ans == INF) cout << -1 << "\n";
	else cout << ans << "\n";
	return 0;
}