//비트 연산 팁 
// . >>3 3으로 나눈 값
// . & 7 8로 나눈 나머지
// Prime 넘버 구할때 2~sqrt(n)까지만 확인하면 된다. (이해 필요)
// 해당 값의 배수만큼 증가하며 지워주고, 남는 값이 Prime 이 되는 방식으로 처리됨

#include <stdio.h>
#include <string.h>
typedef unsigned char uchar;

const int N = 100010;
uchar prime_no[N / 8 + 2];

void SetComposite(int n)
{
	prime_no[n >> 3] &= ~(0x01 << (n & 7));
}

int isPrime(int n)
{
	int ret = prime_no[n >> 3] & (0x01 << (n & 7));

	return ret;
}

int main()
{
	memset(prime_no, 255, sizeof(prime_no));

	SetComposite(0);
	SetComposite(1);

	for (int i = 2; i <= N; i++)
	{
		if (isPrime(i))
		{
			for (unsigned long j = i*i; j <= N; j += i)
			{
				SetComposite(j);
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i <= N; i++)
	{
		if (isPrime(i))
		{
			printf("%d\t", i);
			cnt++;
		}
		if (cnt == 10)
		{
			printf("\n");
			cnt = 0;
		}
	}
}

