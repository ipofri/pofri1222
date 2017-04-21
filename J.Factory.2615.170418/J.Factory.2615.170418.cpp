//Index Tree ���� ���
// 1 2 3 4 5
// 2 4 1 3 5
// ���� ���� ���ǿ��� ũ�ν� �Ǵ� ȸ���� ���Ѵ�. �� �ϴ� 1�� ��� 2,4�� ��ģ��. 3�� ��� 4�� ��ġ�Ƿ� �� 3�� ���̵ȴ�.
// ���������� Ǯ ��� n^2�̹Ƿ� �ε��� Ʈ���� �̿��Ѵ�.
// �ϴ� �Է� �ε��� ���� ���������� �̹� �߰��� ���� �ִ��� ����ϰ� ���Ѵ�.

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