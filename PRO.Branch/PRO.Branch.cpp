#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef struct st {
	int s, e, c;
}ST;

int N;
int R;
int map[1001][1001];
int visited[1001];

int checkLeaf(int node)
{
	int leaf;
	int tar;
	int cnt = 0;
	if (visited[node] != 0)
	{
		leaf = visited[node];
	}
	else
	{
		for (int i = 1; i <= N; i++)
		{
			if (map[node][i] != 0)
			{
				tar = i;
				cnt++;
			}
		}

		if (cnt == 1)//leaf
			leaf = 1;
		else
			leaf = 2;
		visited[node] = leaf;
	}

	return leaf;
}

int findLeastCost(int node, int parents)
{
	int cnt = 0;
	int tar;
	int leaf = checkLeaf(node);

	if (leaf == 1)
		return map[node][parents];

	int upper_cost;
	
	if (node == R)
		upper_cost = 0x7fffffff;
	else
		upper_cost = map[node][parents];

	int lower_cost = 0;
	for (int i = 1; i <= N; i++)
	{
		if (node == i) continue;
		if (parents == i) continue;
		if (map[node][i] == 0) continue;

		lower_cost += findLeastCost(i, node);
	}

	if (upper_cost>lower_cost)
		return lower_cost;
	else
		return upper_cost;

}

void initial()
{
	for (int i = 0; i < 1001; i++)
	{
		visited[i] = 0;
		for (int j = 0; j < 1001; j++)
		{
			map[i][j] = 0;
		}
	}
}

int main(void)
{
	freopen("in2.txt", "r", stdin);

	while (1)
	{
		scanf("%d %d", &N, &R);
		if (N == 0 && R == 0)
			break;

		initial();

		ST tmp;
		for (int i = 1; i <= N - 1; i++)
		{
			scanf("%d %d %d", &tmp.s, &tmp.e, &tmp.c);
			map[tmp.s][tmp.e] = tmp.c;
			map[tmp.e][tmp.s] = tmp.c;
		}

		visited[R] = 2;
		int low_cost = findLeastCost(R, -1);

		printf("%d\n", low_cost);
	}
	return 0;
}