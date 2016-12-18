#include <stdio.h>

int N, M;
int DP[100 + 10][100 + 10];
int PATH[100 + 10][100 + 10];
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
				if (DP[i][j] > DP[i][k] + DP[k][j])
				{
					DP[i][j] = DP[i][k] + DP[k][j];
					PATH[i][j] = k;
				}
			}
		}
	}

	return ret;
}

void printpath(int s, int e)
{
	if (PATH[s][e] == 0) return;
	printpath(s, PATH[s][e]);
	printf("%d ", PATH[s][e]);
	printpath(PATH[s][e], e);
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

	int s = 1;
	int e = M;
	printpath(s, e);
		
	printf("%d ", M);

	return 0;
}
