#include <stdio.h>
#include <stdlib.h>
int N, C;
int item[100000 + 10];
int buf[100000 + 10];

void msort(int s, int e)
{
	if (s >= e)
		return;

	int m = (s + e) / 2;
	msort(s, m);
	msort(m + 1, e);

	int i = s;
	int j = m + 1;
	int k = s;
	
	while (i <= m && j <= e) buf[k++] = item[i] < item[j] ? item[i++] : item[j++];
	while (i <= m) buf[k++] = item[i++];
	while (j <= e) buf[k++] = item[j++];

	for (int i = s; i <= e; i++)
		item[i] = buf[i];
}

int main()
{
#ifdef _WIN32
	N = 100;
	C = 1;
	for (int i = 0; i < N; i++)
	{
		item[i] = rand()%100+1;
	}
#else
	scanf("%d %d", &N, &C);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &item[i]);
	}
#endif

	msort(0, N - 1);

	if (C == 0)
	{
		for (int i = 0; i < N; i++)
			printf("%d\n", item[i]);
	}
	else
	{
		for (int i = N - 1; i >= 0; i--)
			printf("%d\n", item[i]);
	}

	return 0;
}