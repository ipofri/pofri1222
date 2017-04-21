#include <stdio.h>
#include <stdlib.h>
int N;
int item[500000 + 10];

void swap(int a, int b)
{
	int c = item[a]; 
	item[a] = item[b];
	item[b] = c;
}
void push(int pos)
{
	if (pos <= 1 || item[pos] <= item[pos / 2]) return;
	swap(pos, pos / 2);
	push(pos / 2);
}

void pop(int pos, int n)
{
	int ch= pos * 2;
	if (ch < n && item[ch] < item[ch + 1]) ch++;
	if (ch > n || item[pos] >= item[ch]) return;
	swap(pos, ch);
	pop(ch, n);
}

void output()
{
	for (int i = 1; i <= N; i++)
		printf("%d ", item[i]);

	printf("\n");
}

void hsort()
{
	for (int i = N; i > 1; i--)
	{
		swap(1, i);
		pop(1, i - 1);
	}
}
int main()
{
#ifdef _WIN32
	N = 20;
	for (int i = 1; i <= N; i++)
	{
		item[i] = rand() % 100;
		push(i);
	}
#else
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &item[i]);
		push(i);
	}
#endif

	output();

	hsort();

	output();

	return 0;
}