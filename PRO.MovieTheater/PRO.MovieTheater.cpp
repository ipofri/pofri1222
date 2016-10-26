#include <stdio.h>

#define myMax( a,   b) a>b ? a : b

int DP[40 + 2][3 + 1];
int N;
int M;
int item[40 + 2];

int isFix(int n)
{
	for (int i = 0; i < M; i++)
	{
		if (item[i] == n)
			return 1;
	}

	return 0;
}

int CountCase(int n, int select)
{
	//End 조건
	if (n == 0)
	{
		if (select == 1)
			return 1;
		else
			return 0;
	}

	//DP 계산 여부
	if (DP[n][select] != -1)
		return DP[n][select];

	//계산
	if (select == 0)
	{
		if (isFix(n) == 1)
			return 0;

		DP[n][select] = CountCase(n - 1, 2);
		return DP[n][select];
	}
	else if (select == 1)
	{
		int a = CountCase(n - 1, 1);
		int b = CountCase(n - 1, 0);

		DP[n][select] = a + b;
		return DP[n][select];
	}
	else
	{
		if (isFix(n) == 1)
			return 0;

		if (n == N)
			return 0;

		int a = CountCase(n - 1, 1);
		int b = CountCase(n - 1, 0);
		
		DP[n][select] = a + b;
		return DP[n][select];
	}
}

int Solve()
{
	int val[3];

	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			DP[i][j] = -1;
		}
	}

	val[0] = CountCase(N, 0);
	val[1] = CountCase(N, 1);
	val[2] = CountCase(N, 2);

	return val[0] + val[1] + val[2];
}

int main(void)
{
	freopen("in.txt", "r", stdin);
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &item[i]);
	}

	printf("%d", Solve());
	return 0;
}