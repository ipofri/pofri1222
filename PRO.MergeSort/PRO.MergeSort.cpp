#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 1000000;
int temp[N];
int item[N];

void msort(int *item, int low, int high)
{
	if (low >= high)
		return;

	int mid = (low + high ) / 2;
	msort(item, low, mid);
	msort(item, mid + 1, high);

	int i = low;
	int j = mid+1;
	int k = low;

	while (i <= mid && j <= high)
	{
		if (item[i] <= item[j])
			temp[k++] = item[i++];
		else
			temp[k++] = item[j++];
	}

	while (k <= high)
	{
		if (i<mid+1)
			temp[k++] = item[i++];
		else
			temp[k++] = item[j++];
	}

	for (int i = low; i <= high; i++)
		item[i] = temp[i];
}

int main(void)
{
	srand(time(NULL));
	//랜덤배열 생성
	for (int i = 0; i < N; i++)
		item[i] = rand()-N/2;

	int sum1 = 0; 
	for (int i = 0; i < N; i++)
		sum1 += item[i];

	msort(item, 0, N - 1);

	//실행 후 배열 출력
	for (int i = 1; i < N; i++)
	{
		if (item[i] < item[i - 1])
			printf("Error\n");
	}

	int sum2 = 0;
	for (int i = 0; i < N; i++)
		sum2 += item[i] % N;

	return 0;
}