#include <stdio.h>

int N;

unsigned long DP[100010];

unsigned long Solve(int begin)
{
	if (begin >= N )
	{
		return 1;
	}

	unsigned long &sum = DP[begin];

	if (sum != 0)
		return sum;

	sum = 1;

	sum = Solve(begin + 1);

	sum += (2 * Solve(begin + 2));

	sum %= 20100529;

	return sum;
}

int main(void)
{
	scanf("%d", &N);

	printf("%lu", Solve(1));

	return 0;
}