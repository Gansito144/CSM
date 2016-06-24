#inlude <bits/stdc++.h>

using namespace std;

void parse_cmd(string str, string cmd) {
	// Clear whatever cmd contains
	cmd = "";
}

void execute_cmd(string cmd) {
	
}

int main() {
	string hexLine;
	string parsedCmd;

	int err = 0;

	while( !err ) {
		// Read each line from .hex file
		getline(cin, hexLine);
		// Now parse the string to a more friendly format
		err = parse_cmd(hexLine, parsedCmd);
		if(!err) {
			// If no errors proceed to execute the command
			execute_cmd(parsedCmd);
		}
	}
	return 0;	
}