//Insight
//������ �����ϸ� �ݺ��� ������ȹ���� ����. 
//�޸������̼��� ����ϸ� stack overflow�� �����Ѵ�.
//mod ������ ó���ؾ� �ϴµ� �������� �Ϸ��� ������ Ÿ���� long���� ��� �Ѵ�. ���ø��� mod ������ �ϸ� �����ϴ�.

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

int Solve2(int begin)//�ݺ��� ������ȹ��
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