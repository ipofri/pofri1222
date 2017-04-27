#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <string.h>

const int LM = 3;
const int TC = 20;
const int MAX_ROTATE = 7;
int Cube[6][LM][LM];
enum PLANE
{
	F,	B,	U,	D,	L,	R, 
};

void initial_cute(int cube[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
	for (int i = 0; i < LM; i++)
	for (int j = 0; j < LM; j++)
		cube[face][i][j] = face;
}
void copy_cube(int src[6][LM][LM], int tar[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
	for (int i = 0; i < LM; i++)
	for (int j = 0; j < LM; j++)
		tar[face][i][j] = src[face][i][j];
}
int check_cube(int src[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
	for (int i = 0; i < LM; i++)
	for (int j = 0; j < LM; j++)
	if (src[face][i][j] != face)
		return 0;

	return 1;
}
void rotate(int face, int cw)
{
	int local[6][LM][LM];
	copy_cube(Cube, local);
	if (cw == 0)
	{
		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Cube[face][i][j] = local[face][j][LM - 1 - i];
	}
	else
	{
		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Cube[face][i][j] = local[face][LM-1-j][i];
	}

	int i;
	switch (face)
	{
	case 0:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[2][2][i] = local[4][3 - 1 - i][2];
				Cube[4][i][2] = local[3][0][i];
				Cube[3][0][i] = local[5][3 - 1 - i][0];
				Cube[5][i][0] = local[2][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[4][3 - 1 - i][2] = local[2][2][i];
				Cube[3][0][i] = local[4][i][2];
				Cube[5][3 - 1 - i][0] = local[3][0][i];
				Cube[2][2][i] = local[5][i][0];
			}
		}
		break;
	case 1:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[5][i][2] = local[3][2][3 - 1 - i];
				Cube[3][2][i] = local[4][i][0];
				Cube[4][i][0] = local[2][0][3 - 1 - i];
				Cube[2][0][i] = local[5][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[3][2][3 - 1 - i] = local[5][i][2];
				Cube[4][i][0] = local[3][2][i];
				Cube[2][0][3 - 1 - i] = local[4][i][0];
				Cube[5][i][2] = local[2][0][i];
			}
		}
		break;
	case 2:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[0][0][i] = local[5][0][i];
				Cube[5][0][i] = local[1][0][i];
				Cube[1][0][i] = local[4][0][i];
				Cube[4][0][i] = local[0][0][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[5][0][i] = local[0][0][i];
				Cube[1][0][i] = local[5][0][i];
				Cube[4][0][i] = local[1][0][i];
				Cube[0][0][i] = local[4][0][i];
			}
		}
		break;	
	case 3:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[0][2][i] = local[4][2][i];
				Cube[4][2][i] = local[1][2][i];
				Cube[1][2][i] = local[5][2][i];
				Cube[5][2][i] = local[0][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[4][2][i] = local[0][2][i];
				Cube[1][2][i] = local[4][2][i];
				Cube[5][2][i] = local[1][2][i];
				Cube[0][2][i] = local[5][2][i];
			}
		}
		break;
	case 4:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[0][i][0] = local[2][i][0];
				Cube[2][i][0] = local[1][3 - 1 - i][2];
				Cube[1][i][2] = local[3][3 - 1 - i][0];
				Cube[3][i][0] = local[0][i][0];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[2][i][0] = local[0][i][0];
				Cube[1][3 - 1 - i][2] = local[2][i][0];
				Cube[3][3 - 1 - i][0] = local[1][i][2];
				Cube[0][i][0] = local[3][i][0];
			}
		}
		break;	
	case 5:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[0][i][2] = local[3][i][2];
				Cube[3][i][2] = local[1][3 - 1 - i][0];
				Cube[1][i][0] = local[2][3 - 1 - i][2];
				Cube[2][i][2] = local[0][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[3][i][2] = local[0][i][2];
				Cube[1][3 - 1 - i][0] = local[3][i][2];
				Cube[2][3 - 1 - i][2] = local[1][i][0];
				Cube[0][i][2] = local[2][i][2];
			}
		}
		break;
	}

}

struct st{
	int face, cw;
};
st history[MAX_ROTATE], acts[MAX_ROTATE];
int gcube[6][LM][LM];

void grotate(int start[6][LM][LM], int face, int cw);

int do_dynamic(int start[6][LM][LM], int visited)
{
	if (visited == MAX_ROTATE)
	{
		for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
		for (int j = 0; j < LM; j++)
		{
			if (start[face][i][j] != gcube[face][i][j])
				return 0;
		}

		return 1;
	}

	for (int face = 0; face < 6; face++)
	{
		for (int cw = 0; cw < 2; cw++)
		{
			acts[visited].face = face;
			acts[visited].cw = cw;

			grotate(start, face, cw);

			if (do_dynamic(start, visited + 1) == 1)
				return 1;

			grotate(start, face, 1 - cw);
			int a = 0;
		}
	}
	return 0;
}

void runTest(int local[6][LM][LM])
{
	for (int i = 0; i < MAX_ROTATE; i++)
		acts[i].face = -1;

	copy_cube(local, gcube);

	int start[6][LM][LM];
	initial_cute(start);
	int visited = 0;
	if (do_dynamic(start, visited) == 1)
	{
		for (int i = MAX_ROTATE-1; i >= 0; i--)
			grotate(local, acts[i].face, 1-acts[i].cw);
	}

	return;
}

int main()
{
	int total_score = 0;
	int performance = 0;
	for (int tc = 0; tc < TC; tc++)
	{
		initial_cute(Cube);
		int local[6][LM][LM];
		copy_cube(Cube, local);
	
		memset(history, 0, sizeof(history));
		for (int i = 0; i < MAX_ROTATE; i++)
		{
			int face = rand() % 6;
			int cw = rand() % 2;
			history[i].face = face;
			history[i].cw = cw;
			rotate(face, cw);
		}

		copy_cube(Cube, local);
		time_t start = clock();
		runTest(local);
		time_t end = clock();
		performance += end - start;

		int score = 0;
		for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
		for (int j = 0; j < LM; j++)
		{
			if (local[face][i][j] != face)
			{
				score += 1000;
			}
		}

		total_score += score;
	}

	printf("%d %.6f", total_score, double(performance) / 10000.0);

}


void grotate(int start[6][LM][LM], int face, int cw)
{
	int local[6][LM][LM];
	copy_cube(start, local);
	if (cw == 0)
	{
		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			start[face][i][j] = local[face][j][LM - 1 - i];
	}
	else
	{
		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			start[face][i][j] = local[face][LM - 1 - j][i];
	}

	int i;
	switch (face)
	{
	case 0:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				start[2][2][i] = local[4][3 - 1 - i][2];
				start[4][i][2] = local[3][0][i];
				start[3][0][i] = local[5][3 - 1 - i][0];
				start[5][i][0] = local[2][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				start[4][3 - 1 - i][2] = local[2][2][i];
				start[3][0][i] = local[4][i][2];
				start[5][3 - 1 - i][0] = local[3][0][i];
				start[2][2][i] = local[5][i][0];
			}
		}
		break;
	case 1:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				start[5][i][2] = local[3][2][3 - 1 - i];
				start[3][2][i] = local[4][i][0];
				start[4][i][0] = local[2][0][3 - 1 - i];
				start[2][0][i] = local[5][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				start[3][2][3 - 1 - i] = local[5][i][2];
				start[4][i][0] = local[3][2][i];
				start[2][0][3 - 1 - i] = local[4][i][0];
				start[5][i][2] = local[2][0][i];
			}
		}
		break;
	case 2:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				start[0][0][i] = local[5][0][i];
				start[5][0][i] = local[1][0][i];
				start[1][0][i] = local[4][0][i];
				start[4][0][i] = local[0][0][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				start[5][0][i] = local[0][0][i];
				start[1][0][i] = local[5][0][i];
				start[4][0][i] = local[1][0][i];
				start[0][0][i] = local[4][0][i];
			}
		}
		break;
	case 3:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				start[0][2][i] = local[4][2][i];
				start[4][2][i] = local[1][2][i];
				start[1][2][i] = local[5][2][i];
				start[5][2][i] = local[0][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				start[4][2][i] = local[0][2][i];
				start[1][2][i] = local[4][2][i];
				start[5][2][i] = local[1][2][i];
				start[0][2][i] = local[5][2][i];
			}
		}
		break;
	case 4:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				start[0][i][0] = local[2][i][0];
				start[2][i][0] = local[1][3 - 1 - i][2];
				start[1][i][2] = local[3][3 - 1 - i][0];
				start[3][i][0] = local[0][i][0];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				start[2][i][0] = local[0][i][0];
				start[1][3 - 1 - i][2] = local[2][i][0];
				start[3][3 - 1 - i][0] = local[1][i][2];
				start[0][i][0] = local[3][i][0];
			}
		}
		break;
	case 5:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				start[0][i][2] = local[3][i][2];
				start[3][i][2] = local[1][3 - 1 - i][0];
				start[1][i][0] = local[2][3 - 1 - i][2];
				start[2][i][2] = local[0][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				start[3][i][2] = local[0][i][2];
				start[1][3 - 1 - i][0] = local[3][i][2];
				start[2][3 - 1 - i][2] = local[1][i][0];
				start[0][i][2] = local[2][i][2];
			}
		}
		break;
	}

}
