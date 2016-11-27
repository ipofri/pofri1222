#include <stdio.h>

int a, b, d, N;
int DP[10000 + 10];

int reArr(int n)
{
	int result = (n + 10000 + 1) % (10000 + 1);
	return result;
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d %d %d %d", &a, &b, &d, &N);

	DP[0] = 1;
	int idx = 0;
	int subSum = 0;

	for (int i = 1; i <= N; i++)
	{
		idx = reArr(idx - 1);

		DP[reArr(idx + d)] = 0;
		int j = DP[reArr(idx + a)];
		int k = DP[reArr(idx + b)];

		subSum -= k;
		subSum += j;

		DP[idx] = subSum%1000;
	}

	int sum = 0;
	int target = reArr(idx + d);
	while (idx != target)
	{
		sum += DP[idx];
		sum %= 1000;
		idx = reArr(++idx);
	}

	printf("%d", sum);
}