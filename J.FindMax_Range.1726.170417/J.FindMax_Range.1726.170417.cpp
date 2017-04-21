#include <stdio.h>

int N, Q;
int item[50000 * 3];

int myMax(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int f(int s, int e)
{
	if (s > e)		return 0;
	if (s == e) return item[s];

	int ans = 0;
	if (s % 2 == 1) ans = myMax(ans, item[s++]);
	if (e % 2 == 0) ans = myMax(ans, item[e--]);

	ans = myMax(ans, f(s / 2, e / 2));

	return ans;
}
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d %d", &N, &Q);
	int k = 1;
	while (k < N) k *= 2;
	for (int i = 0; i < N; i++)
		scanf("%d", &item[k + i]);
	for (int i = k - 1; i>=1; i--)
		item[i] = myMax(item[i * 2], item[i * 2 + 1]);

	int s, e;
	for (int i = 0; i < Q; i++)
	{
		scanf("%d %d", &s, &e);

		printf("%d\n", f(k + s - 1, k + e - 1));
	}

	return 0;
}