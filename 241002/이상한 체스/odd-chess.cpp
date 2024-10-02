#include <stdio.h>

#define MAX (10 + 2)

int T;
int N, M;
int MAP[MAX][MAX];

typedef struct st {
	int r;
	int c;
	int number;
}CAMERA;

CAMERA camera[8 + 2];
CAMERA camera5[8 + 2];
int cidx;
int cidx5;

int minAnswer;

/* 순서대로 왼쪽, 위, 오른쪽, 아래 */
int dr[] = { 0,-1,0,1 };
int dc[] = { -1,0,1,0 };

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= M + 1; c++)
			MAP[r][c] = 6; /* 벽 */

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			int in;

			scanf("%d", &in);
			MAP[r][c] = in;

			if (in == 5)
			{
				camera5[cidx5].r = r;
				camera5[cidx5++].c = c;

				continue;
			}

			if (0 < in && in < 6)
			{
				camera[cidx].r = r;
				camera[cidx].c = c;
				camera[cidx++].number = in;
			}
		}
	}
}

void output(int map[][MAX])
{
	for (int r = 0; r <= N + 1; r++)
	{
		for (int c = 0; c <= M + 1; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
}

void copy(int dest[][MAX], int src[][MAX])
{
	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= M + 1; c++)
			dest[r][c] = src[r][c];
}

void moveChess(int map[][MAX], CAMERA camera, int dir)
{
	int r, c, cnt;

	r = camera.r;
	c = camera.c;

	while (1)
	{
		r = r + dr[dir];
		c = c + dc[dir];

		if (map[r][c] == 6) return;   /* 벽에서는 종료 */

		map[r][c] = '#';
	}
}

void cctvOn(int map[][MAX], CAMERA camera, int dir)
{
	switch (camera.number)
	{
	case 1:
		moveChess(map, camera, dir);
		break;
	case 2:
	{
		int inverse = dir + 2;
		if (inverse > 3) inverse -= 4;

		moveChess(map, camera, dir);
		moveChess(map, camera, inverse);
		break;
	}
	case 3:
	{
		int nextDir = dir + 1;
		if (nextDir == 4) nextDir = 0;

		moveChess(map, camera, dir);
		moveChess(map, camera, nextDir);
		break;
	}
	case 4:
		for (int i = 0; i < 4; i++)
		{
			if (i == dir) continue;
			moveChess(map, camera, i);
		}
		break;

	default:
		break;
	}
}

int getBlindSpot(int map[][MAX])
{
	int cnt = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			cnt += !map[r][c];

	return cnt;
}

void DFS(int L, int map[][MAX])
{
	if (L == cidx)
	{
		int tmp = getBlindSpot(map);

		if (tmp < minAnswer) minAnswer = tmp;

		return;
	}

	int copyMAP[MAX][MAX];

	for (int dir = 0; dir < 4; dir++)
	{

		if (camera[L].number == 2 && dir > 2) return;

		copy(copyMAP, map);

		cctvOn(copyMAP, camera[L], dir);

		DFS(L + 1, copyMAP);
	}
}

int main(void)
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{

		input();
		minAnswer = 0x7fff0000;

		for (int i = 0; i < cidx5; i++)
		{
			for (int dir = 0; dir < 4; dir++)
				moveChess(MAP, camera5[i], dir);
		}

		int map[MAX][MAX] = { 0 };

		copy(map, MAP);

		DFS(0, map);

		printf("%d\n", minAnswer);
	}

	return 0;
}