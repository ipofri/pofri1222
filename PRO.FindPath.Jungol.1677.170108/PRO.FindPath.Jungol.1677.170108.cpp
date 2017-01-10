#include <stdio.h>
int N;
int item[1002][1002];
int DP[1002][1002][3];

int EDGE = -1000;
int INF = -100000000 - 100;

int path[][3] = {
	{ 0, -1 },
	{ -1, 0 },
	{ 0, 1 },
};

#define myMax(a,b) a>b ? a : b 

int do_dp(int y, int x, int sel)
{
	if (y == 1 && x == 1)
	{
		DP[y][x][sel] = item[y][x];
		return item[y][x];
	}

	if (DP[y][x][sel] != INF)
		return DP[y][x][sel];

	int sol = INF;
	for (int i = 0; i < 3; i++)
	{
		if (i == sel && i != 1)
			continue;

		int ty = y + path[i][0];
		int tx = x + path[i][1];
		if (item[ty][tx] != EDGE)
		{
			int tmp = item[y][x] + do_dp(ty, tx, 2 - i);
			sol = myMax(sol, tmp);
		}
	}
	
	DP[y][x][sel] = sol;

	return sol;
}

int main(void)
{
	freopen("in.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i <= N+1; i++)
	{
		for (int j = 0; j <= N+1; j++)
		{
			for (int k=0; k<3; k++) DP[i][j][k] = INF;
			if (i == 0 || i == N + 1 || j == 0 || j == N + 1)
				item[i][j] = EDGE;
			else
				scanf("%d", &item[i][j]);
		}
	}

	printf("%d", do_dp(N,N, 2));
	int a = 1;
}