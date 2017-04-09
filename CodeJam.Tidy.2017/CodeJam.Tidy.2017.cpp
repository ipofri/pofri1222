#include <stdio.h>

int T;

unsigned long long  isTidy(unsigned long long  n)
{
	int last = n % 10;
	int cur;
	while (n > 0)
	{
		cur = n % 10;
		if (cur > last)
			return 0;

		last = cur;
		n /= 10;
	}

	return 1;
}

unsigned long long  adjustTidy(unsigned long long  n)
{
	int digit[20] = { 0, };
	unsigned long long adjust_no = 0;

	int i;
	for (i = 0; n != 0; i++)
	{
		digit[i] = n % 10;
		n /= 10;
	}

	int upper;
	int lower;
	int cur;

	for (int j = i-1; j > 0; j--)
	{
		unsigned long long exp = 1;
		for (int k = 0; k < j; k++)
			exp *= 10;
		cur = digit[j];
		lower = digit[j-1];
		adjust_no += cur*exp;
		if (cur > lower)
			break;
	}

	n = adjust_no;
	for (i = 0; n != 0; i++)
	{
		digit[i] = n % 10;
		n /= 10;
	}
	
	for (int j = 0; j < i - 1; j++)
	{
		unsigned long long exp = 1;
		for (int k = 0; k < j; k++)
			exp *= 10;
		upper = digit[j + 1];
		cur = digit[j];
		if (cur > upper)
			break;
		else
			adjust_no -= cur*exp;
	}

	return adjust_no;
}
int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	scanf("%d", &T);

	for (int i = 0; i < T; i++)
	{
		unsigned long long n;
		scanf("%llu", &n);
		if (n>9 && !isTidy(n))
			n = adjustTidy(n);
		while (!isTidy(n))
		{
			n--;
		}
		
		printf("Case #%d: %llu\n", i + 1, n);
	}
	fclose(stdout);
}