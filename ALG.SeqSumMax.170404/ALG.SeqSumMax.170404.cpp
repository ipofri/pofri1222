#include <stdio.h>
#include <stdlib.h>

const int N = 20001;
int item[N];


int myMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}
int Solve1()
{
	int ret = -9999999;
	for (int i = 1; i < N; i++)
	{
		int sum = 0;
		for (int j = i; j < N; j++)
		{
			sum += item[j];
			ret = myMax(ret, sum);
		}
	}
	return ret;
}
int Solve2()
{
	int ret = -999999;
	int psum = 0;

	for (int i = 1; i < N; i++)
	{
		psum = myMax(0, psum) + item[i];
		ret = myMax(psum, ret);
	}
	return ret;
}
int main()
{
	srand(3);
	for (int i = 1; i < N; i++)
		item[i] = rand() % 100 - 50;

	int ret1 = 0;// Solve1();
	int ret2 = Solve2();

	printf("%d %d", ret1, ret2);
	int a = 1;
}