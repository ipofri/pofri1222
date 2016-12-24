#include <stdio.h>
#include <iostream>
#include <time.h>

const int FLOOR = 1;
const int ROOM = 10000;

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
			int tmp = rand() % 10000;
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
						TOTAL += 10000;

					break;
				}
			}

			if (k == 3)
				TOTAL += 10000;
		}

		int a = 0;
	}

	printf("TOTAL:%.3f PERP:%.3f", TOTAL / FLOOR / ROOM, PERPORMANCE);

	return 0;
}

#define myMin(a,b) a>b ? b:a
int SubSum[4][10001] = { 0, };
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

		//for (int j = 0; j < ROOM; j++)
		//{
		//	house[i][j] = shelter[rand() % 3];
		//}

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


		int DP[4][10001];
		DP[0][0] = 0;
		DP[1][0] = INF;
		DP[2][0] = INF;
		DP[3][0] = INF;

		for (int k = 0; k <= 3; k++)
		for (int j = 1; j <= ROOM; j++)
		{
			if (k == 0)
			{
				DP[k][j] = 0;
			}
			else
			{
				SubSum[k][j] = abs(shelter[k - 1] - j) + SubSum[k][j - 1];
				DP[k][j] = INF;
			}
		}

		for (int k = 1; k <= 3; k++)
		{
			for (int j = 1; j <= ROOM; j++)
			{
				for (int m = 1; m <= j; m++)
				{
					int a = DP[k - 1][j - m] + CalSubSum(k, j - m, j);
					if (a < DP[k][j])
					{
						DP[k][j] = a;
					}
					//else
					//{
					//	break;
					//}
				}
			}
		}
		int a = 0;
	}
}

