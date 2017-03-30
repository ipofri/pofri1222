//Insight
//패턴을 이해하면 반복적 동적계획법이 쉽다. 
//메모이제이션을 계산하면 stack overflow를 주의한다.
//mod 연산을 처리해야 하는데 마지막에 하려면 데이터 타입을 long형을 써야 한다. 계산시마다 mod 연산을 하면 간편하다.

#include <stdio.h>

int N;

unsigned long DP[100010];

unsigned long Solve1(int begin)
{
	if (begin >= N)
	{
		return 1;
	}

	unsigned long sum = DP[begin];

	if (sum != 0)
		return sum;

	sum = 1;

	sum = Solve1(begin + 1);

	sum += (2 * Solve1(begin + 2));

	sum %= 20100529;

	DP[begin] = sum;

	return sum;
}

int Solve2(int begin)//반복적 동적계획법
{
	int sum = 0;

	DP[1] = 1;
	DP[2] = 3;

	for (int i = 3; i <= N; i++)
	{
		DP[i] = (DP[i - 1] + 2 * DP[i - 2]) % 20100529;
	}
	return DP[N];
}
int main(void)
{
	scanf("%d", &N);

	printf("%lu", Solve2(1));

	return 0;
}