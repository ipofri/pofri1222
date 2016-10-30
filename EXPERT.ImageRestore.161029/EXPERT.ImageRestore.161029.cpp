#include <stdio.h>

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

int main(void)
{
	unsigned char bitmap[256][32] =  {0, };
	//bitmap[0][0] = 3;
	//bitmap[0][12] = 15;
	//bitmap[0][24] = 8;
	setpixel(bitmap,0, 0, 1);
	setpixel(bitmap, 1, 0, 1);
	setpixel(bitmap, 96, 0, 1);
	setpixel(bitmap, 97, 0, 1);
	setpixel(bitmap, 98, 0, 1);
	setpixel(bitmap, 99, 0, 1);
	setpixel(bitmap, 195, 0, 1);

	for (int i = 0; i < 256; i++)
	{
		int a = getpixel(bitmap, i, 0);
		if (a == 1)
			printf("(%d,%d) = %d\n", i, 0,a);
	}

	return 0;
}