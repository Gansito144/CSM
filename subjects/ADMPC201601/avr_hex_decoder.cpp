#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

#define cut(s,i,sz) ((s).substr((i),(sz)))
#define to_c(s) ((s).c_str())
#define getHex(s,n) (sscanf(s,"%x",&(n)))

using namespace std;

int checksum_ok(string cmd, int size) {
	int check = 0, twoByte, i;
	/*for(i=1; i<size-2; i += 2) {
		sscanf(cmd.substr(i,2).c_str(),"%x",&twoByte);
		check += twoByte;
	}
	// Two complement of a function
	check = -(unsigned int)check;
	// The cheksum expected
	sscanf(cmd.substr(i,2).c_str(),"%x",&twoByte);
	printf("%x %x\n",check,twoByte);*/
	return check != twoByte;
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
	printf("byteCount: %02d %02x\n",byteCount,byteCount);

	/** 
	* Address: four hex digits, representing 
	* the 16-bit beginning memory address offset
	* of the data. 
	**/
	getHex(to_c(cut(str,3,4)),address);
	printf("address: %04d %04x\n",address,address);

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
	printf("recordType: %02d %02x\n",recordType,recordType);

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
		puts("-------------");
	}
	return 0;	
}