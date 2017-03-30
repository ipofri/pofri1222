#include <stdio.h>

int C, N, item[501];
int DP[501];

int myMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int do_lis(int last)
{
	if (DP[last] != 0)
		return DP[last];
	int ret = 0;
	for (int i = last + 1; i <= N; i++)
	{
		if (item[i] > item[last])
		{
			ret = myMax(ret, do_lis(i) + 1);
		}
	}

	DP[last] = ret;
	return ret;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	scanf("%d", &C);
	for (int i = 0; i < C; i++)
	{
		scanf("%d", &N);
		DP[0] = 0;
		for (int j = 1; j <= N; j++)
		{
			DP[j] = 0;
			scanf("%d", &item[j]);
		}

		printf("%d\n", do_lis(0));
	}
}