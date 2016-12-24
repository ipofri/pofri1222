#include <stdio.h>

typedef struct st
{
	int s;
	int t;
}WIRE;

#define myMax(a,b) a>b? a:b

int Solve(WIRE *item, int (*DP), int start, int end)
{
	if (DP[start] != 0)
		return DP[start];

	int ret = 1;
	for (int i = start+1; i <= end; i++)
	{
		int src = item[start].t;
		int tar = item[i].t;
		if (src < tar)
			ret = myMax(ret, 1 + Solve(item, DP, i, end));
	}

	DP[start] = ret;

	return ret;
}

void qsort(WIRE* item, int low, int high)
{
	if (low >= high)
		return;
	int i = low;
	int j = high;
	int p = low;
	while (i<j)
	{
		while (item[i].s <= item[p].s && i <= j) i++;
		while (item[j].s>item[p].s) j--;

		if (i < j)
		{
			WIRE temp;
			temp = item[i];
			item[i] = item[j];
			item[j] = temp;
		}
	}

	WIRE temp;
	temp = item[p];
	item[p] = item[j];
	item[j] = temp;

	qsort(item, low, j - 1);
	qsort(item, j + 1, high);
}

int main(void)
{
	int N;
	WIRE item[101];
	int DP[101] = { 0, };
	freopen("in.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d %d", &item[i].s, &item[i].t);

	item[0].s = 0;
	item[0].t = 0;

	qsort(item, 1, N);

	int ret = Solve(item, DP, 0, N)-1;
	printf("%d", N-ret);

	return 0;
}