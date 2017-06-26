#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

/* The archetypal call is the following:

	tone(8, NOTE_A4, 300);
	delay(400);

   This program simply converts from a specified format to the more cumbersome one:

	ex: 'A4 68' to the above 
*/


// The sixteenth is currently the shortest note
//   as well as the quantization step
#define SHORTEST_NOTE 16

int main(int argc, char** argv) {

	int bpm = 120;
	int timeSignatureDenom = 4; 									// note that gets the beat
	int timeStepForDenomMS = (60 / bpm) * 1000;
	int timeStepMS = timeStepForDenomMS / (SHORTEST_NOTE / timeSignatureDenom); // sixteenth note is lowest discrete step

	int noteLength;

	map<char,int> noteVals;
	noteVals['w'] = SHORTEST_NOTE / 1;
	noteVals['h'] = SHORTEST_NOTE / 2;
	noteVals['q'] = SHORTEST_NOTE / 4;
	noteVals['e'] = SHORTEST_NOTE / 8;
	noteVals['s'] = SHORTEST_NOTE / 16;


	const char* file = (argc==2) ?  argv[1] : "input_files/input.txt";

	string line;

	std::fstream infile, outfile, defines;
	defines.open("lib/defines.txt", std::fstream::in); // should be a header file, but tinkercad doesn't allow :_(
    infile.open (file, std::fstream::in);
	outfile.open("melody.ino", std::fstream::trunc | std::fstream::out);

	outfile << "/*\n    File created by Phillip Ring\n    Copyright. All Rights Reserved.\n*/\n\n";
	while (getline(defines, line)) { outfile << line << endl; }
	outfile << "void setup() {}\n\n";
	outfile << "void loop() {\n\n";

	int lineNum=1;
	while (getline(infile, line)) {
	
		lineNum++;	

		if (line[0] == '/') continue;
		
		// rests
		if (line.size() == 3) {
			outfile << "\tdelay(" << (line[2]-'0')*timeStepMS << ");\n\n";
		}
		// natural notes 
		else if (line.size() == 5) {
			noteLength = (line[4] == '.') ? noteVals[line[3]]*1.5 : noteVals[line[3]];
			outfile << "\ttone(8, NOTE_" << line[0] << line[1] << ", " << noteLength*timeStepMS << ");\n";
			outfile << "\tdelay(" << noteLength*timeStepMS << ");\n\n";
		}
		// sharp notes
		else if (line.size() == 6) {
			noteLength = (line[5] == '.') ? noteVals[line[4]]*1.5 : noteVals[line[4]];
			outfile << "\ttone(8, NOTE_" << line[0] << line[1] << line[2] << ", " << noteLength*timeStepMS << ");\n";
			outfile << "\tdelay(" << noteLength*timeStepMS << ");\n\n";
		}	
		else {
			cout << "bad line @ " << lineNum << endl;
		}

	}

	outfile << "}\n";

	infile.close();
	outfile.close();
	defines.close();

	return 0;
}
