#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

// Endianess macro
#define little_endian 0

// Macros for string processing
#define cut(s,i,sz) ((s).substr((i),(sz)))
#define to_c(s) ((s).c_str())
#define getHex(s,n) (sscanf(s,"%x",&(n)))

// Macros for bits manipulation
#define get4Bits(w,B) (((w)&((0xF)<<(B*4)))>>(B*4))
#define getByte(w,B) (((w)&((0xFF)<<(B*8)))>>(B*8))
#define getBit(w,b) (((w)&((0x1)<<b))>>b)
#define shiftBits(w,b) ((w)<<b)

// Macros to evaluate commands
#define AVR_EXE printf

using namespace std;

// Just for debugging process
#if 1
char logs[123456];
#define DEBUG(...) sprintf(logs,__VA_ARGS__)
#else 
#define DEBUG printf
#endif

// Type to store array of functions
typedef void (*Handler)(int &opCode);

// Return true when the checksum of hex line is OK
int checksum_ok(string &str, int &size, int &checkSum) {
	unsigned int check=0;
	int twoByte, i=1;
	for(; i< size; i += 2) {
		getHex(to_c(cut(str,i,2)),twoByte);
		check += twoByte;
		check &= 0xFF;
		DEBUG("i(%d) %x %d %x\n",i,twoByte,twoByte,check);
	}
	// Two complement of a function
	check = (~check) + 1;
	check &= 0xFF;
	// Verify against cheksum expected
	return (check != checkSum) ? -EINVAL : 0;
}

// Separates commands from each hex line 
int parse_cmd(string &str, string &cmds) {
	int byteCount, address, recordType;
	int checkSum, idx = 1;

	// Clear whatever cmds contains
	cmds = "";
	if(!str.size() || ':' != str[0] ){
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

void op0xzz(int &opCode) {
	int B = get4Bits(opCode,2);
	int d=0, r=0;
	char tmp[20];
	string cmd, param;
	DEBUG("OpCode 0x%x B0x%x",opCode,B);
	if(0 == B){
		cmd = (0 == opCode) ? "nop" : "[R]";
		param = "";
	}else if(0x4 <= B){
		cmd = (0xC<=B)?"add":((0x8<=B)?"sbc":"cpc");
		r = shiftBits(getBit(opCode,9),4) + get4Bits(opCode,0);
		d = shiftBits(getBit(opCode,8),4) + get4Bits(opCode,1);
		sprintf(tmp,"R%d, R%d",d,r);
		param = tmp;
	}else {
		switch(B){
			case 1:
			case 2: {
				r = get4Bits(opCode,0);
				d = get4Bits(opCode,1);
				cmd = (2==B)?"movw":"muls";
				break;
			}
			case 3: {
				//Turn off last bit for each word
				r = get4Bits(opCode,0)^0x8;
				d = get4Bits(opCode,1)^0x8;
				// Generate new code to see which type of mul is
				int mCode = shiftBits(getBit(opCode,7),1);
				   mCode += shiftBits(getBit(opCode,3),0);
				switch(mCode){
					case 0:{cmd = "mulsu";break;}
					case 1:{cmd = "fmul";break;}
					case 2:{cmd = "fmuls";break;}
					case 3:{cmd = "fmulsu";break;}
				}
				break;
			}
		}
		sprintf(tmp,"R%d, R%d",d,r);
		param = tmp;
	}
	AVR_EXE("%s\n",to_c(cmd+" "+param));
}

void op1xzz(int &opCode) {
}

void op2xzz(int &opCode){printf("%s\n",__FUNCTION__);}
void op3xzz(int &opCode){printf("%s\n",__FUNCTION__);}
void op4xzz(int &opCode){printf("%s\n",__FUNCTION__);}
void op5xzz(int &opCode){printf("%s\n",__FUNCTION__);}
void op6xzz(int &opCode){printf("%s\n",__FUNCTION__);}
void op7xzz(int &opCode){printf("%s\n",__FUNCTION__);}
void op8xzz(int &opCode){printf("%s\n",__FUNCTION__);}
void op9xzz(int &opCode){printf("%s\n",__FUNCTION__);}
void opAxzz(int &opCode){printf("%s\n",__FUNCTION__);}
void opBxzz(int &opCode){printf("%s\n",__FUNCTION__);}
void opCxzz(int &opCode){printf("%s\n",__FUNCTION__);}
void opDxzz(int &opCode){printf("%s\n",__FUNCTION__);}
void opExzz(int &opCode){printf("%s\n",__FUNCTION__);}
void opFxzz(int &opCode){printf("%s\n",__FUNCTION__);}

// Axzz Array to select based on the first bytes
Handler oAxzz[] = {
    op0xzz, op1xzz, op2xzz, op3xzz,
    op4xzz, op5xzz, op6xzz, op7xzz,
    op8xzz, op9xzz, opAxzz, opBxzz,
    opCxzz, opDxzz, opExzz, opFxzz
};

// Choose the right command to execute based on some reduction  
void execute_cmd( int &opCode ) {
	int A = get4Bits(opCode,3);
	// Delegate the responsability to next functions
	DEBUG("A (%02d) (%x)",A,A);
	oAxzz[A](opCode);
}


void split_cmds(string &cmds) {
	// We had blocks of 4 bytes, lets process them
	int opCode, swapCode;
	for(int i=0; i<cmds.size(); i += 4) {
		getHex(to_c(cut(cmds,i,4)),opCode);
		DEBUG("opCode: %04d %04x\n",opCode,opCode);
		/** Now that we know each opcode lets 'execute' them
		* Each opcode is an int of 16 bits
		**/
		if(little_endian) {
			/* We have to swap the byte order to Endianess */
			swapCode  = shiftBits(getByte(opCode,0),8);
			swapCode |= shiftBits(getByte(opCode,1),0);
		}
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