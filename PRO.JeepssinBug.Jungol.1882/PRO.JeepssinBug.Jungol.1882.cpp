#include <stdio.h>

int a, b, d, N;
int DP[10000 + 10];

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d %d %d %d", &a, &b, &d, &N);

	DP[0] = 1;
	int temp;
	for (int i = 1; i <= N; i++)
	{
		temp = 0;
		for (int j = d; j > 0; j--)
		{
			DP[j] = DP[j-1];
			if (j < b && j >= a)
			{
				temp += DP[j];
				temp %= 1000;
			}
		}

		DP[0] = temp;
		DP[d] = 0;

	}

	int sum = 0;
	for (int i = 0; i < d; i++)
	{
		sum += DP[i];
		sum %= 1000;
	}

	printf("%d", sum);
}