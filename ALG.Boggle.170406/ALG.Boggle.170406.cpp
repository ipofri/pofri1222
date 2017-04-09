//완전탐색으로 풀이는 되지만 시간 초과 발생
//탐색 시간을 줄일 수 있는 방법 찾아야 함. (우선 패스)
#include <stdio.h>
#include <string.h>

int C;
int N;
int word_count;

char map[5][7];
char word[11];

int path[8][2] =
{
	{ -1, -1 },
	{ 0, -1 },
	{ 1, -1 },
	{ -1, 0 },
	{ 1, 0 },
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
};

const int dx = 0;
const int dy = 1;

int Solve(int k, int y, int x)
{
	if (k == word_count)
		return 1;

	if (x < 0 || y < 0)
		return 0;
	if (x >= 5 || y >= 5)
		return 0;
	if (word[k] != map[y][x])
		return 0;

	for (int i = 0; i < 8; i++)
	{
		int new_y = y + path[i][dy];
		int new_x = x + path[i][dx];

		if (Solve(k + 1, new_y, new_x) == 1)
			return 1;
	}

	return 0;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	scanf("%d", &C);
	for (int i = 0; i < C; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			memset(map[j], 0, sizeof(map[j]));
			scanf("%s", map[j]);
		}
		scanf("%d", &N);

		for (int k = 0; k < N; k++)
		{
			memset(word, 0, sizeof(word));
			scanf("%s", word);
			word_count = 0;
			while (word[word_count] != 0)
				word_count++;

			int ret = 0;
			for (int y = 0; y < 5; y++)
			{
				for (int x = 0; x < 5; x++)
				{
					if (Solve(0, y, x) == 1)
					{
						ret = 1;
						break;
					}
				}
				if (ret == 1)
					break;
			}

			printf("%s ", word);
			if (ret == 1)
				printf("YES\n");
			else
				printf("NO\n");
		}
		
	}
}