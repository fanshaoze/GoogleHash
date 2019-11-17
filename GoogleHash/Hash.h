#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include <iostream>
#include<math.h>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;



class lexicon {
public:
	int* Hashtable;
	char* Wordstable;
	int Htable_size;
	int Wtable_size;
	int letter_num;
	int Record_num;
	int incf;
	int Lfactor;
	//char* w;
};



class Hash{

public:
	Hash(int init_size = 10, string str = " ",int init_Lfactor = 15, int init_incf = 2, int init_FCode = 0);//?????????
	~Hash();

	void HashCreate(); // Create L, A. T will have m slots; A should be 15m
	bool HashEmpty(); // Check if L is empty
	
	bool HashFull(); // Check if L can maintain more words
	bool Wtable_Not_Enough(); // Check if L can maintain more words
	
	void HashPrint(); // Print of L
	
	bool HashInsert(); //Insert w into L (and T and A)
	int HashDelete(); //Delete w from L (but not necessarily from A)
	int HashSearch(); //Search for string in L (and this means T)
	
	void HashBatch(string filename);

	int HashFunction(int result, int factor);
	int AsciiSum();

	void HashAdjust();
	void WordsAdjust();

	void HashOperation(istream& in, ostream& out);


	//-------------------------------------------------------------------
	lexicon L;
	string w;
	int Function_Code;
	//int 

};





#endif 