#include <stdio.h>

int N;
int item[31]; 
int N_marble;
int item_marble[8];
int DP[31][80010];

void Solve()
{
	DP[0][15000] = 1;
	for (int i = 1; i <= N; i++)
	{
		DP[i][item[i] + 15000] = 1;
		for (int j = 0; j < 30010; j++)
		{
			if (DP[i - 1][j] != 0)
			{
				int a = j - item[i];
				int b = j + item[i];
				DP[i][a] = 1;
				DP[i][b] = 1;
				DP[i][j] = 1;
			}
		}
	}
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &item[i]);
	}
	scanf("%d", &N_marble);
	for (int i = 1; i <= N_marble; i++)
	{
		scanf("%d", &item_marble[i]);
	}

	Solve();

	for (int i = 1; i <= N_marble; i++)
	{
		int a = item_marble[i] + 15000;
		if (DP[N][a] == 1)
			printf("Y ");
		else
			printf("N ");
	}

	return 0;
}