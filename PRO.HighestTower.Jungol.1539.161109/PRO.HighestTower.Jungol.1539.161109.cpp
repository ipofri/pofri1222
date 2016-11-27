#include <stdio.h>

int N;
typedef struct st
{
	int weight;
	int area;
	int height;
	int no;
} ST;

ST item[110];
int DP[110];
int H[110];

void qsort(int low, int high)
{
	if (low >= high)
		return;

	int i = low;
	int j = high;
	int pivot = i;

	while (i < j)
	{
		while (item[i].area >= item[pivot].area && i <= high)
			i++;
		while (item[j].area < item[pivot].area)
			j--;

		if (i < j)
		{
			ST t;
			t = item[i];
			item[i] = item[j];
			item[j] = t;
		}
	}

	ST t = item[j];
	item[j] = item[pivot];
	item[pivot] = t;

	qsort(low, j - 1);
	qsort(j + 1, high);
}

int myMax(int a, int b)
{
	return a > b ? a : b;
}

int Solve(int last)
{

	if (DP[last+1] != 0)
		return DP[last+1];

	int result = 0;
	for (int i = last+1; i <= N; i++)
	{
		if (item[last].weight > item[i].weight)
		{
			int ar = item[i].height + Solve(i);
			if (ar > result)
			{
				result = ar;
				H[last] = i;
			}
		}
	}

	DP[last+1] = result;

	return result;
}

int main()
{
	freopen("in.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d %d", &item[i].area, &item[i].height, &item[i].weight);
		item[i].no = i;
	}

	qsort(1, N);

	item[0].area = 0x7fffffff;
	item[0].height = 0;
	item[0].weight = 0x7fffffff;
	item[0].no = 0;

	int r = Solve(0);

	int cnt = 0;
	int idx = 0;
	int result[110] = { 0, };
	while (1)
	{
		if (H[idx] != 0)
		{
			idx = H[idx];
			result[cnt] = item[idx].no;
			cnt++;
		}
		else
			break;
	}

	printf("%d\n", cnt);
	for (int i = cnt-1; i >= 0; i--)
		printf("%d\n", result[i]);


	return 0;
}