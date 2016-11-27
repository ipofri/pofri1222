#include <stdio.h>

int N;
typedef struct st
{
	int x;
	int y;
} ST;
ST item[110];
int DP[110];
int ORDER[110];

int comp(int a, int b)
{
	int max1, small1;
	if (item[a].x > item[a].y)
	{
		max1 = item[a].x;
		small1 = item[a].y;
	}
	else
	{
		max1 = item[a].y;
		small1 = item[a].x;
	}
	int max2, small2;
	if (item[b].x > item[b].y)
	{
		max2 = item[b].x;
		small2 = item[b].y;
	}
	else
	{
		max2 = item[b].y;
		small2 = item[b].x;
	}

	if (max1 > max2)
	{
		return 1;
	}
	else if (max1 == max2)
	{
		if (small1 > small2)
			return 1;
		else if (small1 == small2)
			return 0;
		else
			return -1;
	}
	else
		return -1;
}

int stackPossible(int a, int b) //a over b
{
	int max1, small1;
	if (item[a].x > item[a].y)
	{
		max1 = item[a].x;
		small1 = item[a].y;
	}
	else
	{
		max1 = item[a].y;
		small1 = item[a].x;
	}
	int max2, small2;
	if (item[b].x > item[b].y)
	{
		max2 = item[b].x;
		small2 = item[b].y;
	}
	else
	{
		max2 = item[b].y;
		small2 = item[b].x;
	}

	if (max1 <= max2 && small1 <= small2)
		return 1;
	
	return 0;
}

void qsort(int low, int high)
{
	if (low >= high)
		return;

	int pivot = low;
	int i = low;
	int j = high;

	while (i < j)
	{
		while (comp(i, pivot) >= 0 && i > high) i++;
		while (comp(j, pivot) < 0) j--;

		if (i<j)
		{
			ST temp = item[i];
			item[i] = item[j];
			item[j] = temp;
		}
	}

	ST temp = item[pivot];
	item[pivot] = item[j];
	item[j] = temp;

	qsort(low, j - 1);
	qsort(j + 1, high);
}

int myMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int Solve(int last)
{
	if (DP[last+1] != 0)
		return DP[last+1];

	int result = 0;

	for (int next = last + 1; next <= N; next++)
	{
		if (stackPossible(next, last))
			result = myMax(result, 1 + Solve(next));
	}

	DP[last+1] = result;

	return result;
}

/*int Solve(int n, int last)
{
	if (n > N)
		return 0;

	if (DP[n][last] != 0)
		return DP[n][last];

	int result = 0;

	if (stackPossible(n, last))
		result = myMax(1 + Solve(n + 1, n), Solve(n + 1, last));
	else
		result = Solve(n + 1, last);

	DP[n][last] = result;

	return result;
}*/

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &item[i].x, &item[i].y);
	}

	qsort(1, N);

	item[0].x = 1000;
	item[0].y = 1000;

	printf("%d", Solve(0));

	return 0;
}