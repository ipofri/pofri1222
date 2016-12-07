#include <stdio.h>

int N, K;
int MOD = 1000000003;
int DP[1000 + 10][1000 + 10];

int do_dp(int n, int k)
{
	//initial condition
	if (k > n / 2 + 1)
		return 0;

	if (n < 0)
		return 0;
	if (k < 0)
		return 0;

	if (DP[k][n] != 0)
		return  DP[k][n];

	int ret1 = do_dp(n - 2, k - 1) + do_dp(n-1, k);
	
	DP[k][n] = ret1%MOD;

	return DP[k][n];
}

int do_dp2(int n, int k)
{
	for (int i = 2; i <= k; i++)
	{
		for (int j = 2; j <= n; j++)
		{
			int a = DP[i - 1][j - 2];
			int b = DP[i][j - 1];
			DP[i][j] = (a + b) % MOD;
		}
	}

	return DP[n][k];
}

int Solve()
{
	for (int i = 0; i <= N; i++)
	{
		DP[0][i] = 1;
		DP[1][i] = i;
	}

	int sol = do_dp(N, K);

	int ret1 = DP[K - 1][N - 3] % MOD;
	int ret2 = DP[K][N - 1] % MOD;

	return (ret1 + ret2) % MOD;
}

int main(void)
{
	scanf("%d %d", &N, &K);

	printf("%d", Solve());

	return 0;
}