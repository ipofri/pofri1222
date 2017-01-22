#include <stdio.h>

int N;
char item[510];
int DP[510][510];

int myMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int solve_dp(int start, int end)
{
	if (start >= end)
		return 0;

	if (DP[start][end] != 0)
		return DP[start][end];

	int sol = 0;

	//case 1
	if ((item[start] == 'a' && item[end] == 't') ||
		(item[start] == 'g' && item[end] == 'c'))
	{
		sol = myMax(sol, 2 + solve_dp(start + 1, end - 1));
	}

	for (int i = start; i < end; i++)
	{
		sol = myMax(sol, solve_dp(start, i) + solve_dp(i + 1, end));
	}

	DP[start][end] = sol;

	return sol;
}

int solve_dp2(int start, int end)
{
	for (int e = 2; e <= end; e++)
	{
		for (int s = e; s >= 1; s--)
		{
			int sol = 0;

			if ((item[s] == 'a' && item[e] == 't') ||
				(item[s] == 'g' && item[e] == 'c'))
			{
				sol = myMax(sol, 2 + DP[s+1][e-1]);
			}

			for (int k = s; k <= e; k++)
			{
				sol = myMax(sol, DP[s][k] + DP[k][e]);
			}

			DP[s][e] = sol;
		}
	}

	return DP[start][end];
}


int main(void)
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	scanf("%s", item+1);
	int iend = 0;
	for (int i = 1; i < 510; i++)
	{
		if (item[i] == 0)
		{
			iend = i-1;
			break;
		}
	}

	//printf("%d\n", solve_dp(1, iend));
	printf("%d", solve_dp2(1, iend));

	int a = 0;
}