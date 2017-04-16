#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int C,N;
char W[200], S[200];
int wc, sc;
int DP[200][200];
char item[50][200];
int gc;

int match(int w, int s)
{
	if (w > wc || s > sc)
		return 0;

	if (DP[w][s] != 0)
		return DP[w][s];

	if (w < wc && s < sc)
	{
		if (W[w] == S[s] || W[w] == '?')
		{
			return DP[w][s] = match(w+1, s+1);
		}
	}

	if (w == wc && s == sc)
	{
		return 1;
	}

	int ret = 0;
	if (W[w] == '*')
	{
		if (match(w + 1, s) || match(w, s + 1))
		{
			DP[w][s] = 1;
			ret = 1;
		}
	}
	return ret;
}

void sort_str()
{
	for (int i = 0; i < gc; i++)
	{
		for (int j = i + 1; j < gc; j++)
		{
			if (strcmp(item[i], item[j]) > 0)
			{
				char tmp[200];
				strcpy(tmp, item[i]);
				strcpy(item[i], item[j]);
				strcpy(item[j], tmp);
			}
		}
	}
}
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d", &C);
	for (int c = 0; c < C; c++)
	{
		memset(W, 0, sizeof(W));
		scanf("%s", W);
		wc = 0;
		while (W[wc] != 0)
			wc++;
		scanf("%d", &N);
		gc = 0; 
		for (int i = 0; i < N; i++)
		{
			memset(S, 0, sizeof(S));
			scanf("%s", S);
			sc = 0;
			while (S[sc] != 0)
				sc++;

			memset(DP, 0, sizeof(DP));
			if (match(0, 0) == 1)
				strcpy(item[gc++], S);

		}

		sort_str();
		for (int i = 0; i < gc; i++)
			printf("%s\n", item[i]);
	}
}