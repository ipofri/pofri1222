// PRO.GlassBallGame.Jungol.1749.161127.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

int B1, B2, B3;
int K1, K2;

int A = 0;
int B = 1;
int DP[2][500 + 10];

void initial()
{
	for (int i = 0; i < 500 + 10; i++)
	{
		DP[A][i] = -1;
		DP[B][i] = -1;
	}
}

int do_DP(int turn, int a, int b)
{
	int ret = A;

	if ( (a>= B1 && a - B1 < B1)
		|| (a >= B2 && a - B2 < B1)
		|| (a >= B3 && a - B3 < B1) )
	{
		ret = turn;
	}
	else
	{
		int c1 = 1 - turn;
		if (a - B1 >= 0)
			c1 = do_DP(1 - turn, a - B1, b);
		int c2 = 1 - turn;
		if (a - B2 >= 0)
			c2 = do_DP(1 - turn, a - B2, b);
		int c3 = 1 - turn;
		if (a - B3 >= 0)
			c3 = do_DP(1 - turn, a - B3, b);

		if (c1 == turn || c2 == turn || c3 == turn)
			ret = turn;
		else
			ret = 1- turn;
	}

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

	scanf("%d %d %d", &B1, &B2, &B3);
	for (int i = 0; i < 7; i++)
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