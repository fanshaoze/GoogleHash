#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include <iostream>
#include<math.h>
using namespace std;


class {

public:
	void HashCreate(lexicon L, int m); // Create T, A. T will have m slots; A should be 15m
	bool HashEmpty(lexicon L); // Check if L is empty
	bool HashFull(lexicon L); // Check if L can maintain more words
	void HashPrint(lexicon L); // Print of L
	double HashInsert(lexicon L, word w); //Insert w into L (and T and A)
	double HashDelete(lexicon L, word w); //Delete w from L (but not necessarily from A)
	double HashSearch(lexicon L, word w); //Search for string in L (and this means T)
	void HashBatch(lexicon L, string filename);

	//-------------------------------------------------------------------
	lexicon L;
};

class lexicon {
public:
	double* T;
	char* A;
	double M;
	double m;
};
class word {
	int length;
	char* singleword;
};




#endif 