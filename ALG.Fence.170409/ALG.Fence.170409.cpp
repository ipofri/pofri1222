#include <stdio.h>

int C;
int N;
int item[20000 + 10];

int myMax(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int myMin(int a, int b)
{
	if (a > b)
		return b;
	return a;
}
int CalFence(int left, int right)
{
	if (left == right)
		return item[left];

	int mid = (left + right) / 2;

	int ret;
	ret = myMax(CalFence(left, mid), CalFence(mid + 1, right));

	int lo = mid;
	int hi = mid + 1;
	int height = myMin(item[lo], item[hi]);

	while (lo > left || hi < right)
	{
		if (hi < right && (lo == left || item[lo - 1]<item[hi + 1]))
		{
			hi++;
			height = myMin(height, item[hi]);
		}
		else
		{
			lo--;
			height = myMin(height, item[lo]);
		}
		ret = myMax(ret, height*(hi - lo + 1));
	}

	return ret;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	scanf("%d", &C);
	for (int t = 1; t <= C; t++)
	{
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &item[i]);
		}
		printf("%d\n", CalFence(1, N));
	}
}