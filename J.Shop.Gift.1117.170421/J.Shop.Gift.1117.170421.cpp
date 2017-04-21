//network flow 방식,  이분 매칭도 한번 풀어 볼 것
//

#include <iostream>
using namespace std;

const int LM = 500;
int N, M;
int item[LM][LM];
int visited[LM];
int vStep, TAR, SRC;
const int INF = 1 << 30;
int ans;

int myMin(int a, int b) { return a > b ? b : a; }

int DFS(int u, int flow)
{
	if (u == TAR) return flow;

	visited[u] = vStep;
	for (int v = 0; v <= TAR; v++)
	{
		if (visited[v] < vStep && item[u][v] > 0)
		{
			int ret = DFS(v, myMin(item[u][v], flow));
			if (ret)
			{
				item[u][v] -= ret;
				item[v][u] += ret;
				return ret;
			}
		}
	}

	return 0;
}

int main()
{
	freopen("in.txt", "r", stdin);

	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		int temp, val;
		item[0][i] = 1;
		scanf("%d", &temp);
		for (int j = 1; j <= temp; j++)
		{
			scanf("%d", &val);
			item[i][N + val] = 1;
		}
	}

	TAR = N + M + 1;

	for (int i = N + 1; i <= TAR; i++) item[i][TAR] = 1;

	vStep = 1;
	for (; DFS(0, INF); vStep++)
		ans++;

	printf("%d", ans);
	return 0;
}