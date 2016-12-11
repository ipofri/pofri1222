#include <stdio.h>

int N;
int DP[40];

int Solve(int n)
{
	if (n == 4)
		return 11;
	
	int ret = Solve(n-4)*11
	return 0;
}
int main(void)
{
	scanf("%d", &N);
	printf("%d", Solve(N));
	return 0;
}