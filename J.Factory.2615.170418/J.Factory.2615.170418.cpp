//Index Tree 구현 방법
// 1 2 3 4 5
// 2 4 1 3 5
// 위와 같은 조건에서 크로스 되는 회선을 구한다. 즉 하단 1의 경우 2,4와 겹친다. 3의 경우 4와 겹치므로 총 3이 답이된다.
// 정상적으로 풀 경우 n^2이므로 인덱스 트리를 이용한다.
// 하단 입력 인덱스 부터 마지막까지 이미 추가된 값이 있는지 계산하고 더한다.

#include <stdio.h>

#define LL long long

int N;
int K;
int tree[1500000];
int arr_idx[1500000];

void push(int s)
{
	if (s < 1) return;
	tree[s]++;
	push(s / 2);
}

LL f(int s, int e)
{
	int sum = 0;
	if (s>e) return 0;
	if (s==e) return tree[s];
	if (s % 2 == 1) sum = tree[s++];
	if (e % 2 == 0) sum += tree[e--];
	return f(s / 2, e / 2) + sum;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	int tmp;
	scanf("%d", &N);
	K = 1;
	while (K < N)  K *= 2;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &tmp);
		arr_idx[tmp] = i;
	}
	int s, e;
	LL ans = 0;
	e = K + N - 1;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &tmp);
		s = arr_idx[tmp] + K - 1;
		ans += f(s, e);
		push(s);
	}

	printf("%lld", ans);
}