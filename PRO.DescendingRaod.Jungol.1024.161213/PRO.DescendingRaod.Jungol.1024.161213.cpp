#include <stdio.h>

typedef struct st
{
	int x, y;
} PATH;

const int INF = 1234567890;
PATH path[4] = {
	{ -1, 0 },
	{ 1, 0 },
	{ 0, 1 },
	{ 0, -1 },
};

int do_dp(int (*item)[502], int (*DP)[502], int M, int N)
{
	if (DP[M][N] != 0)
		return DP[M][N];

	int cnt[4] = { 0, };
	for (int i = 0; i < 4; i++)
	{
		PATH tar;
		tar.y = M + path[i].y;
		tar.x = N + path[i].x;
		int vel_s = item[M][N];
		int vel_t = item[tar.y][tar.x];
		if (item[tar.y][tar.x] > item[M][N])
			cnt[i] = do_dp(item, DP, tar.y, tar.x);
	}

	int sum = 0;
	for (int i = 0; i < 4; i++)
		sum += cnt[i];

	DP[M][N] = sum;

	return sum;
}

int Solve(int (*item)[502], int M, int N)
{
	//initial
	int DP[502][502] = { 0, };
	
	for (int i = 0; i < 502; i++)
	{
		item[0][i] = -1;
		item[501][i] = -1;
		item[i][0] = -1;
		item[i][501] = -1;
	}
	DP[1][1] = 1;

	int ret = do_dp(item, DP, M, N);
	return ret;
}

int main(void)
{
	int M, N;
	int item[502][502] = { 0, };

	freopen("in.txt", "r", stdin);
	scanf("%d %d", &M, &N);
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			scanf("%d", &item[i][j]);
		}
	}

	printf("%d", Solve(item, M, N));
	return 0;
}