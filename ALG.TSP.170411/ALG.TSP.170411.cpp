#include <stdio.h>
#include <stdlib.h>

const int N = 20;
int map[N][N];
int visited[N];
const int INF = 1234567890;
int DP[N][0x01 << N];

int myMin(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

int tsp_solve1(int here)
{
	int all_visited = 1;
	for (int i = 0; i < N; i++)
	{
		if (visited[i] == 0)
		{
			all_visited = 0;
			break;
		}
	}
	if (all_visited == 1)
		return map[here][0];

	int ret = INF;
	for (int i = 0; i < N; i++)
	{
		if (visited[i] == 0)
		{
			visited[i] = 1;
			ret = myMin(ret, tsp_solve1(i) + map[here][i]);
			visited[i] = 0;
		}
	}

	return ret;
}

int tsp_solve2(int here, int visited)
{
	if (visited == (0x01 << N) - 1)
		return map[here][0];

	if (DP[here][visited] != 0)
		return DP[here][visited];

	int ret = INF;

	for (int i = 0; i < N; i++)
	{
		if ((visited & (0x01 << i)) == 0)
		{
			visited += 0x01 << i;
			ret = myMin(ret, tsp_solve2(i, visited) + map[here][i]);
			visited -= 0x01 << i;
		}
	}

	DP[here][visited] = ret;

	return ret;
}

int main()
{
	srand(3);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			map[i][j] = rand() % 100 + 10;
		}
	}

	visited[0] = 1;
	//printf("%d\n", tsp_solve1(0));
	printf("%d\n", tsp_solve2(0, 1));
}