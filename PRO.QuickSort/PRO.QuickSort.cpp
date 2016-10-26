#include <stdio.h>
#include <stdlib.h>

int N;
int map[10000];

void QuickSort(int low, int high)
{
	int i = low;
	int j = high;
	int pivot = low;

	if (low >= high)
		return;

	while (i < j)
	{
		while (map[i] <= map[pivot] && i <= high) i++;
		while (map[j] > map[pivot]) j--;

		if (i < j)
		{
			int temp = map[i];
			map[i] = map[j];
			map[j] = temp;
		}
	}

	int temp = map[j];
	map[j] = map[pivot];
	map[pivot] = temp;

	QuickSort(low, j - 1);
	QuickSort(j + 1, high);
}
int main(void)
{
	int a = rand();
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		map[i] = rand() % 100;

	QuickSort(0, N - 1);
	for (int i = 0; i < N; i++)
	{
		printf("%d ", map[i]);
		if (i>0 && map[i] < map[i - 1])
		{
			int a = 0;
		}
	}
}