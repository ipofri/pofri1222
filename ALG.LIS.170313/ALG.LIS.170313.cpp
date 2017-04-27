//재귀호출 메모이제이션으로 풀이
//각 멤버를 기준으로 해당 값보다 큰 값들에 대한 후보를 선정하고 재귀 메모이제이션 하여 최대값 산출
//사용하지 않는 0 위치 값을 가장 작은 값으로 설정하여 별도로 최고값을 다시 산출하지 않는 것이 팁

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