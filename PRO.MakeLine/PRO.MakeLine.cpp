#include <stdio.h>

int N;
int map[201];
int DP[201];

int MyMax(int a, int b) { return a > b ? a : b; };

int lis(int start)
{
	// base condition
	if (start >= N)
		return 0;

	if (DP[start] != 0)
		return DP[start];

	int max_val = 1;

	for (int i = start + 1; i < N; i++)
	{
		if (map[start] < map[i])
		{
			max_val = MyMax(max_val, 1 + lis(i));
		}
	}

	DP[start] = max_val;

	return max_val;
}
int Solve()
{
	int max_val = -1;
	for (int i = 0; i < N; i++)
		max_val = MyMax(max_val, lis(i));

	return N - max_val;
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &map[i]);
	}

	printf("%d", Solve());
	return 0;
}