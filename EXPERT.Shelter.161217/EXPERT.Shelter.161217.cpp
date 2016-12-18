#include <stdio.h>
#include <iostream>
#include <time.h>

const int FLOOR = 10000;
const int ROOM = 10000;

void assign(int (*house)[ROOM]);

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

			if (k==3)
				TOTAL += 10000;
		}

		int a = 0;
	}

	printf("TOTAL:%.3f PERP:%.3f", TOTAL / FLOOR / ROOM, PERPORMANCE);

	return 0;
}

void assign(int (*house)[ROOM])
{
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

		int sum[3] = { 0, };
		idx = 0;
		for (int j = 0; j < ROOM; j++)
		{
			if (sum[idx] + house[i][j] > 20000)
				idx++;
			if (idx >= 3)
				idx = 2;

			sum[idx] += house[i][j];
			house[i][j] = shelter[idx];
		}

		int a = 0;
	}
}

