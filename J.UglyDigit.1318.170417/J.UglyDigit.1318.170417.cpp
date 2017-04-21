#include <stdio.h>

#define LL long long
LL item[5000];
int N;
int idx;

void swap(LL a, LL b)
{
	LL c = item[a];
	item[a] = item[b];
	item[b] = c;
}

void push(int pos)
{
	if (pos <= 1 || item[pos] >= item[pos / 2]) return;
	swap(pos, pos / 2);
	push(pos / 2);
}

void pop(int pos)
{
	int ch = pos * 2;

	if (ch < idx && item[ch] > item[ch + 1]) ch++;
	if (ch > idx || item[pos] < item[ch]) return;
	swap(pos, ch);
	pop(ch);
}

LL Solve()
{
	int cnt = 0;
	LL ans = 0;
	item[1] = 1;
	idx = 1;
	while (cnt < N)
	{
		while (ans == item[1])
		{
			swap(1, idx--);
			pop(1);
		}
		ans = item[1];
		cnt++;

		item[++idx] = 2 * ans; push(idx);
		item[++idx] = 3 * ans; push(idx);
		item[++idx] = 5 * ans; push(idx);
	}

	return ans;
}
int main()
{
	while (1)
	{
		scanf("%lld", &N);
		if (N == 0)
			break;

		printf("%lld\n", Solve());
	}


}