#include <stdio.h>

int T;
int K;
int P[1000 + 1];
int N[1000 + 1];
unsigned long DP[100 + 1][10000 + 1];
unsigned long cnt;

int Coin(int step, int t)
{
	if (t == 0)
		return 1;

	if (t < 0)
		return 0;

	if (step>K)
		return 0;

	if (DP[step][t] != 0)
	{
		cnt++;
		return DP[step][t];
	}

	unsigned long sum = 0;

	for (int i = N[step]; i >=0 ; i--)
	{
		sum += Coin(step + 1, t - i*P[step]);
	}
	DP[step][t] = sum;

	return sum;
}

int Coin2()
{
	for (int i = 1; i <= K; i++)
	{
		for (int j = 1; j <= T; j++)
		{
			for (int k = 0; k <= N[i]; k++)
			{
				if (j < k*P[i])
					break;

				DP[i][j] += DP[i - 1][j - k*P[i]];
			}
		}
	}

	return DP[K][T];
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d", &T);
	scanf("%d", &K);
	DP[0][0] = 1;
	for (int i = 1; i <= K; i++)
	{
		DP[i][0] = 1;
		scanf("%d %d", &P[i], &N[i]);
	}

	unsigned long ret = Coin(1, T);//Coin2();// 

	printf("%lu", ret);

	return 0;
}