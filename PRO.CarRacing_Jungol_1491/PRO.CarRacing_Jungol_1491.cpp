#include <stdio.h>

typedef struct st 
{
	int time;
	int dist;
} ST;

ST item[101];
int item_max_dist;
int item_count;
int DP[102];
int PartialSum[102];
int choosed[102];

int myMin(int a, int b)
{
	if (a > b)
		return b;
	else
		return a;
}

int PS(int p1, int p2)
{
	return PartialSum[p1] - PartialSum[p2];
}

int FindCost(int n)
{
	//end
	if (n == 0)
		return 0;

	//memoization
	if (DP[n] != -1)
		return DP[n];

	int min_val = 0x7fffffff;
	for (int i = n-1; i >= 0; i--)
	{
		int ps = PS(n, i);
		if (ps <= item_max_dist)
		{
			int find_new_val = FindCost(i) + item[i].time;
			if (min_val > find_new_val)
			{
				min_val = find_new_val;
				choosed[n] = i;
			}
		}
	}

	DP[n] = min_val;
	return min_val;
}

int Solve()
{
	for (int i = 0; i < 102; i++)
	{
		DP[i] = -1;
	}

	return FindCost(item_count+1);
}

int main(void)
{
	freopen("in.txt", "r", stdin);
	scanf("%d", &item_max_dist);
	scanf("%d", &item_count);

	for (int i = 0; i <= item_count; i++)
	{
		scanf("%d", &item[i].dist);
		PartialSum[i+1] = item[i].dist + PartialSum[i];
	}
	for (int i = 1; i <= item_count; i++)
	{
		scanf("%d", &item[i].time);
	}

	int ret = Solve();
	printf("%d\n", ret);

	if (ret != 0)
	{
		int arr_list[102];
		int opt_path_count = 0;
		for (int i = item_count + 1; i >= 0;)
		{
			if (choosed[i] != 0)
			{
				arr_list[opt_path_count++] = choosed[i];
				i = choosed[i];
			}
			else
				break;
		}
		printf("%d\n", opt_path_count);
		for (int i = opt_path_count - 1; i >= 0; i--)
		{
			printf("%d ", arr_list[i]);
		}
	}
	return 0;
}