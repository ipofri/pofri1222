#include <stdio.h>

int N;
int W;

typedef struct st
{
	int w;
	int p;
} PRECIUS;

PRECIUS map[1000 + 1];

int DP[1000 + 1][10000 + 1];

int myMax(int a, int b)
{
	return a > b ? a : b; 
}

int Solve(int idx, int weight)
{
	int max = -1;

	if (idx >= N)
		return 0;

	if (DP[idx][weight] != 0)
		return  DP[idx][weight];

	int val1 = 0;
	if (weight - map[idx].w >= 0)
	{
		val1 = map[idx].p + Solve(idx + 1, weight - map[idx].w);
	}
	int val2 = Solve(idx + 1, weight);

	DP[idx][weight] = myMax(val1, val2);
	return DP[idx][weight];
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d %d", &N, &W);
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &map[i].w, &map[i].p);
	}

	printf("%d", Solve(0, W));

	return 0;
}