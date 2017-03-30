//���ڿ� �Է½� 0������ �������� 1������ �Է¹ް� �ؾ� ����� ���ϴ�.
//�̷��� �ؼ� �迭 �ʱ�ȭ�� �迭 ������ �ʰ��ϴ� ������ �߻��Ͽ���.
//�迭�ʱ�ȭ Ȯ�� �����ϰ� , �迭ũ�⸦ �� ũ�� ��Ƶ� �ȴ�.

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