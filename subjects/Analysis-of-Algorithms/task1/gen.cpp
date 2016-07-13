#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>

#define MAXN 12345
#define N 100000

using namespace std;

int v[N];

int main()
{
	srand(time(0));

	// Ordered
	printf("%d\n",N);
	for(int i=0; i<N; i++)
	{
		printf("%d ",i+1);
	}
	puts("");

	// Ordered Inversed
	printf("%d\n",N);
	for(int i=0; i<N; i++)
	{
		printf("%d ",N-i);
	}
	puts("");

	// Almost ordered
	for(int i=0; i<N; i++)
	{
		v[i] = i+1;
	}
	// Shuffle
	for(int i=0; i<44; i++) //Some shuffle
	{
		int x=rand()%N, y=rand()%N;
		swap(v[x],v[y]);
	}
	//Print
	printf("%d\n",N);
	for(int i=0; i<N; i++)
	{
		printf("%d ",v[i]);
	}
	printf("\n");

	// Random
	int test = 1;
	while( test-- )
	{
		//int N = rand() % MAXN + 1;
		//int v[N];
		// Initialize
		for(int i=0; i<N; i++)
		{
			v[i] = i+1;
		}
		// Shuffle
		for(int i=0; i<N; i++)
		{
			//for(int i=0; i<N; i++)
			{
				int x=rand()%N, y=rand()%N;
				swap(v[x],v[y]);
			}
		}
		//Print
		printf("%d\n",N);
		for(int i=0; i<N; i++)
		{
			printf("%d ",v[i]);
		}
		printf("\n");
	}
	return 0;
}
