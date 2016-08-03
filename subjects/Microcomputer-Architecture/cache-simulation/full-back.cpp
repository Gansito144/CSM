#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <deque>

#define MEM_SIZE (1<<20)
#define CACHE_SIZE (1<<8)
#define DATA_SIZE (1<<8) 

using namespace std;

int main() {
	// Variables used
	int dir, cmd, op;
	unsigned char dat, wait;

	// Plant the seed
	srand(time(0));

	// Infinit Loop
	while(true){
		// Each command is 32 bits,
		// 19...0 bits for dir,
		// 27...20 bits for data
		// 28 bit indicates operation type 1:read 0:write 
		cmd = rand();
		dir = cmd & 0xFFFFF;
		dat = (cmd & 0xF00000)>>20;
		op = (cmd>>28)&1;
		printf("op=%c on dir(0x%x) data:%d\n","wr"[op],dir,dat);
		wait = getchar();
	}
	return 0;
}