#include <stdio.h>

int N, M;
typedef struct st {
	int cost;
	int mem;
} APPS;

APPS item[102];
int DP[102][10004];

int INF = 1234567890;

int myMin(int a, int b)
{
	if (a < b) return a;
	return b;
}

int myMax(int a, int b)
{
	if (a>b)
		return a;
	return b;
}

int Solve()
{
	for (int i = 0; i < 102; i++)
	{
		for (int j = 1; j < 10004; j++)
		{
			DP[i][j] = -1;
		}
	}

	for (int i = 1; i <= N; i++)
	{
		int c = item[i].cost;
		int m = item[i].mem;
		for (int j = 10003; j >=0; j--)
		{
			//i-1 의 j cost 보다 i-1 j-c 의 m을 더한 값이 크면 갱신
			if (j>=c && DP[i - 1][j - c] != -1)
				DP[i][j] = myMax(DP[i - 1][j], DP[i - 1][j - c] + m);
			else
				DP[i][j] = myMax(DP[i - 1][j], DP[i][j]);

			//if (j >= c && DP[i - 1][j - c] != -1)
			//	DP[i][j] = myMax(DP[i - 1][j], DP[i - 1][j - c] + m);
		}
	}

	int sol = 0;
	for (int i = 0; i < 10004; i++)
	{
		if (DP[N][i] >= M)
		{
			sol = i;
			break;
		}
	}

	return sol;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &item[i].mem);
	}
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &item[i].cost);
	}

	printf("%d", Solve());

	int a = 0;
}