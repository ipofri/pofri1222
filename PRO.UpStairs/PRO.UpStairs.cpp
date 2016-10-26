#include <stdio.h>

int N;

int item[100000 + 10];
int DP[100000 + 10][2];

int getMax(int t1, int t2)
{
	int tmp;
	if (t1 > t2) tmp = t1; else tmp = t2;

	return tmp;
}

int main(void)
{
	freopen("in2.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &item[i]);

	DP[1][0] = item[1];
	DP[1][1] = item[1];

	DP[2][0] = item[2];
	DP[2][1] = DP[1][0]+item[2];

	int s1, s2;
	for (int i = 3; i <= N; i++)
	{
		DP[i][0] = getMax(DP[i - 2][0] + item[i], DP[i - 2][1] + item[i]);
		DP[i][1] = DP[i - 1][0] + item[i];
	}

	printf("%d", getMax(DP[N][0], DP[N][1]));

	return 0;
}

/*
7
13
1
15
27
29
21
20


CPU Result
96


You Result
104
*/
