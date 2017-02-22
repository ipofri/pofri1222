#include<stdio.h>
int N, M;
char item1[1001];
char item2[1001];

int INF = 1234567890;
int DP[1001][1001];

int myMin(int a, int b)
{
	if (a > b)
		return b;
	else
		return a;	
}

int Solve(int m, int n)
{
	if (m == M+1 && n==N+1)
		return 0;
	if (m > M)
		return INF;

	if (n > N)
		return INF;

	if (DP[m][n] != 0)
		return DP[m][n];

	int ret = INF;

	//same
	if (item1[m] == item2[n])
	{
		ret = myMin(ret, Solve(m + 1, n + 1));
	}
	else
	{
		//change
		ret = myMin(ret, 1 + Solve(m + 1, n + 1));
	}

	//add
	ret = myMin(ret, 1 + Solve(m + 1, n));
	//sub
	ret = myMin(ret, 1 + Solve(m, n + 1));

	DP[m][n] = ret;

	return ret;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	char c;
	scanf("%d", &M);
	scanf("%c", &c);
	for (int i = 1; i <= M; i++)
		scanf("%c", &item1[i]);
	scanf("%d", &N);
	scanf("%c", &c);
	for (int i = 1; i <= N; i++)
		scanf("%c", &item2[i]);

	printf("%d", Solve(1, 1));

	return 0;
}