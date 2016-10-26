#include <stdio.h>

int sol_val[81];

int isPossible(int s, int e)
{
	if (e / 2 < e - s)
		return 1;

	int flag = 0;
	for (int i = 0; i < e-s; i++)
	{
		if (sol_val[s+i] != sol_val[s - (e - s) +i])
		{
			flag = 1;
		}
	}

	if (flag ==0)
		return 0;

	return isPossible(s - 1, e);
}

int main(void)
{
	// 여기서부터 작성
	int N;
	//freopen("in.txt", "r", stdin);
	scanf("%d", &N);

	int lastReturn = 0;
	for (int i = 0; i < N; i++)
	{
		sol_val[i] = 1;
		if (isPossible(i, i + 1) == 1 && lastReturn != 1)
		{
			lastReturn = 0;
			sol_val[i] = 1;
			continue;
		}

		sol_val[i] = 2;
		if (isPossible(i, i + 1) == 1 && lastReturn != 2)
		{
			lastReturn = 0;
			sol_val[i] = 2;
			continue;
		}

		sol_val[i] = 3;
		if (isPossible(i, i + 1) == 1 && lastReturn != 3)
		{
			lastReturn = 0;
			sol_val[i] = 3;
			continue;
		}

		lastReturn = sol_val[i - 1];
		i -= 2;
	}

	for (int i = 0; i < N; i++)
		printf("%d", sol_val[i]);

	return 0;
}
/*Input Data
8


CPU Result
12131231


You Result
12131213
*/