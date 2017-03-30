//문자열 입력시 0번부터 들어오지만 1번부터 입력받게 해야 계산이 편하다.
//이렇게 해서 배열 초기화시 배열 범위를 초과하는 문제가 발생하였다.
//배열초기화 확인 주의하고 , 배열크기를 좀 크게 잡아도 된다.

#include <stdio.h>

char scroll[22];
char bridge[2][102];

int N, M;
int DP[2][22][102];

int Solve(int idx)
{
	int idx2;
	for (int pos = 1; pos < N; pos++)
	{
		char key = scroll[pos];
		idx2 = 1 - idx;

		for (int i = 1; i < M; i++)
		{
			if (key == bridge[idx][i] && DP[idx2][pos - 1][i - 1] != 0)
				DP[idx][pos][i] = DP[idx][pos][i - 1] + DP[idx2][pos - 1][i - 1];
			else
				DP[idx][pos][i] = DP[idx][pos][i - 1];
		}

		idx = idx2;
	}
	return DP[1-idx][N-1][M-1];
}

void init()
{
	for (int i = 0; i <= 1; i++)
		for (int j = 0; j <= N; j++)
			for (int k = 0; k <= M; k++)
				DP[i][j][k] = 0;

	for (int i = 0; i <= 1; i++)
		for (int j = 0; j <= M; j++)
			DP[i][0][j] = 1;

}
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%s", &scroll[1]);
	scanf("%s", &bridge[0][1]);
	scanf("%s", &bridge[1][1]);

	N = M = 1;
	while (scroll[N] != 0) N++;
	while (bridge[1][M] != 0) M++;


	init();
	int sum = Solve(0);
	init();
	sum += Solve(1);
	printf("%d", sum);
	return 0;
}