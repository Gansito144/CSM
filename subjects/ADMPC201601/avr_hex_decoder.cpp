#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

// Macros for string processing
#define cut(s,i,sz) ((s).substr((i),(sz)))
#define to_c(s) ((s).c_str())
#define getHex(s,n) (sscanf(s,"%x",&(n)))

// Macros for bits manipulation
#define getByte(w,B) (((w)&((0xFF)<<B))>>B)
#define getBit(w,b) (((w)&((0x1)<<b))>>b)

using namespace std;

#if 1
char logs[123456];
#define DEBUG(...) sprintf(logs,__VA_ARGS__)
#else 
#define DEBUG printf
#endif

int checksum_ok(string &str, int &size, int &checkSum) {
	unsigned int check=0;
	int twoByte, i=1;
	for(; i< size; i += 2) {
		DEBUG("i(%d): ",i);
		getHex(to_c(cut(str,i,2)),twoByte);
		check += twoByte;
		check &= 0xFF;
		DEBUG("%x %d %x\n",twoByte,twoByte,check);
	}
	// Two complement of a function
	check = (~check) + 1;
	check &= 0xFF;

	// Verify against cheksum expected
	return (check != checkSum) ? -EINVAL : 0;
}

int parse_cmd(string &str, string &cmds) {
	int byteCount, address, recordType;
	int checkSum, idx = 1;

	// Clear whatever cmds contains
	cmds = "";
	if(!str.size() || str[0] != ':' ){
		return -EINVAL;
	}
	
	/**
	* Byte Count: two hex digits, indicating
	* the number of bytes (hex digit pairs) 
	* in the data field
	**/
	getHex(to_c(cut(str,idx,2)),byteCount);
	idx += 2;
	DEBUG("byteCount: %02d %02x\n",byteCount,byteCount);

	/** 
	* Address: four hex digits, representing 
	* the 16-bit beginning memory address offset
	* of the data. 
	**/
	getHex(to_c(cut(str,idx,4)),address);
	idx += 4;
	DEBUG("address: %04d %04x\n",address,address);

	/** Record type: (see record types below),
	* two hex digits, 00 to 05, defining the 
	* meaning of the data field.
	* 00	Data
	* 01	End Of File
	* 02	Extended Segment Address
	* 03	Start Segment Address
	* 04	Extended Linear Address
	* 05	Start Linear Address
	**/
	getHex(to_c(cut(str,idx,2)),recordType);
	idx += 2;
	DEBUG("recordType: %02d %02x\n",recordType,recordType);

	/** Data: a sequence of n bytes of data, represented
	* by 2n hex digits.
	**/
	cmds = cut(str,idx,2*byteCount);
	idx += 2*byteCount;
	DEBUG("data: %s\n",to_c(cmds));

	/** Checksum, two hex digits, a computed value that
	* can be used to verify the record has no errors.
	**/
	getHex(to_c(cut(str,idx,2)),checkSum);
	DEBUG("checkSum: %02d %02x\n",checkSum,checkSum);
	return checksum_ok(str, idx, checkSum);
}

void execute_cmd( int &opCode ) {
	printf("%02X %02X %02X %02X\n",getByte(opCode,0),getByte(opCode,1),getByte(opCode,2),getByte(opCode,3));
	printf("%02X %02X %02X %02X\n",getByte(opCode,3),getByte(opCode,2),getByte(opCode,1),getByte(opCode,0));
}


void split_cmds(string &cmds) {
	// We had blocks of 4 bytes, lets process them
	int opCode;
	for(int i=0; i<cmds.size(); i += 4) {
		getHex(to_c(cut(cmds,i,4)),opCode);
		DEBUG("opCode: %04d %04x\n",opCode,opCode);
		/** Now that we know each opcode lets 'execute' them
		* Each opcode is an int of 16 bits
		**/
		execute_cmd(opCode);
	}
}

int main() {
	string hexLine;
	string parsedCmd;
	ifstream hexFile;

	//For test purposes
	hexFile.open("main.hex");
	int err = 0;

	// Read each line from .hex file while possible
	while (getline(hexFile, hexLine)) {
		// Now parse the string to a more friendly format
		err = parse_cmd(hexLine, parsedCmd);
		if(err) {
			printf("Error ocurred %d\n",err);
			break;
		}
		// If no errors proceed to execute the command	
		split_cmds(parsedCmd);
	}
	return 0;	
}