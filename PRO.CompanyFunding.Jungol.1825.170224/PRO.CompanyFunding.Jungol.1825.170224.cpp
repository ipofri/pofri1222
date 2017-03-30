#include <stdio.h>

int Money, N;
int item[21][301];
int DP[21][301];
int DP_VAL[21][301];

int myMax(int a, int b)
{
	if (a > b) return a;
	else
		return b;
}

int Solve()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= Money; j++)
		{
			for (int k = 0; k <= j; k++)
			{
				if (DP[i][j] < DP[i - 1][j - k] + item[i][k])
				{
					DP[i][j] = DP[i - 1][j - k] + item[i][k];
					DP_VAL[i][j] = k;
				}
			}
		}
	}
	return DP[N][Money];
}

int printf_Value(int n, int val)
{
	if (n == 0)
		return 0;
	int tmp = DP_VAL[n][val];
	
	printf_Value(n - 1, val - tmp);

	printf("%d ", tmp);
	
	return 0;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	scanf("%d %d", &Money, &N);
	for (int j = 1; j <= Money; j++)
	{
		int tmp;
		scanf("%d", &tmp);
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &item[i][tmp]);
		}
	}

	printf("%d\n", Solve());
	printf_Value(N, Money);

	return 0;
}