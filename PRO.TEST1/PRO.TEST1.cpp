#include <stdio.h>

int T;
int C;
int N;

int partial_sum[50*2];
int item[50];
int DP[25 + 1][50 + 1][50 + 1][2];

int min_val;
int max_val;
int sol_val;
int start_idx;
int visited[50];
int INF = 987654321;
unsigned long long skip_count;

int myMax(int x, int y) { return x > y ? x : y; }
int myMin(int x, int y) { return x > y ? y : x; }
int myAbs(int x) { return x > 0 ? x : x*-1; }


int find_min(int c)
{
	int min = INF;

	for (int i = 0; i < c; i++)
	{
		min = myMin(min, visited[i]);
	}

	return min;
}

int find_max(int c)
{
	int max = 0;

	for (int i = 0; i < c; i++)
	{
		max = myMax(max, visited[i]);
	}

	return max;
}

void init_value()
{
	for (int c = 0; c < 25 + 1; c++)
	{
		for (int i = 0; i < 50 + 1; i++)
		{
			for (int j = 0; j < 50 + 1; j++)
			{
				DP[c][i][j][0] = INF;
				DP[c][i][j][1] = -1;
			}
		}
	}
}

int oilCompany(int c, int next)
{
	if (c == C)
	{
		min_val = find_min(c);
		max_val = find_max(c);

		if (sol_val > max_val - min_val)
			sol_val = max_val - min_val;

		return 0;
	}

	if (next >= N)
		return 0;

	int temp_min_val = find_min(c);
	int	temp_max_val = find_max(c);
	if (temp_max_val - temp_min_val > sol_val)
	{
		skip_count++;
		return 0;
	}

	int sum = 0;
	if (c == C - 1)
	{
		visited[c] = partial_sum[N] - partial_sum[next];
		visited[c] += partial_sum[start_idx];

		oilCompany(c + 1, N);
	}
	else
	{
		for (int i = next; i < N; i++)
		{
			visited[c] = partial_sum[i+1] - partial_sum[next];
			oilCompany(c + 1, i+1);
		}
	}

	return 0;
}

int oilcompany2(int c, int next, int init_val)
{
	//기저조건
	if (next > N)
		return 0;

	if (c == C)
	{
		int tmp1 = partial_sum[N] - partial_sum[next - 1] + partial_sum[init_val-1];
		DP[c][next][init_val][0] = tmp1;
		DP[c][next][init_val][1] = tmp1;
		return 0;
	}

	//DP 확인
	if (DP[c][next][init_val][0] != INF)
		return 0;

	int local_min = INF;
	int local_max = -1;
	int local_diff = INF;

	for (int k = next; k <= N; k++)
	{
		oilcompany2(c + 1, k + 1, init_val);
		if (DP[c + 1][k + 1][init_val][0] != INF)
		{
			local_min = myMin(DP[c + 1][k + 1][init_val][0], partial_sum[k] - partial_sum[next - 1]);
		}
		if (DP[c + 1][k + 1][init_val][1] != -1)
		{
			local_max = myMax(DP[c + 1][k + 1][init_val][1], partial_sum[k] - partial_sum[next - 1]);
		}

		if (DP[c + 1][k + 1][init_val][0] != INF)
		{
			local_diff = local_max - local_min;

			if (local_diff < myAbs(DP[c][next][init_val][0] - DP[c][next][init_val][1]))
			{
				DP[c][next][init_val][0] = local_min;
				DP[c][next][init_val][1] = local_max;
			}
		}
	}

	return 0;
}

int Solve()
{
	//for (int i = 1; i < N; i++)
	//{
	//	start_idx = i;
	//	oilCompany(0, i);
	//}

	for (int i= 1; i<= N; i++)
	{
		oilcompany2(1, i, i);
		sol_val = myMin(sol_val, myAbs(DP[1][i][i][1] - DP[1][i][i][0]));
	}

	//int local_min, local_max;
	//for (int c = 1; c <= C; c++)
	//{
	//	int a = 0;
	//	for (int i = c; i <= N; i++)
	//	{
	//		int target_index = N;
	//		if (c == C)
	//			target_index = i;

	//		for (int j = i; j <= target_index; j++)
	//		{
	//			for (int k = 0; k < i; k++)
	//			{
	//				if (c != C)
	//				{
	//					local_min = partial_sum[j] - partial_sum[i - 1];
	//					local_max = partial_sum[j] - partial_sum[i - 1];
	//				}
	//				else
	//				{
	//					local_min += partial_sum[N] - partial_sum[i - 1] + partial_sum[i - 1];
	//					local_max += partial_sum[N] - partial_sum[i - 1] + partial_sum[i - 1];
	//				}

	//				DP[c][i][j][0] = myMin(DP[c - 1][k][i - 1][0], local_min);
	//				DP[c][i][j][1] = myMax(DP[c - 1][k][i - 1][1], local_max);
	//			}
	//		}
	//	}
	//}
	//for (int i= 1; i<= N; i++)
	//{
	//	for (int j = 1; j<= N; j++)
	//		sol_val = myMin(sol_val, myAbs(DP[C][i][j][1] - DP[C][i][j][0]));
	//}

	return 0;
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d", &T);

	for (int i = 0; i < T; i++)
	{
		scanf("%d %d", &C, &N);
		for (int j = 1; j <= N; j++)
		{
			scanf("%d", &item[j]);
			partial_sum[j] = item[j];
			partial_sum[j] += partial_sum[j-1];
		}
		for (int j = N+1; j <= N*2; j++)
		{
			partial_sum[j] += partial_sum[j - 1] + item[j-N];
		}


		skip_count = 0;
		sol_val = INF;
		init_value();
		Solve();
		printf("#%d %d %llu\n", i + 1, sol_val, skip_count);
	}
	return 0;
}