/*
격자 : N x M, 모든 위치에는 포탑이 존재 (포탑의 개수는 NM개)
포탑 : 위치, 공격력, 최근 공격턴 (모든 포탑은 시점 0에 모두 공격한 경험이 있다고 가정), 공격 참여 여부(공격하거나 공격받을 때 관리)
공격자
피공격자

상황에 따라 공격력이 줄어들거나 늘어날 수 있음
공격력이 0이하가 된다면, 해당 포탑은 부서지며 더 이상의 공격을 할 수 없음
최초에 공격력이 0인 포탑 즉, 부서진 포탑이 존재할 수 있음

하나의 턴은 다음의 4가지 액션을 순서대로 수행하며, 총 K번 반복
만약 부서지지 않은 포탑이 1개가 된다면 그 즉시 중지
1. 공격자 선정
부서지지 않은 포탑 중 가장 약한 포탑이 공격자로 선정
공격자로 선정되면 가장 약한 포탑이므로, 핸디캡이 적용되어 N + M만큼의 공격력이 증가
가장 약한 포탑의 기준 : 공격력 최소 > 최근 공격턴 최대 > 포탑 위치의 행과 열의 합 최대 > 포탑 위치의 열 값이 최대

2. 공격자의 공격
공격자는 자신을 제외한 가장 강한 포탑을 공격
가장 강한 포탑은 위에서 정한 가장 약한 포탑 선정 기준의 반대
가장 강한 포탑의 기준 : 공격력 최대 > 최근 공격턴 최소 > 포탑 위치의 행과 열의 합 최소 > 포탑 위치의 열 값 최소

공격을 할 때에는 레이저 공격을 먼저 시도하고, 만약 그게 안 된다면 포탄 공격
[레이저 공격]
(1) 상하좌우의 4개의 방향으로 움직일 수 있음
(2) 부서진 포탑이 있는 위치는 지날 수 없음
(3) 가장자리에서 막힌 방향으로 진행하고자 한다면, 반대편으로 나옴
레이저 공격은 공격자의 위치에서 공격 대상 포탑까지의 최단 경로로 공격
만약 경로의 길이가 똑같은 최단 경로가 2개 이상이라면, 우/하/좌/상의 우선순위대로 먼저 움직인 경로가 선택
만약 그러한 경로가 존재하지 않는다면 포탄 공격을 진행

최단 경로가 정해졌으면, 공격 대상에는 공격자의 공격력 만큼의 피해를 입히며, 피해를 입은 포탑은 해당 수치만큼 공격력이 줄어듬
또한 공격 대상을 제외한 레이저 경로에 있는 포탑도 공격을 받게 되는데, 이 포탑은 공격자 공격력의 절반 만큼의 공격을 받음 (절반 = 공격력 / 2)
[포탄 공격]
공격 대상에 포탄을 던짐.
공격 대상은 공격자 공격력만큼의 피해를 받음
추가적으로 주위 8개 방향에 있는 포탑도 피해를 받는데, 공격저 공격력의 절반 만큼의 피해를 받음 (절반 = 공격력 / 2)
공격자는 해당 공격에 영향을 받지 않음
만약 가장자리에 포탄이 떨어졌다면, 위에서 레이저 이동처럼 포탄의 추가 피해가 반대편 격자에 미치게 됨

3. 포탑 부서짐
공격을 받아 공격력이 0 이하가 된 포탑은 부서짐

4. 포탑 정비
공격이 끝났으면, (부서지지 않은 포탑 중) 공격과 무관했던 포탑은 공격력이 1씩 올라감
공격과 무관하다는 뜻은 공격자도 아니고, 공격에 피해를 입은 포탑도 아니라는 뜻

전체 과정이 종료된 후 남아있는 포탑 중 가장 강한 포탑의 공격력을 출력하는 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int GRIDSIZE = 10;

struct Turret {
	int p;
	int t;
	int x;
	int y;

	bool operator < (const Turret& other) const {
		if (p != other.p) return p > other.p;
		if (t != other.t) return t < other.t;
		if (x + y != other.x + other.y) return x + y < other.x + other.y;
		return y < other.y;
	}
};

int N, M, K;
int grid[GRIDSIZE + 10][GRIDSIZE + 10]; // 포탑의 위치와 공격력, 한번만 초기화
int recent_attack[GRIDSIZE + 10][GRIDSIZE + 10]; // 최근 공격턴, 한번만 초기화
int participant[GRIDSIZE + 10][GRIDSIZE + 10]; // 현재 턴 공격 참여 여부, 매턴마다 초기화 필요, 공격하거나 공격받을 때 관리
pair<int, int> attacker;
pair<int, int> attacked;

bool visited[GRIDSIZE + 10][GRIDSIZE + 10];
int raser_route[GRIDSIZE + 10][GRIDSIZE + 10];
int back_x[GRIDSIZE + 10][GRIDSIZE + 10];
int back_y[GRIDSIZE + 10][GRIDSIZE + 10];

void print() {
	cout << "attacker : " << attacker.first << " " << attacker.second << "\n";
	cout << "attacked : " << attacked.first << " " << attacked.second << "\n";
	cout << "\n";

	cout << "grid" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "recent_attack" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << recent_attack[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "participant" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << participant[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

bool isOver() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] > 0) cnt++;
		}
	}

	if (cnt == 1) return true;
	else return false;
}

void selectAttack(int turn) {
	vector<Turret> v;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] > 0) v.push_back({ grid[i][j], recent_attack[i][j], i, j });
		}
	}

	sort(v.begin(), v.end());
	int sz = (int)v.size();
	attacker.first = v[sz - 1].x;
	attacker.second = v[sz - 1].y;
	grid[attacker.first][attacker.second] += (N + M);
	recent_attack[attacker.first][attacker.second] = turn;
	participant[attacker.first][attacker.second] = 1;

	attacked.first = v[0].x;
	attacked.second = v[0].y;
	participant[attacked.first][attacked.second] = 1;
}

bool inRange(int x, int y) {
	return (x >= 0 && x < N && y >= 0 && y < M);
}

bool isWay() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = 0;
			raser_route[i][j] = 0;
		}
	}
	queue<pair<int, int>> q;

	q.push(attacker);
	visited[attacker.first][attacker.second] = true;
	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		if (cx == attacked.first && cy == attacked.second) {

			while (1) {
				int bx = back_x[cx][cy];
				int by = back_y[cx][cy];

				if (bx == attacker.first && by == attacker.second) break;

				raser_route[bx][by] = 1;

				cx = bx;
				cy = by;
			}

			return true;
		}

		int dx[4] = {0,1,0,-1};
		int dy[4] = {1,0,-1,0};
		for (int dir = 0; dir < 4; dir++) {
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];

			if (!inRange(nx, ny)) {
				while (nx < 0) nx += N;
				nx %= N;

				while (ny < 0) ny += M;
				ny %= M;
			}

			if (visited[nx][ny] || grid[nx][ny] == 0) continue;
			
			q.push({ nx, ny });
			visited[nx][ny] = true;
			back_x[nx][ny] = cx;
			back_y[nx][ny] = cy;
		}
	}

	return false;
}

void raserAttack() {
	int damage = grid[attacker.first][attacker.second];
	int half_damage = damage / 2;

	grid[attacked.first][attacked.second] -= damage;
	participant[attacked.first][attacked.second] = 1;


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (raser_route[i][j] == 0) continue;
			grid[i][j] -= half_damage;
			participant[i][j] = 1;
		}
	}
}

void bombAttack() {
	int damage = grid[attacker.first][attacker.second];
	int half_damage = damage / 2;

	int cx = attacked.first;
	int cy = attacked.second;
	grid[cx][cy] -= damage;
	participant[cx][cy] = 1;

	int dx[8] = {-1,-1,0,1,1,1,0,-1};
	int dy[8] = {0,1,1,1,0,-1,-1,-1};
	for (int dir = 0; dir < 8; dir++) {
		int nx = cx + dx[dir];
		int ny = cy + dy[dir];
		if (!inRange(nx, ny)) {
			while (nx < 0) nx += N;
			nx %= N;

			while (ny < 0) ny += M;
			ny %= M;
		}

		if (nx == attacker.first && ny == attacker.second) continue;

		grid[nx][ny] -= half_damage;
		participant[nx][ny] = 1;
	}
}

void attackTurret() {
	if (isWay()) raserAttack();
	else bombAttack();
}

void collapseTurret() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] < 0) grid[i][j] = 0;
		}
	}
}

void recoveryTurret() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] > 0 && participant[i][j] == 0) grid[i][j]++;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("sample_input.txt", "r", stdin);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> grid[i][j];
		}
	}

	//print();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			recent_attack[i][j] = 0;
		}
	}
	for (int turn = 1; turn <= K; turn++) {

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				participant[i][j] = 0;
			}
		}

		//cout << "selectAttack" << "\n";
		selectAttack(turn);
		//print();

		//cout << "attackTurret" << "\n";
		attackTurret();
		//print();

		//cout << "collapseTurret" << "\n";
		collapseTurret();
		if (isOver()) break;
		//print();

		//cout << "recoveryTurret" << "\n";
		recoveryTurret();
		//print();
	}

	int max_power = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (max_power < grid[i][j]) max_power = grid[i][j];
		}
	}
	cout << max_power << "\n";
	return 0;
}