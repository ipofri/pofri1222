#include <stdio.h>
//#include <stdlib.h>
// LIS 로 풀수 있으나 300K 로 시간초과
// 길이 기준 DP 저장할 수 있으나 메모리 초과
// LIS로 풀되 bottom up으로 S보다 작은 값만 찾기, 95%까지 통과되나 시간초과
//   -> S보다 작을 값을 찾을 때 binary Search로 통과 됨
typedef struct st {
	int height;
	int cost;
} ST;

int N, S;
ST item[300000 + 2];
int DP[300000 + 2];

void qsort(int low, int high)
{
	if (low >= high)
		return;
	int i = low;
	int j = high;
	int pivot = low;

	while (i < j)
	{
		while (item[i].height <= item[pivot].height && i <= j) i++;
		while (item[j].height > item[pivot].height) j--;

		if (i < j)
		{
			ST tmp = item[i];
			item[i] = item[j]; 
			item[j] = tmp;
		}
	}

	ST tmp = item[pivot];
	item[pivot] = item[j]; 
	item[j] = tmp;

	qsort(low, j-1);
	qsort(j + 1, high);
}

int myMax(int a, int b)
{
	if (a > b)return a;
	else return b;
}

int exhibition(int start)
{
	if (DP[start] != 0)
		return DP[start];

	int max_val = item[start].cost;
	for (int i = start + 1; i <= N; i++)
	{
		if (item[i].height - item[start].height >= S)
			max_val = myMax(max_val, item[start].cost + exhibition(i));
	}

	DP[start] = max_val;

	return max_val;
}

int bin_search(int start, int end, int val)
{
	if (start >= end - 1)
	{
		if (item[start].height + S <= val)
			return start;
		else
			return 0;
	}

	int mid = (start + end) / 2;

	if (item[mid].height + S > val)
		end = mid;
	else
		start = mid;

	return bin_search(start, end, val);
}

int Solve()
{
	//case 3
	int max_val = 0;
	for (int i = 1; i <= N; i++)
	{
		int can_exhibit = bin_search(1, i, item[i].height);

		if (can_exhibit != 0)
		{
			if (item[can_exhibit].height + S > item[i].height)
			{
				int a = 1;
			}
			while (item[can_exhibit + 1].height == item[can_exhibit].height)
			{
				can_exhibit++;
			}
		}

		DP[i] = myMax(DP[i - 1], item[i].cost);
		if (can_exhibit != 0)
		{
			DP[i] = myMax(DP[i], DP[can_exhibit] + item[i].cost);
		}
	}
	max_val = DP[N];

	//case 2
	//int max_val = 0;
	//for (int i = 1; i <= N; i++)
	//{
	//	int can_exhibit = 0;
	//	for (int j = i - 1; j >= 1; j--)
	//	{
	//		if (item[i].height - item[j].height >= S)
	//		{
	//			can_exhibit = j;
	//			break;
	//		}
	//	}

	//	DP[i] = myMax(DP[i - 1], item[i].cost);
	//	if (can_exhibit != 0)
	//	{
	//		DP[i] = myMax(DP[i], DP[can_exhibit] + item[i].cost);
	//	}
	//}
	//max_val = DP[N];
		
	//case 1
	//int h = 0;
	//for (int i = 1; i <= N; i++)
	//{
	//	h = item[i].height;
	//	if (DP[item[i].height] < item[i].cost)
	//	{
	//		DP[item[i].height] = item[i].cost;
	//	}
	//}
	//int max_val = 0;
	//for (int i = 1; i < S; i++)
	//{
	//	if (DP[i] < DP[i - 1])
	//		DP[i] = DP[i - 1];
	//}
	//for (int i = S; i <= h; i++)
	//{
	//	DP[i] = myMax(DP[i - 1], DP[i - S] + DP[i]);
	//}
	//max_val = DP[h];

	//case 0
	//int max_val = 0;
	//for (int i = 1; i <= N; i++)
	//{
	//	max_val = myMax(max_val, exhibition(i));
	//}

	return max_val;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d %d", &N, &S);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &item[i].height, &item[i].cost);
	}

	//N = 300000;
	//S = 1000;
	//srand(3);
	//for (int i = 1; i <= N; i++)
	//{
	//	item[i].height = rand() % 20000000 + 1;
	//	item[i].cost = rand() % 1000 + 1;
	//}

	qsort(1, N);

	printf("%d", Solve());

	int a = 0;
}
