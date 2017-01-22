#include <stdio.h>

int N;
int item[510];
int DP[2][510][510];

#define myMax(a,b) a>b ? a:b

int solve_dp(int n, int a_cnt, int g_cnt, int last)
{
	if (n >= N)
		return 0;

	int sol = 0;

	for (int i = n; i < N; i++)
	{
		int a, b, a_tmp, g_tmp;
		if (item[n] == 2 || item[n] == 3)
		{
			item[n] == 2 ? a_tmp = a_cnt + 1 : a_tmp = a_cnt;
			item[n] == 3 ? g_tmp = g_cnt + 1 : g_tmp = g_cnt;
			a = 1 + solve_dp(n + 1, a_cnt + 1, g_cnt);
			b = solve_dp(n + 1, a_cnt + 1, g_cnt);
		}
		else
		{
			item[n] == 0 ? a_tmp = a_cnt + 1 : a_tmp = a_cnt;
			item[n] == 1 ? a_tmp = a_cnt : g_tmp = g_cnt +1;
			a = 1 + solve_dp(n + 1, a_cnt + 1, g_cnt);
			b = solve_dp(n + 1, a_cnt + 1, g_cnt);
		}
	}

	return 0;
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	char str[510];
	scanf("%s", str);


	for (int i = 0;; i++)
	{
		if (str[i] == 0)
			break;

		if (str[i] == 'a')
			item[N++] = 0;
		else if (str[i] == 't')
			item[N++] = 1;
		else if (str[i] == 'g')
			item[N++] = 2;
		else  if (str[i] == 'c')
			item[N++] = 3;

	}

	printf("%d", solve_dp(0, 0, 0, -1));

	int a = 0;
}