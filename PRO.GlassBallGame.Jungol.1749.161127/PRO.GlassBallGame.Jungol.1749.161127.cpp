// PRO.GlassBallGame.Jungol.1749.161127.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

int B1, B2, B3, BL[3];
int K1, K2;

int A = 0;
int B = 1;
int DP[2][500 + 10][500+10];

void initial()
{
	for (int i = 0; i < 500 + 10; i++)
	{
		for (int j = 0; j < 500 + 10; j++)
		{
			DP[0][i][j] = -1;
			DP[1][i][j] = -1;
		}
	}
}

int do_DP(int turn, int a, int b)
{
	//init condition
	int flag = 0;
	for (int i = 0; i < 3; i++)
	{
		if (a - BL[i] >= 0)
			flag = 1;
		if (b - BL[i] >= 0)
			flag = 1;
	}
	if (flag == 0)
		return 1 - turn;

	//DP condition
	if (DP[turn][a][b] != -1)
		return DP[turn][a][b];

	int condition[6];

	int ret;
	for (int i = 0; i < 3; i++)
	{
		ret = 1 - turn;
		if (a - BL[i] >= 0)
			ret = do_DP(1 - turn, a - BL[i], b);
		if (ret == turn)
			break;
		if (b - BL[i] >= 0)
			ret = do_DP(1 - turn, a, b - BL[i]);
		if (ret == turn)
			break;
	}

	//DP assign
	DP[turn][a][b] = ret;

	return ret;
}

int Solve()
{
	int ret = do_DP(A, K1, K2);

	return ret;
}

int main(void)
{
	freopen("in.txt", "r", stdin);

	scanf("%d %d %d", &BL[0], &BL[1], &BL[2]);
	for (int i = 0; i < 5; i++)
	{
		scanf("%d %d", &K1, &K2);

		initial();

		int ret = Solve();
		if (ret == A)
			printf("A\n");
		else
			printf("B\n");
	}
	return 0;
}