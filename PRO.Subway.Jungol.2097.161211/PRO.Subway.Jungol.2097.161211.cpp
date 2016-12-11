#include <stdio.h>

int N, M;
int DP[100 + 10][100 + 10];
int PATH[100 + 10][100 + 10][100 + 10];
int item[100 + 10][100 + 10];

#define myMin(a,b) a>b ? b: a

int do_dp()
{
	int ret = 0;

	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				int t1 = DP[i][j];
				int t2 = item[i][k] + item[k][j];
				if (t1 > t2)
				{
					DP[i][j] = t2;
					for (int l = 1; l <= N; l++)
					{
						if (PATH[i][j][l] == 0)
						{
							PATH[i][j][l] = k;
							break;
						}
					}
				}
			}
		}
	}

	return ret;
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &item[i + 1][j + 1]);
			DP[i + 1][j + 1] = item[i + 1][j + 1];
		}
	}

	do_dp();

	printf("%d\n", DP[1][M]);
	printf("1 ");
	for (int i = 1; i <= N && PATH[1][M][i] != 0; i++)
		printf("%d ", PATH[1][M][i]);
	printf("%d ", M);

	return 0;
}
