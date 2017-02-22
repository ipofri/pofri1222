#include <stdio.h>

char src[1002];
char tar[1002];

int DP[1002][1002];

int M, N;

int myMax(int a, int b)
{
	return a > b ? a : b;
}
int Solve(int m, int n)
{
	if (m >= M || n >= N)
		return 0;

	if (DP[m][n] != 0)
		return DP[m][n];

	int max = 0;

	if (tar[n] == src[m])
	{
		max = myMax(max, 1 + Solve(m + 1, n + 1));
	}
	else
	{
		max = myMax(max, Solve(m + 1, n));
		max = myMax(max, Solve(m, n+1));
	}

	DP[m][n] = max;
	return max;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%s", src);
	scanf("%s", tar);

	while (1)
	{
		if (src[M] == 0)
			break;
		M++;
	}
	while (1)
	{
		if (tar[N] == 0)
			break;
		N++;
	}
	printf("%d", Solve(0,0));

	return 0;
}