#include <iostream>
#include <fstream>
#include "Hash.h"



Hash::Hash(int init_size, string str, int init_incf, int init_Lfactor, int init_FCode) {
	L.Hashtable = NULL;

	//L.Wordstable = (char*)malloc((str.length() + 1) * sizeof(char));
	//str.copy(L.Wordstable, str.length(), 0);

	L.Htable_size = init_size;
	L.incf = init_incf;
	L.Lfactor = init_Lfactor;
	L.Wtable_size = L.Lfactor * L.Htable_size;
	L.Record_num = 0;
	L.letter_num = 0;
	Function_Code = init_FCode;
}

Hash::~Hash() {
	delete L.Wordstable;
	delete L.Hashtable;
}

void Hash::HashCreate() // Create T, A. T will have m slots; A should be 15m
{
	cout << "wordtable size: " << L.Wtable_size << " and Hashtable size: " << L.Htable_size << endl;
	L.Wordstable = new char[L.Wtable_size];
	for (int i = 0; i < L.Wtable_size; i++)
		L.Wordstable[i] = '\0';
	L.Hashtable = new int[L.Htable_size];
	for (int i = 0; i < L.Htable_size; i++)
		L.Hashtable[i] = -1;
}

bool Hash::HashEmpty() // Check if L is empty
{
	//find out whether hash is full or not 
	return L.Record_num == 0 ? true : false;
}

bool Hash::Htable_Not_Enough() // Check if L can maintain more words
{
	return L.Record_num + 1 >= L.Htable_size ? true : false;
}

bool Hash::Wtable_Not_Enough() // Check if L can maintain more words
{

	return L.letter_num + w.length() + 1 >= L.Wtable_size ? true : false;
}

void Hash::HashPrint() // Print of L
{
	utils U;
	int Bits = U.Bit_Int(L.Htable_size);
	cout << "T" << endl;
	for (int i = 0; i < L.Htable_size; i++) {
		cout.width(Bits);
		cout << i << ": ";
		if (L.Hashtable[i] == -1) cout  << endl;
		else cout << L.Hashtable[i] << endl;
	}
	cout << "A" << endl;
	for (int i = 0; i < L.letter_num; i++) {
		if (L.Wordstable[i] == '\0') cout<<'\\';
		else cout << L.Wordstable[i];
	}
	return;
}

bool Hash::HashInsert() //Insert w into L (and T and A)
{
	//actually it should be a......recursive function......we need to write down 
	
	int j = 0;
	//HashFunction();
	int index;
	int origin_letter_num = L.letter_num;
	if (Htable_Not_Enough() || Wtable_Not_Enough()) {
		cout <<"Htable/Wtable Not Enough"<<endl;
		HashAdjust();
		return 0;
	}



	for (int i = 0; i < L.Htable_size; i++) {
		index = HashFunction(U.AsciiSum(w), i);
		cout << "Insert index:" << index << endl;
		if (L.Hashtable[index] == -1) break;
		j++;
	}
	if (j == L.Htable_size - 1) {
		cout << "No proper place for new word" << endl;
		HashAdjust();
	}

	else {
		L.Hashtable[index] = origin_letter_num;
		for (int i = L.letter_num; i < L.letter_num + w.length(); i++) L.Wordstable[i] = w[i - L.letter_num];
		L.Wordstable[L.letter_num + w.length()] = '\0';
		L.Record_num++;
		L.letter_num += w.length() + 1;
		
	}

	return 0;
}

int Hash::HashDelete() //Delete w from L (but not necessarily from A)
{
	/*
	we just need to delete one in the L. But according to the input here, if not we assign no 
	*/
	int HashIndex = HashSearch();
	if (HashIndex != -1) 
		L.Hashtable[HashIndex] = -1;
	return 0;
}

int Hash::HashSearch() //Search for string in L (and this means T)
{
	//utils U;
	int HashIndex = -1;
	//diectly search -1 for not get one
	int WordSum = U.AsciiSum(w);
	for (int i = 0; i < L.Htable_size; i++)
	{
		HashIndex = HashFunction(WordSum, i);
		//need a print out here,check first
		if (!w.compare(&(L.Wordstable[L.Hashtable[HashIndex]])))
			return HashIndex;
	}
	return -1;
}




/* when we need to add an word in wordlist, and wordlist is full, then we need to
adjust the length of word table and hash table, the method is evertime we double
the size of wordlist, and we adjust the length of hash table. Also, we reculculate
every stored element in hash table.
We need to keep that the size of hash table and the size of words satisfy the 15 times.
*/
void Hash::HashAdjust()
{
	/*flag to find out whether the new hash size and word table size is good for every

	*/
	bool cflag = false;
	int ori_Htable_size = L.Htable_size;
	int ori_Wtable_size = L.Wtable_size;
	int ori_Record_num = L.Record_num;
	int ori_letter_num = L.letter_num;
	int j = 0;

	//double the size of the Hash table and readjust the Hash
	while(!cflag){
		cflag = true;
		int sum = 0;
		int index = -1;
		string cword = "";
		L.Htable_size = L.incf * L.Htable_size + 1;
		WordsAdjust();
		if (ori_letter_num + w.length() + 1 > L.Wtable_size) {
			cflag = false;
			continue;
		}
		//Copy the current hash table to Hash temp 
		int* Hashtmp = new int[ori_Htable_size];
		for (int i = 0; i < ori_Htable_size; i++) {
			Hashtmp[i] = L.Hashtable[i];
		}
		//Copy the current word table to Hash temp, including the inserting word w
		char * Wtabletmp = new char[ori_Wtable_size];
		for (int i = 0; i < ori_letter_num; i++) Wtabletmp[i] = L.Wordstable[i];
		for (int i = ori_letter_num; i < ori_letter_num + w.length(); i++) Wtabletmp[i] = w[i - ori_letter_num];
		for (int i = ori_letter_num + w.length(); i < L.Wtable_size; i++) Wtabletmp[i] = '\0';
		
		delete L.Hashtable;
		delete L.Wordstable;
		L.Record_num = 0;
		L.letter_num = 0;
		HashCreate();

		//Insert all the exist words in the new hash table  

		for (int i = 0; i < ori_Htable_size; i++) {
			index = -1;
			cout << "hash tmp[" << i << "] : " << Hashtmp[i] << endl;
			if (Hashtmp[i] != -1) {
				cword = Wtabletmp[Hashtmp[i]];
				cout << "cword : "<< cword <<" AsciiSum : "<<U.AsciiSum(cword) << endl;
			}
			j = 0;
			for (int i = 0; i < ori_Htable_size; i++) {
				index = HashFunction(U.AsciiSum(cword), i);
				cout << "new index : "<<index << endl;
				if (L.Hashtable[index] != -1) break;
				j++;
			}
			if (j == ori_Htable_size - 1) {
				cflag = false;
				break;
			}
			else L.Hashtable[index] = Hashtmp[i];
		}
		if (!cflag) break;


		//Insert w into the hash table 
		j = 0;
		for (int i = 0; i < ori_Htable_size; i++) {
			index = HashFunction(U.AsciiSum(w) , i);
			if (L.Hashtable[index] != -1) break;
			j++;
		}
		if (j == ori_Htable_size - 1) {
			cflag = false;
			break;
		}
		else L.Hashtable[index] = ori_letter_num;
		
	}



	L.Record_num = ori_Record_num++;
	L.letter_num = ori_letter_num + w.length() + 1;
	
}

void Hash::WordsAdjust()
{
	//double the size of A and readjust the size of Hash 
	
	L.Wtable_size = L.incf * L.Htable_size;

}


int Hash::HashFunction(int WordSum, int factor)
{
	int result = -1;
	switch (Function_Code)
	{
	case 0:
		return (WordSum % L.Htable_size + factor * factor) % L.Htable_size;
		break;
	case 1:
		return (WordSum % L.Htable_size + factor) % L.Htable_size;
		break;
	default:
		break;
	}
	return result;

}





void Hash::HashOperation(istream& in, ostream& out)
{
	int i = 0;
	string Command;
	string para;
	string CommandLine = " ";

	for (;;) {
		//CommandLine = in.get();
		getline(in, CommandLine);
		if (in.eof() || in.bad()) return;

		cout << "CommandLine: " << CommandLine << endl;
		cout << "Command size: " << CommandLine.length() << endl;
		for (i = 0; i < CommandLine.length(); i++) {
			if (CommandLine.at(i) == ' ') break;
		}
		Command = CommandLine.substr(0, i+1);
		cout << "Command: " << Command << endl;
		cout << "Command length: " << Command.length() << endl;
		if (Command == "13") {//print
			if (Command.length() != CommandLine.length()) return;
			else HashPrint();
		}
		else {
			Command = Command.substr(0, i);
			cout << "Command: " << Command << endl;
			cout << "Command length: " << Command.length() << endl;
			para = CommandLine.substr(i + 1, CommandLine.length() - (i + 1));
			cout << "para: " << para << endl;
			cout << "para size: " << para.length() << endl;
			if (Command == "14") {
				for (i = 0; i < para.length(); i++) {
					if (!isdigit(para[i])) return;
				}
				L.Htable_size = stoi(para);
				WordsAdjust();
				cout << "Htable_size: " << L.Htable_size << endl;
				HashCreate();
			}
			else {
				w = para;
				if (Command == "10") {
					HashInsert();
				}
				else if (Command == "11") {
					HashDelete();
				}
				else if (Command == "12") {
					HashSearch();
				}
				else if (Command == "15") {
					continue;
				}
				else return;
			}
		}
	}
	return;
}




