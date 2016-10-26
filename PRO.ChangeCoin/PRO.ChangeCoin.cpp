#include <stdio.h>

typedef struct st {
	int p, n;
} ST;

int T;
int K;
ST item[101];
int DP[10000 + 10][100];

int main(void)
{
	freopen("in.txt", "r", stdin);
	scanf("%d %d", &T, &K);
	for (int i = 1; i <= K; i++)
		scanf("%d %d", &item[i].p, &item[i].n);

	DP[0][0] = 1;

	for (int i = 1; i <= K; i++)
	{
		DP[0][i] = 1;
	}
	for (int i = 1; i <= K; i++)
	{
		for (int j = 1; j <= T; j++)
		{
			for (int k = 0; k <= item[i].n; k++)
			{
				if (j < k*item[i].p)
					break;

				DP[j][i] += DP[j - k*item[i].p][i-1];
			}

		}
	}

	printf("%d", DP[T][K]);
	return 0;
}