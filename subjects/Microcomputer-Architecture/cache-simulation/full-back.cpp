#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <bitset>
#include <deque>

#define MEM_SIZE (1<<20)
#define CACHE_SIZE (1<<8)

using namespace std;

enum{
	read,
	write
};

int main() {
	// Variables used
	int dir, cmd, op;
	unsigned char dat, wait;

	// Memory simulated
	unsigned char rawMemory[MEM_SIZE];
	int cacheDirection[CACHE_SIZE];
	unsigned char cacheData[CACHE_SIZE];

	// To simulate the circular queue
	int front = 0, tail = 0;

	// Initialize the cached Directions
	memset(cacheDirection, -1, sizeof cacheDirection);

	// Plant the seed
	srand(time(0));

	// Infinit Loop
	while(true){
		// Each command is 32 bits,
		cmd = rand();
		// 19...0 bits for dir
		dir = ((cmd)&(0xFFFFF));
		// 27...20 bits for data
		dat = (((cmd)&(0xF00000))>>20);
		// 28 bit indicates operation type 0:read 1:write
		op  = ((cmd>>28)&(1));
		
		//Perform operation according
		if(op == read) {
			
		} else { // write

		}

		wait = getchar();
	}
	return 0;
}