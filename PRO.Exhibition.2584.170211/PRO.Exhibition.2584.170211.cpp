#include <stdio.h>

typedef struct st {
	int height;
	int cost;
} ST;

int N, S;
ST item[300000 + 2];
int DP[300000 + 2];

void qsort(int low, int high)
{
	if (low >= high)
		return;
	int i = low;
	int j = high;
	int pivot = low;

	while (i < j)
	{
		while (item[i].height <= item[pivot].height && i <= j) i++;
		while (item[j].height > item[pivot].height) j--;

		if (i < j)
		{
			ST tmp = item[i];
			item[i] = item[j]; 
			item[j] = tmp;
		}
	}

	ST tmp = item[pivot];
	item[pivot] = item[j]; 
	item[j] = tmp;

	qsort(low, j-1);
	qsort(j + 1, high);
}

int myMax(int a, int b)
{
	if (a > b)return a;
	else return b;
}

int exhibition(int start)
{
	if (DP[start] != 0)
		return DP[start];

	int max_val = item[start].cost;
	for (int i = start + 1; i <= N; i++)
	{
		if (item[i].height - item[start].height >= S)
			max_val = myMax(max_val, item[start].cost + exhibition(i));
	}

	DP[start] = max_val;

	return max_val;
}

int Solve()
{
	int max_val = 0;
	for (int i = 1; i <= N; i++)
	{
		max_val = myMax(max_val, exhibition(i));
	}

	return max_val;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d %d", &N, &S);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &item[i].height, &item[i].cost);
	}

	qsort(1, N);

	printf("%d", Solve());

	int a = 0;
}
