#include <iostream>
#include <ctime>
#include "Hash.h"
#include<math.h>


template <class T>
Hash<T>::Hash(int init_size, string str, int init_incf, int init_timesf, int init_FCode) {
	L.Hashtable = NULL;
	L.Wordstable = str;
	L.Htable_size = init_size;
	L.incf = init_incf;
	L.timesf = init_timesf;
	L.Wtable_size = L.timesf * L.Htable_size;
	L.Record_num = 0;
	Function_Code = init_FCode;
}
template <class T>
Hash<T>::~Hash() {
	delete L.Wordstable;
	delete L.Hashtable;
}
template <class T>
void Hash<T>::HashCreate() // Create T, A. T will have m slots; A should be 15m
{
	L.Wordstable = new char[L.Wtable_size];
	for (int i = 0; i < L.Wtable_size; i++)
		L.Wordstable[i] = '\0';
	L.Hashtable = new int[L.Htable_size];
	for (int i = 0; i < L.Htable_size; i++)
		L.Hashtable[i] = -1;

}
template <class T>
bool Hash<T>::HashEmpty() // Check if L is empty
{
	//find out whether hash is full or not 
	return L.Record_num == 0 ? true : false;
}
template <class T>
bool Hash<T>::HashFull() // Check if L can maintain more words
{
	return L.Record_num >= L.Htable_size ? true : false;
}
template <class T>
bool Hash<T>::Wtable_Not_Enough() // Check if L can maintain more words
{
	return w.length + 1 >= L.Wtable_size - L.letter_num ? true : false;
}
template <class T>
void Hash<T>::HashPrint() // Print of L
{

}
template <class T>
bool Hash<T>::HashInsert() //Insert w into L (and T and A)
{
	/*actually it should be a......recursive function......we need to write down 
	
	*/
	if (HashFull() || Wtable_Not_Enough()) {
		HashAdjust();

	}
	HashFunction();
	L.Record_num ++;
	L.letter_num += w.length + 1;
	return 0;
}
template <class T>
int Hash<T>::HashDelete() //Delete w from L (but not necessarily from A)
{
	/*
	we just need to delete one in the L. But according to the input here, if not we assign no 
	*/
	int HashIndex = HashSearch();
	if (HashIndex != -1) 
		L.Hashtable[HashIndex] = -1;
	return 0;
}
template <class T>
int Hash<T>::HashSearch() //Search for string in L (and this means T)
{
	int HashIndex = -1;
	//diectly search -1 for not get one
	int WordSum = AsciiSum();
	for (int i = 0; i < L.Htable_size; i++)
	{
		HashIndex = HashFunction(WordSum, i);
		//need a print out here,check first
		if (!w.compare(&(L.Wordstable[L.Hashtable[HashIndex]])))
			return HashIndex;
	}
	return -1;
}
template <class T>
void Hash<T>::HashBatch(string filename)
{
	/*
	Get the file stream and get every line, every line is a command, using switch case,
	using this function to give the tests.
	*/
}

template <class T>
/* when we need to add an word in wordlist, and wordlist is full, then we need to
adjust the length of word table and hash table, the method is evertime we double
the size of wordlist, and we adjust the length of hash table. Also, we reculculate
every stored element in hash table.
We need to keep that the size of hash table and the size of words satisfy the 15 times.
*/
void Hash<T>::HashAdjust()
{
	//double the size of the Hash table and readjust the Hash
	L.Htable_size = L.incf * L.Htable_size + 1;
	
}

template <class T>
void Hash<T>::WordsAdjust()
{
	//double the size of A and readjust the size of Hash 
	
	L.Wtable_size = L.incf * L.Htable_size;

}

template <class T>
int Hash<T>::HashFunction(int WordSum, int factor)
{
	int result = 0;
	switch (Function_Code)
	{
	case 0:
		result = (WordSum % L.Htable_size + factor*factor) % L.Htable_size;
		break;
	case 1:
		result = (WordSum % L.Htable_size + factor) % L.Htable_size;
		break;
	default:
		break;
	}
	return result;

}

template <class T>
int Hash<T>::AsciiSum()
{
	int WordSum = 0;
	for (int i = 0; i < w.length; i++)
		WordSum += w[i];
	return WordSum;
}
