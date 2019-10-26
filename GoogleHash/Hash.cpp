#include <iostream>
#include <ctime>
#include "Hash.h"
#include<math.h>


template <class T>
Hash<T>::Hash(double start,string str) {
	L.TL = start;
	L.A = str;
	L.m = start;
	L.M = 15 * L.m;
}
template <class T>
Hash<T>::~Hash() {

}
template <class T>
void Hash<T>::HashCreate(int m) // Create T, A. T will have m slots; A should be 15m
{
	L.A = new char[L.M];
	L.TL = new double[L.m];

}
template <class T>
bool Hash<T>::HashEmpty() // Check if L is empty
{
	return true;
}
template <class T>
bool Hash<T>::HashFull() // Check if L can maintain more words
{
	return true;
}
template <class T>
void Hash<T>::HashPrint() // Print of L
{

}
template <class T>
double Hash<T>::HashInsert() //Insert w into L (and T and A)
{
	return 0;
}
template <class T>
double Hash<T>::HashDelete() //Delete w from L (but not necessarily from A)
{
	/*
	we just need to delete one in the L. But according to the input here, we need to 
	*/
	return 0;
}
template <class T>
double Hash<T>::HashSearch() //Search for string in L (and this means T)
{
	
	return 0;
}
template <class T>
void Hash<T>::HashBatch(string filename)
{

}

template <class T>
/* when we need to add an word in wordlist, and wordlist is full, then we need to
adjust the length of word table and hash table, the method is evertime we double
the size of wordlist, and we adjust the length of hash table. Also, we reculculate
every stored element in hash table.
*/
void Hash<T>::HashAdjust()
{


}
void Hash<T>::WordsAdjust()
{


}