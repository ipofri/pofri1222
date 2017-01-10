#include <stdio.h>
#include <iostream>
#include <time.h>

const int FLOOR = 10;
const int ROOM = 10;

void assign(int(*house)[ROOM]);

int main(void)
{
	int house[FLOOR][ROOM];
	int org[FLOOR][ROOM];
	int shelter[FLOOR][3];

	srand(3);

	for (int i = 0; i < FLOOR; i++)
	{
		for (int j = 0; j < ROOM; j++)
		{
			house[i][j] = org[i][j] = rand() % 9 + 1;
		}

		for (int j = 0; j < 3;)
		{
			int tmp = rand() % ROOM;
			if (house[i][tmp] == 0)
				continue;

			shelter[i][j++] = tmp;
			house[i][tmp] = 0;
		}
	}

	clock_t start = clock();
	assign(house);
	double PERPORMANCE = 100000;
	PERPORMANCE -= (clock() - start)* CLOCKS_PER_SEC / 1000;
	double TOTAL = 0.;

	for (int i = 0; i < FLOOR; i++)
	{
		int sum[3] = { 0, };

		for (int j = 0; j < ROOM; j++)
		{
			int k;
			for (k = 0; k < 3; k++)
			{
				if (shelter[i][k] == house[i][j])
				{
					if (sum[k] < 20000)
					{
						sum[k] += abs(org[i][j]);
						TOTAL += abs(shelter[i][k] - j);
					}
					else
						TOTAL += ROOM;

					break;
				}
			}

			if (k == 3)
				TOTAL += ROOM;
		}

		int a = 0;
	}

	printf("TOTAL:%.3f PERP:%.3f", TOTAL / FLOOR / ROOM, PERPORMANCE);

	return 0;
}

#define myMin(a,b) a>b ? b:a
int SubSum[4][ROOM+1] = { 0, };
#define CalSubSum(n, a,b) SubSum[n][b] - SubSum[n][a]

void assign(int(*house)[ROOM])
{
	const int INF = 1234567890;
	for (int i = 0; i < FLOOR; i++)
	{
		int shelter[3] = { 0, };
		int idx = 0;
		for (int j = 0; j < ROOM; j++)
		{
			if (house[i][j] == 0)
				shelter[idx++] = j;
		}

		//case1
		//for (int j = 0; j < ROOM; j++)
		//{
		//	house[i][j] = shelter[rand() % 3];
		//}

		//case2
		//int sum[3] = { 0, };
		//idx = 0;
		//for (int j = 0; j < ROOM; j++)
		//{
		//	if (sum[idx] + house[i][j] > 20000)
		//		idx++;
		//	if (idx >= 3)
		//		idx = 2;

		//	sum[idx] += house[i][j];
		//	house[i][j] = shelter[idx];
		//}

		//case3
		int DP[4][ROOM+1];
		DP[0][0] = 0;
		DP[1][0] = INF;
		DP[2][0] = INF;
		DP[3][0] = INF;

		for (int k = 0; k <= 3; k++)
		{
			for (int j = 1; j <= ROOM; j++)
			{
				if (k == 0)
				{
					DP[k][j] = 0;
				}
				else
				{
					SubSum[k][j] = abs(shelter[k - 1] - j) + SubSum[k][j - 1];
					if (k == 1)
					{
						DP[k][j] = SubSum[k][j];
					}
					else
					{
						DP[k][j] = INF;
					}
					
				}
			}
		}

		int sol_arr[4][ROOM+1] = { 0, };
		for (int k = 2; k <= 3; k++)
		{
			for (int to = k; to <= ROOM; to++)
			{
				for (int from = k; from <= to; from++)
				{
					int a = DP[k - 1][from-1] + CalSubSum(k, from-1, to);
					if (a < DP[k][to])
					{
						DP[k][to] = a;
						sol_arr[k][to] = from;
					}
					else
					{
						int b = 1;
					}
				}
			}
		}

		int b = sol_arr[3][ROOM];
		int a = sol_arr[2][b];
		int c = 0;

		//case4
	}
}

