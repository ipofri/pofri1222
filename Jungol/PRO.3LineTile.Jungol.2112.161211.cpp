#include <stdio.h>

int N;
int DP[40][3];

int Solve(int n,int step)
{
	if (DP[n][step] != -1)
		return DP[n][step];

	int ret = 0;

	if (step == 0)
	{
		ret = Solve(n - 2, 0) * 3 + Solve(n - 2, 1) + Solve(n - 2, 2);
	}
	else if (step == 1)
	{
		ret = Solve(n - 2, 0) + Solve(n - 2, 1);
	}
	else if (step == 2)
	{
		ret = Solve(n - 2, 0) + Solve(n - 2, 2);
	}

	DP[n][step] = ret;

	return ret;
}

int main(void)
{
	scanf("%d", &N);

	for (int i = 2; i < 40; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			DP[i][j] = -1;
		}
	}

	DP[2][0] = 3;
	DP[2][1] = 1;
	DP[2][2] = 1;

	int ret = 0;
	for (int i = 0; i < 3; i++)
	{
		Solve(N, i);
	}

	printf("%d", DP[N][0]);
	return 0;
}