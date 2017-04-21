#include <stdio.h>

int N;
int tree[1500000];
int arr_idx[1500000];
#define LL long long
LL ans;

LL read(int idx)
{
	if (idx <= 0) return 0;
	return read(idx - (idx & -idx)) + tree[idx];
}

void update(int idx)
{
	if (idx > N) return;
	tree[idx]++;
	update(idx + (idx & -idx));
}
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	scanf("%d", &N);
	int tmp;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &tmp);
		arr_idx[tmp] = i;
	}

	int s, e, k;
	k = 1;
	while (k < N) k *= 2;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &tmp);
		ans += (i - read(arr_idx[tmp]) - 1);
		update(arr_idx[tmp]);
	}

	printf("%lld", ans);

	return 0;
}