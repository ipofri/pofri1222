#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

typedef struct prs {
	int w, p;
} PRS;

int N, W;
int DP[10001];

int main(void)
{
	freopen("in.txt", "r", stdin);
	scanf("%d %d", &N, &W);
	PRS item;
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &item.w, &item.p);

		for (int j = item.w; j <= W; j++)
		{
			if (DP[j - item.w] + item.p>DP[j])
				DP[j] = DP[j - item.w] + item.p;
		}
	}
	printf("%d", DP[W]);
	return 0;
}