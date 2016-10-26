#include <stdio.h>

int T;//10

int L;//1~10000;
int K;
int ITEM[101];
int MAP[10000+10];//1~10000
int SEQ;//2~10000
int CACHE[10000 + 10];

int INF = 987654321;

#define myMin(x,y) x>y ? y : x

int resetValue()
{
	for (int i = 0; i < 10000 + 10; i++)
	{
		MAP[i] = 0;
		CACHE[i] = 0;
	}

	return 0;
}

int road(int n)
{
	if (n<0)
		return 0;

	int& ret = CACHE[n];

	if (ret != 0)
		return ret;

	if (MAP[n] == 0)
	{
		ret = road(n - 1);
	}
	else
	{
		if (n - SEQ >= 0)
			ret = road(n - SEQ) + SEQ;
		else
		{
			ret = SEQ;
		}
	}
	return ret;
}

int main(void)
{
	//T 많큼 입력 받는다.
	int l[10];
	int k[10];
	int item[101][10];
	int seq[10];
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf("%d", &l[i]);
		scanf("%d", &k[i]);
		for (int j = 0; j < k[i]; j++)
		{
			scanf("%d", &item[j][i]);
		}
		scanf("%d", &seq[i]);
	}

	for (int i = 0; i < T; i++)
	{
		resetValue();

		L = l[i];
		K = k[i];
		for (int j = 0; j < K; j++)
		{
			MAP[item[j][i]] = 1;
		}
		SEQ = seq[i];

		road(L);

		printf("#%d %d\n", i + 1, CACHE[K]);
	}

	return 0;
}
