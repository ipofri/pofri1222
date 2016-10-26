
#include <stdio.h>

#define MIN(x,y) x>y ? y : x

int N;
int W;
int cache[64000+10];

int INF = 0x7fffffff;
int item[10];

int Solve(int w)
{
	if (w <= 0)
		return 0;

	if (cache[w] != INF)
		return cache[w];

	int ret = INF;
	for (int i = 0; i < N; i++)
	{
		int tmp = item[i];
		int ret2 = 0;
		if (w>=tmp)
		{
			ret2 = Solve(w - tmp) + 1;
		}

		if (ret2>0)
			ret = MIN(ret, ret2);
	}

	if (ret != INF)
	{
		cache[w] = ret;
	}

	return ret;
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &item[i]);
	}
	scanf("%d", &W);
	for (int i = 0; i <= W; i++)
	{
		cache[i] = INF;
	}
	printf("%d", Solve(W));
	return 0;
}

/*
======== test3.in
5
21 4 33 33 15
15966

======== test3.out
Right:
486
*/