//dijkstra
/*
#include <iostream>

const int LM = 110;
int map[LM][LM];
int N, M;
int visited[LM];
int dist[LM];
int path[LM];

int MAX_VAL = 1 << 30;
int myMin(int a, int b)
{
	return a > b ? b : a;
}
void dijk()
{
	int node;
	while (1)
	{
		int min = MAX_VAL;
		for (int i = 1; i <= N; i++)
		{
			if (visited[i] == 0 && dist[i] < min)
			{
				min = dist[i];
				node = i;
			}
		}

		if (node == M) return;
		visited[node] = 1;
		for (int i = 1; i <= N; i++)
		{
			if (visited[i] == 0 && dist[i] > min + map[node][i])
			{
				dist[i] = min + map[node][i];
				path[i] = node;
			}
		}
	}
}

void print_path(int pos)
{
	if (pos < 1) return;
	print_path(path[pos]);
	printf("%d ", pos);
}

int main()
{
	freopen("in.txt", "r", stdin);
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		dist[i] = MAX_VAL;
		for (int j = 1; j <= M; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}

	dist[1] = 0;

	dijk();

	printf("%d\n", dist[M]);

	print_path(M);

	return 0;
}
*/

#include <iostream>

const int LM = 110;
int N, M;
const int MAX_VAL = 1 << 30;
int map[LM][LM];
int path[LM][LM];

int myMin(int a, int b)
{
	return a > b ? b : a;
}

void floyd()
{
	for (int k = 1; k <= N; k++)
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (map[i][j] > map[i][k] + map[k][j])
	{
		map[i][j] = map[i][k] + map[k][j];
		path[i][j] = k;
	}
}

void print_path(int s, int e)
{
	if (path[s][e] == 0) return;
	print_path(s, path[s][e]);
	printf("%d ", path[s][e]);
	print_path(path[s][e], e);
}
int main()
{
	freopen("in.txt", "r", stdin);
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}

	floyd();

	printf("%d\n", map[1][M]);

	printf("%d ", 1);
	print_path(1, M);
	printf("%d ", M);
	return 0;
}