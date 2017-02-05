#include <stdio.h>

int N;
int item[1002];
int DP[1002][1002];

int myMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int Solve()
{
	for (int t = 2; t <= N; t++)
	{
		for (int s = t - 1; s >= 1; s--)
		{
			if ((t + s) % 2 != 0 && item[s] == item[t])
			{
				DP[s][t] = DP[s + 1][t - 1] + 1;
			}
			else
			{
				DP[s][t] = DP[s + 1][t - 1];
			}

			for (int k = s+1; k < t; k+=2)
			{
				int temp = DP[s][k] + DP[k + 1][t];
				DP[s][t] = myMax(DP[s][t], temp);
			}
		}
	}

	return DP[1][N];
}

int Solve2()
{
	for (int t = 2; t <= N; t++)
	{
		for (int s = t - 1; s >= 1; s--)
		{
			if ((t - s) % 2 != 0)
			{
				if (item[s] == item[t])
					DP[s][t] = DP[s + 1][t - 1] + 1;
			}
			else
			{
				DP[s][t] = DP[s + 1][t - 1];
			}
			
			int max = 0;
			for (int k = 2; k < (t - s); k = k + 2)
			{
				int temp = DP[s + ((t - s) + 1 - k)][t] + DP[s][t - k];
				if (max < temp)
				{
					max = temp;
				}
			}

			DP[s][t] = myMax(DP[s][t], max);
		}
	}

	return DP[1][N];
}

int main(void)
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &item[i]);

	int ret = Solve();

	printf("%d", ret);

	return 0;
}