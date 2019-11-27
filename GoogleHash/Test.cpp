#include <iostream>
#include <fstream>
#include "Hash.h"
using namespace std;



int main(int argc, char* argv[]) {
	Hash GoogleHash(10, " ", 15, 2, 0);
	string cmd(argv[1]);

	istream* in = & cin;
	ifstream file;
	cout << "argc:"<<argc << endl;
	for (int i = 0; i < argc; i++) {
		cout << "agrv[" << i << "]:" << argv[i] << endl;
	}
	if (argc == 1) {
		cout << "MISSING COMMAND" << endl;
		return 1;
	}

	if (argc > 2) {
		cout << "TOO MANY ARGUMENTS" << endl;
		return 1;
	}
	if (argc == 2) {
		file.open(argv[1]);
		if (!file.is_open()) {
			cout << argv[1] << " FILE COULD NOT BE OPENED" << endl;
			return 1;
		}
		in = &file;
	}


	GoogleHash.HashOperation(*in, cout);


	



}


