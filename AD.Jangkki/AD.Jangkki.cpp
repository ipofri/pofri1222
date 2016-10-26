#include <stdio.h>

int N;//row
int M;//col
int R, C, S, K;

typedef struct st
{
	int row, col;
} ST;

int BFS[101][101];
int visited[101][101];

ST myQueue[1000000];
int myStart;
int myEnd;
int myEnque(ST p)
{
	myQueue[myStart++] = p;
	return 0;
}
ST myDeque()
{
	return myQueue[myEnd++];
}

int path[][2] =
{
	{ 2, -1 },
	{ 2, 1 },
	{ -2, -1 },
	{ -2, 1 },

	{ 1, 2 },
	{ -1, 2 },
	{ 1, -2 },
	{ -1, -2 },
};

int Solve()
{
	//초기 위치 추가
	int cnt = 0;
	ST t;
	t.row = R;
	t.col = C;
	BFS[t.row][t.col] = 0;
	visited[t.row][t.col] = 1;
	myEnque(t);

	while (1)
	{
		t = myDeque();
		if (t.row == S && t.col == K)
			return BFS[t.row][t.col];

		for (int i = 0; i < 8; i++)
		{
			ST tmp;
			tmp.row = t.row + path[i][0];
			tmp.col = t.col + path[i][1];

			if (tmp.row>0 && tmp.row <= N && tmp.col > 0 && tmp.col <= M
				&& visited[tmp.row][tmp.col] != 1)
			{
				BFS[tmp.row][tmp.col] = BFS[t.row][t.col] + 1;
				visited[tmp.row][tmp.col] = 1;
				myEnque(tmp);
			}
		}
	}

	return -1;
}

int main(void)
{
	freopen("in.txt", "r", stdin);
	scanf("%d %d %d %d %d %d", &N, &M, &R, &C, &S, &K);

	printf("%d", Solve());

	return 0;
}