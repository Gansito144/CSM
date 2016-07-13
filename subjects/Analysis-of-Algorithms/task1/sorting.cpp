#include <iostream>
#include <cstdio>
#include <algorithm>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

typedef long long int i64;
using namespace std;

#define MAXN 1234567 // ~ 10^6


/** Utilities BEGIN **/
// Time measurement
#define measure(name,fun,arr,sz,t1,t2,et) do{\
		gettimeofday(&t1, 0);\
		fun(arr,sz);\
		gettimeofday(&t2, 0);\
		et = (t2.tv_sec - t1.tv_sec) * 1000000.0;\
		et += (t2.tv_usec - t1.tv_usec);\
		printf("It took %7.0lf(us) sort array of size %d using %s\n",et,sz,name);\
	}while(0);

inline void print_array(int v[],int size)
{
	for(int i=0; i<size; i++)
	{
		printf("%s%d",(i?" ":""),v[i]);
	}
	printf("\n");
}
/** Utilities END **/





// Global variables
int raw[MAXN];

// Merge Sort Variables
int m_array[MAXN], m_aux[MAXN];

// Heap Sort Variables
int h_array[MAXN], h_aux[MAXN], h_size, h_root;

// Quick Sort  Variables
int q_array[MAXN];


//  Merge
i64 merge(int v[], int va[], int L, int R)
{
	i64 cnt = 0LL; //swapping ops
	if( L<R ) //More than one element
	{
		// Split array in two
		int mid = (L+R)/2;

		//Solve each part
		cnt += merge(va,v,L,mid);
		cnt += merge(va,v,mid+1,R);

		//Merge both solutions
		int i = L, j = mid + 1, k = L;
		while( i<=mid && j<=R )
		{
			if(va[i] <= va[j])
				v[k++] = va[i++];
			else
			{
				v[k++] = va[j++];
				cnt += (mid+1) - i; // swaps 
			}
		}
		//Fill the rest
		while ( i <= mid ) v[ k++ ] = va[ i++ ];
		while ( j <= R ) v[ k++ ] = va[ j++ ];
	}
	return cnt;
}

//Merge Sort
i64 merge_sort(int data[], int size)
{
	// Initialize
	for(int i=0; i<size; i++)
	{
		m_array[i] = m_aux[i] = data[i];
	}
	i64 movs = merge(m_array,m_aux,0,size-1);
	//print_array(m_array,size);
	return movs;
}

// A heap reference 
// http://algorithms.tutorialhorizon.com/binary-min-max-heap/

// Heap initialization 
inline void heap_init()
{
	h_size = 0;
	h_root = 1;
}

// Heap is_root
inline int is_root(int node)
{
	return node == 1;
}

// Heap get_parent
inline int get_parent(int node)
{
	return node >> 1;
}

// Heap insert
i64 heap_insert(int heap[], int val)
{
	int parent = 0;
	int node = ++h_size;
	i64 cicles = 0LL;
	heap[node] = val;
	while( !is_root(node) )
	{
		parent = get_parent(node);
		//printf("%s n=%d p=%d\n",__FUNCTION__,node,parent);
		if(heap[node] >= heap[parent]) break;
		//printf("%d %d\n",heap[node],heap[parent]);
		swap(heap[node], heap[parent]);
		node = parent;
		cicles++;
	}
	return cicles;
}

// Heap delete
i64 heap_delete(int heap[], int &val)
{
	int parent, left, right;
	i64 cicles = 0LL;

	if( h_size == 0) return -1LL;
	val = heap[h_root];
	h_size--;

	if(h_size >= h_root)
	{   // Set the last element
		heap[h_root] = heap[h_size+1];
		int node, small=h_root;
		do
		{
			node = small;
			left = node << 1;
			right = left + 1;
			if(left<=h_size && heap[left]<heap[small])
			{
				small = left;
			}
			if(right<=h_size && heap[right]<heap[small])
			{
				small = right;
			}
			//printf("n=%d s=%d sm=%d\n",node,small,heap[small]);
			swap(heap[node],heap[small]);
			cicles++;
		}while(small != node);
	}

	return cicles;
}

// Heap Sort
i64 heap_sort(int data[], int size)
{
	i64 movs = 0LL;
	heap_init();
	// Insert elements
	for(int i=1; i<=size; i++)
	{
		movs += heap_insert(h_aux, data[i-1]);
	}
	// Extract ordered elements
	for(int i = 0; i < size; i++)
	{
		movs += heap_delete(h_aux, h_array[i]);
	}
	//print_array(h_array,size);
	return movs;
}


// partition
i64 partition(int A[], int p, int r, int &i)
{
	i64 movs = 0LL;
	int x = A[r]; // We need to change this after
	i = p-1;
	for(int j=p; j<r; j++)
	{
		if(A[j]<=x)
		{
			++i;
			swap(A[i],A[j]);
			++movs;
		}
	}
	swap(A[++i],A[r]);
	return ++movs;
}

// quick sort 
i64 q_sort(int A[], int p, int r)
{
	i64 movs = 0LL;
	if(p < r)
	{
		int q;
		movs += partition(A,p,r,q);
		movs += q_sort(A, p, q-1);
		movs += q_sort(A, q+1, r);
	}
	return movs;
}

// Quick Sort
i64 quick_sort(int data[], int size)
{
	// Initialize
	for(int i=0; i<size; i++)
	{
		q_array[i] = data[i];
	}
	i64 movs = q_sort(q_array,0,size-1);
	//print_array(q_array,size);
	return movs;
}


int main()
{
	int array_size;
	struct timeval t_start,t_end;
	double elapsed_time;

	while(scanf("%d",&array_size) != EOF && array_size)
	{
	/*
	 * puts("Please specify the size of array:");
	 * scanf("%d",&array_size);
	 * puts("Please introduce the elements of the array:");
	 */
		for(int i = 0; i < array_size; i++)
		{
			scanf("%d",&raw[i]);
		}
		//measure(name,fun,arr,sz,t1,t2,et)
		measure("Merge Sort",merge_sort,raw,array_size,t_start,t_end,elapsed_time);
		measure("Heap Sort",heap_sort,raw,array_size,t_start,t_end,elapsed_time);
		measure("Quick Sort",quick_sort,raw,array_size,t_start,t_end,elapsed_time);
		puts("");
	}

	return 0;
}

