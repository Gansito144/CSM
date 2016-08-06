#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <bitset>
#include <deque>

using namespace std;

#define shiftL(n, k) ((n)<<(k))
#define shiftR(n, k) ((n)>>(k))
#define BITS_MEM  (5)
#define BITS_CACHE (2)
#define BITS_DATA (2)

enum{ read, write };

// Memory simulated
int  rawMemory[ shiftL(1,BITS_MEM)  ];
int cachedAddr[ shiftL(1,BITS_CACHE)];
int cachedData[ shiftL(1,BITS_CACHE)];

//helper function to get bits, len shold be at least 1
inline int get_bits(int n, int len, int from) {
	int bits = (shiftL(1,len)) - 1;
	return (shiftR(n,from)&bits);
}

// Inline function to search address within cachedA array
inline int cache_search(int address) {
	int sz = shiftL(1,BITS_CACHE);
	for(int i=0; i<sz; ++i)
		if(cachedAddr[i] == address) return i;
	return -1;
}

inline int read_cache(int index) {
	return cachedData[index];
}

inline void write_cache(int index, int data) {
	cachedData[index] = data;
}

inline void update_cache(int address, int data) {
	/* TODO search the best place to update cache*/
}

int main() {
	// Variables used
	int address, cmd, rnd, pos;
	unsigned char dat, wait;

	// To simulate the circular queue
	int front = 0, tail = 0;

	// Initialize the cached Directions
	memset(cachedAddr, -1, sizeof cachedAddr);

	// Feed the seed
	srand(time(0));

	// Infinit Loop
	while(true){
		// Each command is 32 bits,
		rnd = rand();
		// 0 - bit indicates operation type 0:read 1:write
		cmd = get_bits(rnd,1,0);
		// 20...1 bits for address
		address = get_bits(rnd,BITS_MEM,1);
		// 28...21 bits for data
		dat = get_bits(rnd,BITS_DATA,BITS_MEM + 1);
		
		//Perform operation according
		// search in cache
		pos = cache_search(address);
		if(cmd == read) {
			puts("Operation: [Read]");
			// Was found in cache, just read this value
			if(pos >= 0) {
				printf("Address 0x%x found in cache index(%d)\n",address,pos);
				printf("Data in cache = 0x%x\n",read_cache(pos));
			}else { // Read from raw memory
				printf("Address 0x%x not Found!\n",address);
				printf("Raw data read = 0x%x\n",rawMemory[address]);
				// And insert new data into cache
				update_cache(address, rawMemory[address]);
			}
		} else { // write
			puts("Operation: [Write]");
			// Was found in cache, just update this value
			if(pos >= 0) {
				printf("Address 0x%x found in cache index(%d)\n",address,pos);
				printf("Update cached data, Old[0x%x], New[0x%x]\n",read_cache(pos),dat);
				write_cache(pos, dat);
			}else{
				// Write directly to raw 	
				printf("Address 0x%x not Found!\n",address);
				printf("Write raw data, New[0x%x]\n",dat);
				rawMemory[address] = dat;
				// And insert new data into cache
				update_cache(address, rawMemory[address]);
			}
		}

		wait = getchar();
	}
	return 0;
}