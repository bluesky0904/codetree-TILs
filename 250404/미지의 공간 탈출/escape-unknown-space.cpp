#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 20;
const int MAXM = 10;
const int MAXID = 1000;
const int INF = 1e9;

struct AbnormalEvent {
	int x;
	int y;
	int d;
	int v;
};

vector<AbnormalEvent> abnormal_events;

int N, M, F;
int id;
int space[MAXN + 10][MAXN + 10]; // 미지의 공간
int spaceId[MAXN + 10][MAXN + 10]; // 미지의 공간
int timewall[5][MAXM + 10][MAXM + 10]; // 시간의벽 : 동 남 서 북 윗면
int timewallId[5][MAXM + 10][MAXM + 10]; // 시간의벽 : 동 남 서 북 윗면

int graph[MAXID + 10][4];
int dist[MAXID + 10];
int start_id, end_id;

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

void print() {
	cout << "space" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << space[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "timewall 동" << "\n";
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cout << timewall[0][i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "timewall 남" << "\n";
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cout << timewall[1][i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "timewall 서" << "\n";
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cout << timewall[2][i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "timewall 북" << "\n";
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cout << timewall[3][i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "timewall 윗" << "\n";
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cout << timewall[4][i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "abnormal times" << "\n";
	for (int i = 0; i < (int)abnormal_events.size(); i++) {
		cout << abnormal_events[i].x << " " << abnormal_events[i].y << " " << abnormal_events[i].d << " " << abnormal_events[i].v << "\n";
	}
}

void connectGrid() {
	for (int i = 1; i <= id; i++) {
		for (int dir = 0; dir < 4; dir++) {
			graph[i][dir] = -1;
		}
	}

	// 밑면
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (space[i][j] == 1 || space[i][j] == 3) continue;

			for (int dir = 0; dir < 4; dir++) {
				int nx = i + dx[dir];
				int ny = j + dy[dir];

				if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

				int idx = spaceId[i][j];
				int idy = spaceId[nx][ny];

				graph[idx][dir] = idy;
			}
		}
	}

	// 측면
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				if (timewall[k][i][j] == 1) continue;

				for (int dir = 0; dir < 4; dir++) {
					int nx = i + dx[dir];
					int ny = j + dy[dir];

					if (nx < 0 || nx >= M) continue;

					if (ny < 0) {
						int idx = timewallId[k][i][j];
						int idy = timewallId[(k + 1) % 4][nx][M - 1];

						graph[idx][dir] = idy;
					}
					else if (ny >= M) {
						int idx = timewallId[k][i][j];
						int idy = timewallId[(k + 3) % 4][nx][0];

						graph[idx][dir] = idy;
					}
					else {
						int idx = timewallId[k][i][j];
						int idy = timewallId[k][nx][ny];

						graph[idx][dir] = idy;
					}
				}
			}
		}
	}

	// 윗면
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (timewall[4][i][j] == 1) continue;

			for (int dir = 0; dir < 4; dir++) {
				int nx = i + dx[dir];
				int ny = j + dy[dir];

				if (nx < 0 || nx >= M || ny < 0 || ny >= M) continue;

				int idx = timewallId[4][i][j];
				int idy = timewallId[4][nx][ny];

				graph[idx][dir] = idy;
			}
		}
	}

	// 윗면과 측면
	for (int i = 0; i < M; i++) {
		int idx = timewallId[4][i][M - 1];
		int idy = timewallId[0][0][M - i - 1];

		graph[idx][0] = idy;
		graph[idy][3] = idx;
	}
	for (int i = 0; i < M; i++) {
		int idx = timewallId[4][M - 1][i];
		int idy = timewallId[1][0][i];

		graph[idx][1] = idy;
		graph[idy][3] = idx;
	}
	for (int i = 0; i < M; i++) {
		int idx = timewallId[4][i][0];
		int idy = timewallId[2][0][i];

		graph[idx][2] = idy;
		graph[idy][3] = idx;
	}
	for (int i = 0; i < M; i++) {
		int idx = timewallId[4][0][i];
		int idy = timewallId[3][0][M - i - 1];

		graph[idx][3] = idy;
		graph[idy][3] = idx;
	}

	// 밑면과 측면
	int start_x = -1;
	int start_y = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (space[i][j] == 3) {
				start_x = i;
				start_y = j;
				break;
			}
		}
		if (start_y != -1) break;
	}

	if (start_x - 1 >= 0) {
		for (int i = 0; i < M; i++) {
			int idx = spaceId[start_x - 1][start_y + i];
			int idy = timewallId[3][M - 1][M - i - 1];

			graph[idx][1] = idy;
			graph[idy][1] = idx;
		}
	}
	
	if (start_y + M < N) {
		for (int i = 0; i < M; i++) {
			int idx = spaceId[start_x + i][start_y + M];
			int idy = timewallId[0][M - 1][M - i - 1];

			graph[idx][2] = idy;
			graph[idy][1] = idx;
		}
	}

	if (start_x + M < N) {
		for (int i = 0; i < M; i++) {
			int idx = spaceId[start_x + M][start_y + i];
			int idy = timewallId[1][M - 1][i];

			graph[idx][3] = idy;
			graph[idy][1] = idx;
		}
	}

	if (start_y - 1 >= 0) {
		for (int i = 0; i < M; i++) {
			int idx = spaceId[start_x + i][start_y - 1];
			int idy = timewallId[2][M - 1][i];

			graph[idx][0] = idy;
			graph[idy][1] = idx;
		}
	}
}

int getStartId() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (timewall[4][i][j] == 2) return timewallId[4][i][j];
		}
	}
}

int getEndId() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (space[i][j] == 4) return spaceId[i][j];
		}
	}
}

void initDist() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (space[i][j] == 1 || space[i][j] == 3) dist[spaceId[i][j]] = INF;
		}
	}

	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				if (timewall[k][i][j] == 1) dist[timewallId[k][i][j]] = INF;
			}
		}
	}
}

void spreadEvent(int turn) {
	vector<AbnormalEvent> tmp;

	for (AbnormalEvent a : abnormal_events) {
		if (turn % a.v == 0) {
			int nx = a.x + dx[a.d];
			int ny = a.y + dy[a.d];
			if (nx >= 0 && nx < N && ny >= 0 && ny < N && space[nx][ny] == 0) {
				dist[spaceId[nx][ny]] = INF;
				tmp.push_back({ nx, ny, a.d, a.v });
			}
		}
		else tmp.push_back(a);
	}

	abnormal_events.clear();
	for (AbnormalEvent a : tmp) {
		abnormal_events.push_back(a);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> N >> M >> F;

	id = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> space[i][j];
			id++;
			spaceId[i][j] = id;
		}
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cin >> timewall[0][i][j];
			id++;
			timewallId[0][i][j] = id;
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cin >> timewall[2][i][j];
			id++;
			timewallId[2][i][j] = id;
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cin >> timewall[1][i][j];
			id++;
			timewallId[1][i][j] = id;
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cin >> timewall[3][i][j];
			id++;
			timewallId[3][i][j] = id;
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cin >> timewall[4][i][j];
			id++;
			timewallId[4][i][j] = id;
		}
	}

	for (int i = 0; i < F; i++) {
		int r, c, d, v; cin >> r >> c >> d >> v;
		dist[spaceId[r][c]] = INF;
		if (d == 0) abnormal_events.push_back({ r, c, 0, v });
		else if(d == 1) abnormal_events.push_back({ r, c, 2, v });
		else if(d == 2) abnormal_events.push_back({ r, c, 1, v });
		else if(d == 3) abnormal_events.push_back({ r, c, 3, v });
	}

	connectGrid();
	start_id = getStartId();
	end_id = getEndId();
	initDist();

	queue<int> q;
	q.push(start_id);
	dist[start_id] = 0;
	int turn = 0;
	while (!q.empty()) {
		vector<int> next_v;

		turn++;
		spreadEvent(turn);

		int q_size = (int)q.size();
		for (int i = 0; i < q_size; i++) {
			int cur = q.front();
			q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int next_id = graph[cur][dir];
				if (next_id == -1 || dist[next_id] != 0) continue;
				next_v.push_back(next_id);
				dist[next_id] = dist[cur] + 1;
			}
		}

		for (int x : next_v) {
			q.push(x);
		}

		if (dist[end_id] != 0) break;
	}
	
	// 타임머신이 시작점에서 탈출구까지 이동하는데 필요한 최소 시간
	if (dist[end_id] == 0) cout << -1 << "\n";
	else cout << dist[end_id] << "\n";
	return 0;
}