//DQ 로 해결 가능
//처음부터 모든 조합을 사용하면 N*N 으로 가능하지만 시간초과 발생
//중심 기준 왼쪽, 오른쪽, 중심포함 중에서 가장 큰 값을 선택하는 방식
//중심포함에서 좌우로 확장할때 더 높은쪽으로 확대하고 Height를 낮은 값으로 업데이트 하는 것을 유념. 이 방식의 정당성은 귀류법으로 파악 가능. 책 참고할 것
/*DQ
	- merge sort, quick sort에 활용 가능함
	- 문제를 둘로 나눈 후 계산, 원본 문제 계산 3개 중 선택하는 문제에 적용 가능
*/
#include <stdio.h>

int C;
int N;
int item[20000 + 10];

int myMax(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int myMin(int a, int b)
{
	if (a > b)
		return b;
	return a;
}
int CalFence(int left, int right)
{
	if (left == right)
		return item[left];

	int mid = (left + right) / 2;

	int ret;
	ret = myMax(CalFence(left, mid), CalFence(mid + 1, right));

	int lo = mid;
	int hi = mid + 1;
	int height = myMin(item[lo], item[hi]);

	while (lo > left || hi < right)
	{
		if (hi < right && (lo == left || item[lo - 1]<item[hi + 1]))
		{
			hi++;
			height = myMin(height, item[hi]);
		}
		else
		{
			lo--;
			height = myMin(height, item[lo]);
		}
		ret = myMax(ret, height*(hi - lo + 1));
	}

	return ret;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	scanf("%d", &C);
	for (int t = 1; t <= C; t++)
	{
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &item[i]);
		}
		printf("%d\n", CalFence(1, N));
	}
}