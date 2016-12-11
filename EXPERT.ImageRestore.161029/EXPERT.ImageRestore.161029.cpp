#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>

int getpixel(unsigned char (*bitmap)[32], int x, int y)
{
	unsigned char temp = bitmap[y][x / 8];
	int val = (temp >> (x % 8)) & 0x01;
	return val;
}

void setpixel(unsigned char (*bitmap)[32], int x, int y, int val)
{
	unsigned char temp = bitmap[y][x / 8];
	if (val == 1)
		temp = temp | (0x01 << (x % 8)); 
	else
		temp = temp & ~(0x01 << (x % 8));
	bitmap[y][x / 8] = temp;
}

void rotate(unsigned char(*bitmap)[32], int opt)
{
	unsigned char temp_map[256][32];

	switch (opt)
	{
	case 0:
		return;
	case 1:
		for (int y = 0; y < 256; y++)
		{
			for (int x = 0; x < 256; x++)
			{
				setpixel(temp_map, x, y, getpixel(bitmap, y, 255 - x));
			}
		}
		break;
	case 2:
		for (int y = 0; y < 256; y++)
		{
			for (int x = 0; x < 256; x++)
			{
				setpixel(temp_map, x, y, getpixel(bitmap, 255 - x, 255 - y));
			}
		}
		break;
	case 3:
		for (int y = 0; y < 256; y++)
		{
			for (int x = 0; x < 256; x++)
			{
				setpixel(temp_map, x, y, getpixel(bitmap, 255 - y, x));
			}
		}
		break;
	}

	memcpy(bitmap, temp_map, 256 * 32);
}

void flip(unsigned char(*bitmap)[32], int opt)
{
	unsigned char temp_map[256][32];

	switch (opt)
	{
	case 0:
		return;

	case 1://vertical
		for (int y = 0; y < 256; y++)
		{
			for (int x = 0; x < 256; x++)
			{
				setpixel(temp_map, x, y, getpixel(bitmap, 255 - x, y));
			}
		}
		break;
	case 2://horizental
		for (int y = 0; y < 256; y++)
		{
			for (int x = 0; x < 256; x++)
			{
				setpixel(temp_map, x, y, getpixel(bitmap, x, 255 - y));
			}
		}
	}

	memcpy(bitmap, temp_map, 256 * 32);

}

void initial(unsigned char(*bitmap)[32])
{
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			setpixel(bitmap, x, y, 0);
		}
	}
}

void encode(unsigned char(*bitmap)[32], unsigned char *data)
{
	for (int i = 0; i < 4096; i++)
	{
		int parse[4] = { 0, };
		for (int j = 0; j < 4; j++)
		{
			parse[j] = (data[i] >> j) & 0x01;
		}

		//temp
		unsigned char c1 = data[i];

		int row = i / 32;
		int col = i % 32;

		for (int j = 0; j < 4; j++)
		{
			bitmap[row * 2][col] |= parse[j] << (j * 2);
			bitmap[row * 2][col] |= parse[j] << (j * 2 + 1);
		}

		//temp
		unsigned char c2 = bitmap[row * 2][col];
		bitmap[row * 2 + 1][col] = bitmap[row * 2][col];

		//index Ãß°¡
		if (row == 0 && col < 16)
		{
			for (int j = 0; j < 4; j++)
				bitmap[row * 2 + 1][col] |= 0x01 << (j * 2 + 1);
		}
		else
		{
			for (int j = 0; j < 4; j++)
			{
				unsigned char t1 = ~(0x01 << (j * 2 + 1));
				bitmap[row * 2 + 1][col] &= t1;
			}
		}
	}
}

void decode(unsigned char(*bitmap)[32], unsigned char *data)
{
	int findstate[8] = { 0, };

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				switch (i)
				{
				case 0: //upper left
					if (bitmap[1][j] & (0x01 << (k * 2 + 1)))
						findstate[i]++;
					break;
				case 1: // upper right
					if (bitmap[1][j + 16] & (0x01 << (k * 2)))
						findstate[i]++;
					break;
				case 2: // right upper
					if (bitmap[j * 8 + 1 + k * 2][31] & (0x01 << 6))
						findstate[i]++;
					break;
				case 3: // right lower
					if (bitmap[128 + j * 8 + k * 2][31] & (0x01 << 6))
						findstate[i]++;
					break;
				case 4: //lower left
					if (bitmap[254][j] & (0x01 << (k * 2+1)))
						findstate[i]++;
					break;
				case 5: // lower right
					if (bitmap[254][j + 16] & (0x01 << (k * 2)))
						findstate[i]++;
					break;
				case 6: // left upper
					if (bitmap[j * 8 + 1 + k * 2][0] & (0x01 << 1))
						findstate[i]++;
					break;
				case 7: // left lower
					if (bitmap[128 + j * 8 + k * 2][0] & (0x01 << 1))
						findstate[i]++;
					break;
				}
			}
		}
	}

	int case1 = 0;
	for (int i = 1; i < 8; i++)
	{
		if (findstate[i]>findstate[case1])
			case1 = i;
	}

	switch (case1)
	{
	case 0:
		break;
	case 1:
		flip(bitmap, 1);
		break;
	case 2:
		rotate(bitmap, 3);
		break;
	case 3:
		flip(bitmap, 2);
		rotate(bitmap, 3);
		break;
	case 4:
		flip(bitmap, 2);
		break;
	case 5:
		rotate(bitmap, 2);
		break;
	case 6:
		flip(bitmap, 1);
		rotate(bitmap, 3);
		break;
	case 7:
		rotate(bitmap, 1);
		break;
	}

	for (int i = 0; i < 4096; i++)
	{
		int row = i / 32;
		int col = i % 32;

		int parse[4] = { 0, };
		int noise[4] = { 0, };

		//temp
		unsigned char c1 = bitmap[row][col];

		for (int j = 0; j < 4; j++)
		{
			noise[0] = (bitmap[row*2][col] >> (j * 2 + 0)) & 0x01;
			noise[1] = (bitmap[row*2][col] >> (j * 2 + 1)) & 0x01;
			noise[2] = (bitmap[row*2+1][col] >> (j * 2 + 0)) & 0x01;
//			noise[3] = (bitmap[row*2+1][col] >> (j * 2 + 1)) & 0x01;

			int count0 = 0;
			int count1 = 0;
			for (int k = 0; k < 3; k++)
			{
				if (noise[k] == 0)
					count0++;
				else
					count1++;
			}
			if (count0>count1)
				parse[j] = 0;
			else
				parse[j] = 1;
		}

		for (int j = 0; j < 4; j++)
			data[i] |= parse[j] << j;

		//temp
		unsigned char c2 = data[i];
		c2 = c2;
	}
}

void noise(unsigned char(*bitmap)[32])
{
	for (int i = 0; i < 256; i+=2)
	{
		for (int j = 0; j < 256; j+=2)
		{
			int rand0 = rand() % 2;
			int rand1 = rand() % 2; 
			setpixel(bitmap, j + rand0, i + rand1, 0);
			rand0 = rand() % 2;
			rand1 = rand() % 2;
			setpixel(bitmap, j + rand0, i + rand1, 1);
		}
	}
}

const int TC = 1024;
unsigned char bitmap[TC][256][32] = { 0, };
unsigned char origin_data[TC][4096] = { 0, };
unsigned char recover_data[TC][4096] = { 0, };

int main(void)
{
	clock_t t = clock();
	for (int tc = 0; tc < TC; tc++)
	{
		for (int i = 0; i < 4096; i++)
			origin_data[tc][i] = rand() % 15;
		
		t = clock() - t;
		printf("getdata = %d\n", t);

		initial(bitmap[tc]);
		t = clock() - t;
		printf("intial = %d\n", t);
		
		encode(bitmap[tc], origin_data[tc]);
		t = clock() - t;
		printf("encode = %d\n", t);

		noise(bitmap[tc]);
		t = clock() - t;
		printf("noise = %d\n", t);

		rotate(bitmap[tc], rand() % 4);
		t = clock() - t;
		printf("rotate = %d\n", t);

		flip(bitmap[tc], rand() % 3);
		t = clock() - t;
		printf("flip = %d\n", t);
		
		decode(bitmap[tc], recover_data[tc]);
		t = clock() - t;
		printf("decode = %d\n", t);

	}
	int performance = 10000;
	
	t = clock();
	for (int tc = 0; tc < TC; tc++)
		decode(bitmap[tc], recover_data[tc]);
	t = clock() - t;
	performance -= (t / (double)CLOCKS_PER_SEC) * 10000;
	
	int pass = 0;

	for (int tc = 0; tc < TC; tc++)
	{
		if (memcmp(origin_data[tc], recover_data[tc], 4096) == 0)
			pass++;
	}

	printf("Score = %d", pass * 10000 + performance);

	return 0;
}