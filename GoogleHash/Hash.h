#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include <iostream>
#include<math.h>
using namespace std;


template <class T>
class lexicon {
public:
	double* Hashtable;
	T* Wordstable;
	double Htable_size;
	double Wtable_size;
	//char* w;
};


template <class T>
class Hash{

public:
	Hash(double start = 0, string str = " ");//?????????
	~Hash();
	void HashCreate(int m); // Create T, A. T will have m slots; A should be 15m

	bool HashEmpty(); // Check if L is empty
	bool HashFull(); // Check if L can maintain more words
	void HashPrint(); // Print of L
	double HashInsert(); //Insert w into L (and T and A)
	double HashDelete(); //Delete w from L (but not necessarily from A)
	double HashSearch(); //Search for string in L (and this means T)
	void HashBatch(string filename);

	void HashAdjust();
	void WordsAdjust();


	//-------------------------------------------------------------------
	lexicon<char> L;
	char* w;

};





#endif 