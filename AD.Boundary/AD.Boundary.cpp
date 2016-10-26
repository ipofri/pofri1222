#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
typedef struct st {
	int y, x;
}ST;

int N;
int map[102][102];
int visited[102][102];
int X, Y;
int sol_count;

int path[][2] =
{
	{ 1, 0 },
	{ -1, 0 },
	{ 0, 1 },
	{ 0, -1 },
};

void DFS(int y, int x)
{
	ST tmp;
	for (int i = 0; i < 4; i++)
	{
		tmp.y = y + path[i][0];
		tmp.x = x + path[i][1];

		if (tmp.y >= 0 && tmp.y <= 101 &&
			tmp.x >= 0 && tmp.x <= 101 &&
			visited[tmp.y][tmp.x] == 0)
		{
			if (map[tmp.y][tmp.x] == 1)
				sol_count++;
			else
			{
				visited[tmp.y][tmp.x] = 1;
				DFS(tmp.y, tmp.x);
			}
		}
	}
}

int main(void)
{
	// 여기서부터 작성
	freopen("in.txt", "r", stdin);
	scanf("%d", &N);
	ST temp;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &temp.x, &temp.y);
		map[temp.y][temp.x] = 1;
	}

	for (int i = 1; i <= 100; i++)
	{
		for (int j = 1; j <= 100; j++)
		{
			map[i][j] = 1;
		}
	}

	DFS(0, 0);

	printf("%d", sol_count);
	return 0;
}