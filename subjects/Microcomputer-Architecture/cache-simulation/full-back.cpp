#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <bitset>
#include <deque>

using namespace std;

const int MEM_SIZE = (1<<20);
const int CACHE_SIZE = (1<<8);
enum{ read, write };

// Inline function to search address within cachedA array
inline int cache_search(int cachedA[], int address){
	for(int i=0; i<CACHE_SIZE; ++i) {
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
	unsigned char rawMemory[MEM_SIZE];
	int cachedAddresses[CACHE_SIZE];
	unsigned char cacheData[CACHE_SIZE];

	// To simulate the circular queue
	int front = 0, tail = 0;

	// Initialize the cached Directions
	memset(cachedAddresses, -1, sizeof cachedAddresses);

	// Plant the seed
	srand(time(0));

	// Infinit Loop
	while(true){
		// Each command is 32 bits,
		rnd = rand();
		// 19...0 bits for address
		address = ((rnd)&(0xFFFFF));
		// 27...20 bits for data
		dat = (((rnd)&(0xF00000))>>20);
		// 28 bit indicates operation type 0:read 1:write
		cmd  = ((rnd>>28)&(1));
		
		//Perform operation according
		// search in cache
		pos = cache_search(cachedAddresses, address);
		if(cmd == read) {
			// Was found in cache, just read this value
			if(pos >= 0) {
				printf("Address 0x%x found at %d index in cache\n",address,pos);
				printf("Raw data = 0x%x\n",cacheData[pos]);
			}else { // Read from raw memory
				printf("Address 0x%x not found in cache take it from Raw",address);
				printf("Raw data = 0x%x\n",rawMemory[address]);
				// And insert new data into cache
				printf("Saving new address/data into cache...\n");
				/*TODO*/
			}
		} else { // write
			// Was found in cache, just update this value
			if(pos >= 0) {
				printf("Address 0x%x found at %d index in cache\n",address,pos);
				printf("Update data = 0x%x\n",(cacheData[pos] = data));
			} /*TODO*/
			// update in cache
		}

		wait = getchar();
	}
	return 0;
}