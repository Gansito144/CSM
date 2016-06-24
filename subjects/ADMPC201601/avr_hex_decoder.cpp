#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

#define cut(s,i,sz) ((s).substr((i),(sz)))
#define to_c(s) ((s).c_str())
#define getHex(s,n) (sscanf(s,"%x",&(n)))

using namespace std;

#define DEBUG printf

int checksum_ok(string cmd, int size) {
	unsigned int check=0;
	int twoByte, i=1;
	size = (size+4) * 2;
	for(; i< size; i += 2) {
		DEBUG("i(%d): ",i);
		getHex(to_c(cut(cmd,i,2)),twoByte);
		check += twoByte;
		check &= 0xFF;
		DEBUG("%x %d %x\n",twoByte,twoByte,check);
	}
	// Two complement of a function
	check = (~check) + 1;
	check &= 0xFF;

	// The cheksum expected
	getHex(to_c(cut(cmd,i,2)),twoByte);
	DEBUG("CheckSums %x %x\n",check,twoByte);
	return (check != twoByte) ? -EINVAL : 0;
}

int parse_cmd(string str, string cmd) {
	int byteCount, address, recordType;

	// Clear whatever cmd contains
	cmd = "";
	if(!str.size() || str[0] != ':' ){
		return -EINVAL;
	}
	
	/**
	* Byte Count: two hex digits, indicating
	* the number of bytes (hex digit pairs) 
	* in the data field
	**/
	getHex(to_c(cut(str,1,2)),byteCount);
	DEBUG("byteCount: %02d %02x\n",byteCount,byteCount);

	/** 
	* Address: four hex digits, representing 
	* the 16-bit beginning memory address offset
	* of the data. 
	**/
	getHex(to_c(cut(str,3,4)),address);
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
	getHex(to_c(cut(str,7,2)),recordType);
	DEBUG("recordType: %02d %02x\n",recordType,recordType);

	return checksum_ok(str, byteCount);
}

void execute_cmd(string cmd) {

}

int main() {
	string hexLine;
	string parsedCmd;
	ifstream hexFile;

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
		execute_cmd(parsedCmd);
		DEBUG("-------------\n");
	}
	return 0;	
}