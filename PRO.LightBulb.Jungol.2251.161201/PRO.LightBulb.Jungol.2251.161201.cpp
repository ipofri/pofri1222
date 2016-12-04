// PRO.LightBulb.Jungol.2251.161201.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

typedef struct ST
{
	int id;
	int target;
} SWITCH;

SWITCH item[10000 + 10];
int DP[10000 + 10];
int PATH[10000 + 10];
int N;
int arr[10000 + 10];

int myMax(int a, int b)
{
	return a > b ? a : b;
}

int do_dp(int last)
{
	if (last > N)
		return 0;

	if (DP[last] != 0)
		return DP[last];

	int max = 0;
	for (int i = last + 1; i <= N; i++)
	{
		if (item[last].target < item[i].target)
		{
			int tmp = 1 + do_dp(i);
			if (max < tmp)
			{
				PATH[last] = i;
				max = tmp;
			}
		}
	}

	DP[last] = max;

	return max;
}

void qsort(int low, int high)
{
	if (low >= high)
		return;

	int l = low;
	int r = high;
	int pivot = arr[l];

	while (l < r)
	{
		while (arr[l] <= pivot && l <= r) l++;
		while (arr[r] > pivot) r--;

		if (l < r)
		{
			int tmp = arr[l];
			arr[l] = arr[r];
			arr[r] = tmp;
		}
	}

	arr[low] = arr[r];
	arr[r] = pivot;

	qsort(low, r - 1);
	qsort(r + 1, high);
}
int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &item[i].id);
	}
	int temp;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &temp);
		for (int j = 1; j <= N; j++)
		{
			if (temp == item[j].id)
			{
				item[j].target = i;
				break;
			}
		}
	}

	int ret = do_dp(0);

	arr[0] = PATH[0];
	for (int i = 1; i < ret; i++)
	{
		arr[i] = PATH[arr[i - 1]];
	}

	printf("%d\n", ret);
	for (int i = 0; i < ret; i++)
	{
		arr[i] = item[arr[i]].id;
	}

	qsort(0, ret - 1);

	for (int i = 0; i < ret; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}
