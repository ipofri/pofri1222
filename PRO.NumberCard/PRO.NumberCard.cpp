#include <stdio.h>

char item[40+2];
int map[40 + 2];
int N;

int DP[40 + 2][2];

int CountCardArray(int n, int select)
{
	//종료조건
	if (n == 0)
	{
		if (select == 1)
			return 1;
		else
			return 0;
	}

	//계산여부
	if (DP[n][select] != -1)
		return DP[n][select];

	if (select == 0)
	{
		if (n >= 2 && map[n - 1] * 10 + map[n] <= 34 && map[n - 1] * 10 + map[n] > 9)
		{
			int a = CountCardArray(n - 2, 0);
			int b = CountCardArray(n - 2, 1);

			DP[n][select] = a + b;
		}
		else
		{
			DP[n][select] = 0;
		}

	}
	else
	{
		if (map[n] == 0)
			DP[n][select] = 0;
		else
		{
			int a = CountCardArray(n - 1, 0);
			int b = CountCardArray(n - 1, 1);

			DP[n][select] = a + b;
		}
	}

	return DP[n][select];
}

int Solve()
{
	for (int i = 0; i <= 40; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			DP[i][j] = -1;
		}
	}

	return CountCardArray(N, 0) + CountCardArray(N, 1);
}

int main(void)
{
	freopen("in.txt", "r", stdin);
	scanf("%s", item);
	for (int i = 0; i < 40; i++)
	{
		if (item[i] == 0)
			break;
		map[i+1] = item[i] - '0';
		N++;
	}

	printf("%d", Solve());

	return 0;
}
