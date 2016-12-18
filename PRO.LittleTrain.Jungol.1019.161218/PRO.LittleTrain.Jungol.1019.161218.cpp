#include <stdio.h>

int N;
int item[50000 + 1];
int M;
int DP[4][50000 + 1];
int subsum[50000 + 1];

#define myMax(a,b) a>b? a: b
#define SubSum(a,b) subsum[b] - subsum[a]

int Solve(int n, int m)
{
	for (int i = 1; i <= 3; i++)
	{
		for (int j = m; j <= n; j++)
		{
			DP[i][j] = myMax(DP[i][j - 1], DP[i-1][j-m] + SubSum(j-m,j));
		}
	}

	return DP[3][n];
}

int main(void)
{
	freopen("in.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &item[i]);
		subsum[i] = subsum[i - 1] + item[i];
	}
	scanf("%d", &M);

	printf("%d", Solve(N, M));

	return 0;
}