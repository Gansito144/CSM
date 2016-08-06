#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <bitset>
#include <deque>

using namespace std;

const int BITS_MEM = (5);
const int BITS_CACHE = (2);
const int BITS_DATA = (2);
enum{ read, write };

inline int left_shift(int n, int k) {
	return ((n)<<(k));
}

//helper function to get bits, len shold be at least 1
inline int get_bits(int n, int len, int from){
	int bits = (left_shift(1,len))-1;
	return (((n)>>from)&bits);
}

// Inline function to search address within cachedA array
inline int cache_search(int cachedA[], int address){
	int sz = left_shift(1,BITS_CACHE);
	for(int i=0; i<sz; ++i) {
		if(cachedA[i] == address){
			return i;
		}
	}
	return -1;
}

int main() {
	// Variables used
	int address, cmd, rnd, pos;
	unsigned char dat, wait;

	// Memory simulated
	unsigned char rawMemory[left_shift(1,BITS_MEM)];
	int cachedAddresses[left_shift(1,BITS_CACHE)];
	unsigned char cacheData[left_shift(1,BITS_CACHE)];

	// To simulate the circular queue
	int front = 0, tail = 0;

	// Initialize the cached Directions
	memset(cachedAddresses, -1, sizeof cachedAddresses);

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
		pos = cache_search(cachedAddresses, address);
		if(cmd == read) {
			puts("Operation: [Read]");
			// Was found in cache, just read this value
			if(pos >= 0) {
				printf("Address 0x%x found at %d index in cache\n",address,pos);
				printf("Raw data = 0x%x\n",cacheData[pos]);
			}else { // Read from raw memory
				printf("Address 0x%x not found in cache take it from Raw",address);
				printf("Raw data = 0x%x\n",rawMemory[address]);
				// And insert new data into cache
				printf("Saving new address/data into cache...\n");
				puts("TODO");
			}
		} else { // write
			puts("Operation: [Write]");
			// Was found in cache, just update this value
			if(pos >= 0) {
				printf("Address 0x%x found at %d index in cache\n",address,pos);
				printf("Update cached data = old(0x%x), new(0x%x)\n",(cacheData[pos]),dat);
				cacheData[pos] = dat;
			}else{
				// Write directly to 	
				puts("TODO 2");
			}
			
		}

		wait = getchar();
	}
	return 0;
}