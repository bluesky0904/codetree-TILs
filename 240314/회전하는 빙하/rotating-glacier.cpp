#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct Coord {
	int r, c;
};

int M;
int NOW[66][66];
int NEXT[66][66];
int visited[66][66];

int n, q;
vector<int> order;

int numIce, sizeIce;

int dr[] = { 0, 0, -1, 1 };
int dc[] = { -1, 1, 0, 0 };

int isIce(int r, int c)
{
	int cnt = 0;
	for (int i = 0; i < 4; i++)
	{
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (nr < 0 || nc < 0 || nr >= M || nc >= M) continue;
		if (NOW[nr][nc] == 0) continue;
		cnt++;
	}
	if (cnt >= 3) return 1;
	else return 0;
}

void bfs(int sr, int sc, int idx)
{
	int cnt = 1;
	visited[sr][sc] = 1;
	queue<Coord> nowQ;
	nowQ.push({ sr, sc });
	while (!nowQ.empty())
	{
		Coord now = nowQ.front();
		nowQ.pop();
		for (int i = 0; i < 4; i++)
		{
			Coord n = { now.r + dr[i], now.c + dc[i] };
			if (n.r < 0 || n.c < 0 || n.r >= M || n.c >= M) continue;
			if (NOW[n.r][n.c] == 0) continue;
			if (visited[n.r][n.c] != 0) continue;
			visited[n.r][n.c] = idx;
			cnt++;
			nowQ.push({ n.r, n.c });
		}
	}
	if (sizeIce < cnt)
	{
		sizeIce = cnt;
	}
}

void getAnswer()
{
	memset(visited, 0, sizeof(visited));
    // 얼음군집의 인덱스
	int idx = 1;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (visited[i][j] == 0 &&
				NOW[i][j] != 0)
			{
				visited[i][j] = idx;
				bfs(i, j, idx);
				idx++;
			}
		}
	}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			numIce += NOW[i][j];
}

void mapCopy(int A[66][66], int B[66][66])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			A[i][j] = B[i][j];
		}
	}
}

// 빙하는 동시에 녹음
void melt()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (NOW[i][j] == 0)
				NEXT[i][j] = 0;
			else if (!isIce(i, j))
				NEXT[i][j] = NOW[i][j] - 1;
			else
				NEXT[i][j] = NOW[i][j];
		}
	}

	mapCopy(NOW, NEXT);
}

int getPower(int n)
{
	int num = 1;
	for (int i = 1; i <= n; i++)
		num *= 2;
	return num;
}

void rotate(int level)
{
	if (level == 0)
	{
		return;
	}
	memset(NEXT, 0, sizeof(NEXT));
	int outtime = getPower(n - level);
	for (int i = 0; i < outtime; i++)
	{
		for (int j = 0; j < outtime; j++)
		{
			int sr = i * getPower(level);
			int sc = j * getPower(level);
			int intime = getPower(level - 1);
			// 0,0
			for (int a = 0; a < intime; a++)
			{
				for (int b = 0; b < intime; b++)
				{
					int r = sr + a;
					int c = sc + b;
					NEXT[r][c + intime] = NOW[r][c];
				}
			}
			// 0,1
			for (int a = 0; a < intime; a++)
			{
				for (int b = 0; b < intime; b++)
				{
					int r = sr + a;
					int c = sc + b + intime;
					NEXT[r + intime][c] = NOW[r][c];
				}
			}
			// 1,0
			for (int a = 0; a < intime; a++)
			{
				for (int b = 0; b < intime; b++)
				{
					int r = sr + a + intime;
					int c = sc + b;
					NEXT[r - intime][c] = NOW[r][c];
				}
			}
			// 1,1
			for (int a = 0; a < intime; a++)
			{
				for (int b = 0; b < intime; b++)
				{
					int r = sr + a + intime;
					int c = sc + b + intime;
					NEXT[r][c - intime] = NOW[r][c];
				}
			}
		}
	}
	mapCopy(NOW, NEXT);
}

void CLEAR()
{

}

void INPUT()
{
	cin >> n >> q;
	M = getPower(n);
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> NOW[i][j];
		}
	}
	for (int i = 0; i < q; i++)
	{
		int num;
		cin >> num;
		order.push_back(num);
	}
}

void SOLVE()
{
	for (int i = 0; i < q; i++)
	{
		rotate(order[i]);
		melt();
	}
	getAnswer();
	cout << numIce << endl << sizeIce << endl;
}

int main()
{
	CLEAR();
	INPUT();
	SOLVE();

	return 0;
}